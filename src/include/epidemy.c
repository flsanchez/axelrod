#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "agent.h"
#include "axelrod.h"
#include "label.h"
#include "misc.h"
#include "epidemy.h"

// epidemyInit() inicializa el tipo epidemia, con un vector de compartimientos
// de largo nComp y cada uno de los compartimientos a 0

int epidemyInit(epidemy* population, int idx, int nComp){
  population[idx].comp = malloc(nComp*sizeof(int));
  for(int i = 0; i < nComp; i++) population[idx].comp[i] = 0;
  return 0;
}

// epidemyNCompNeig() devuelve cuantos vecinos en estado de compartimiento iComp
// tiene el agente idx

int epidemyCompNNeig(epidemy* population, vertex* graph, int idx, int iComp){
  int nEdges, i, res;
  res = 0;
  nEdges = graph[idx].nEdges;
  for(int idxEdges = 0; idxEdges < nEdges; idxEdges++){
    i = graph[idx].edges[idxEdges];
    res = res + population[i].comp[iComp];
  }
  return res;
}

// populationInit() inicializa la poblacion, con cada uno de los vectores comp
// con largo nComp

int populationInit(epidemy* population, int n, int nComp){
  for(int idx = 0; idx < n*n; idx++) epidemyInit(population, idx, nComp);
  return 0;
}

// populationInitSEIR() simplemente inicializa con nComp = 4

int populationInitSEIR(epidemy* population, int n){
  int nComp = 4;
  populationInit(population, n, nComp);
  return 0;
}

// populationFillSEIRVac() pone los agentes en susceptible o refractario
// de su opinion de vacunacion previamente sorteada (mucho muy importante)

int populationFillSEIRVacc(epidemy* population, agent* lattice, int n){
  int f, nComp = 4;
  for(int idx = 0; idx < n*n; idx++){
    f = lattice[idx].f;
    if(lattice[idx].feat[f-1] == 0){
      population[idx].comp[0] = 1;
      for(int i = 1; i < nComp; i++) population[idx].comp[i] = 0;
    }
    else{
      population[idx].comp[3] = 1;
      for(int i = 1; i < nComp; i++) population[idx].comp[i-1] = 0;
    }
  }
  return 0;
}

// populationSEIRInfect() infecta una cantidad de agentes sobre el cluster mas
// grande. Si el cluster mas grande es mas chico que la cantidad de infectados
// que quiero, devuelvo -1

int populationSEIRInfect(epidemy* population, vertex* graph,
                          agent* lattice, int n, int nInf)
{
  int frag = latticeLabelVac(graph, lattice, n); // labeleo
  // obtengo la etiqueta del cluster mas grande
  int labelClusMax = latticeLabelMax(lattice, n, frag);
  printf("LabelMax %d\n", labelClusMax);

  // obtengo la lista con los integrantes del cluster mas grande
  int* maxClusterList;
  int nMaxClusterList = latticeClusterNList(lattice, n, labelClusMax,
                                        &maxClusterList);
  // mezclo el array
  shuffleArray(maxClusterList, nMaxClusterList);
  // chequeo que sea posible la asignacion, si algo salio mal, devuelvo -1
  if(nMaxClusterList < nInf) return -1;
  // asigno los infectados
  for(int idxInf = 0; idxInf < nInf; idxInf++){
    int i = maxClusterList[idxInf];
    // promuevo el agente i a infectado
    population[i].comp[2] = 1;
    population[i].comp[0] = 0;
    population[i].comp[1] = 0;
    population[i].comp[3] = 0;
  }
  return 0;
}

// populationFillRand() llena con compartimientos aleatorios para cada agente

int populationFillRand(epidemy* population, int n, int nComp){
  for(int i = 0; i < n*n; i++){
    int whichComp = getRand(nComp);
    population[i].comp[whichComp] = 1;
  }
  return 0;
}

// populationNCompTotal() devuelve la cuenta de cuantos agentes en la poblacion
// se encuentran en estado de compartimiento compN

int populationCompNTotal(epidemy* population, int n, int iComp){
  int res = 0;
  for(int idx = 0; idx < n*n; idx++) res = res + population[idx].comp[iComp];
  return res;
}

// populationNCompNeig() llena el vector infArray, donde el valor de la
// componente i-esima arroja cuantos vecinos en estado de compartimiento iComp
// tiene cada agente

int populationCompNNeig(epidemy* population, vertex* graph, int* infArray,
                        int n, int iComp)
{
  for(int idx = 0; idx < n*n; idx++){
    infArray[idx] = epidemyCompNNeig(population, graph, idx, iComp);
  }
  return 0;
}

int populationSaveToFile(FILE* fs, epidemy* population, int n){
  int whichComp;
  for(int idx = 0; idx < n*n; idx++){
    whichComp = 0;
    while(population[idx].comp[whichComp] == 0) whichComp++;
    fprintf(fs, "%d ", whichComp);
  }
  fprintf(fs, "\n");
  return 0;
}
// stepSEIR() realiza el paso temporal para un modelo SEIR

int stepSEIR(epidemy* population, vertex* graph, int n, float nuS, float nuE,
              float nuI, float dt)
{
  int whichComp; // aca va en que compartimiento esta cada agente
  float prob,r;
  // para cada agente
  for(int idx = 0; idx < n*n; idx++){
    // busco en que compartimiento esta el agente
    whichComp = 0;
    while(population[idx].comp[whichComp] == 0) whichComp++;
    // calculo las probabilidades para cada estado
    prob = 0;
    // si es susceptible
    if(whichComp == 0){
      float aux = 1;
      int z = epidemyCompNNeig(population, graph, idx, 2); // vecinos infectados
      for(int i = 0; i < z; i++) aux = aux*(1-dt*nuS);
      prob = 1-aux;
    }
    // si es expuesto
    else if(whichComp == 1) prob = nuE*dt;
    // si es infectado
    else if(whichComp == 2) prob = nuI*dt;
    // con probabilidad prob promuevo de un estado a otro
    // notar que si whichComp == 3 (refractario) -> prob = 0
    r = (float)rand()/RAND_MAX; // tiro la moneda
    if(r<prob){
      population[idx].comp[whichComp] = 0;
      population[idx].comp[whichComp + 1] = 1;
    }
  }
  return 0;
}

int stopReachedSEIR(epidemy* population, int n){
  int E,I;
  E = populationCompNTotal(population, n, 1); // total de expuestos
  I = populationCompNTotal(population, n, 2); // total de infectados
  if(E+I == 0) return 1; // si no tengo riesgo de epidemias, devuelvo 1
  else return 0;
}

int populationFree(epidemy* population, int n){
  for(int idx=0;idx<n*n;idx++) free(population[idx].comp);
  return 0;
}

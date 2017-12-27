#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "agent.h"
#include "axelrod.h"
#include "label.h"
#include "misc.h"
#include "functions.h"
#include "epidemy.h"

// epidemyInit() inicializa el tipo epidemia, con un vector de compartimientos
// de largo nComp y cada uno de los compartimientos a 0, salvo el removido a 1

int epidemyInit(epidemy* population, int idx, int nComp){
  population[idx].comp = malloc(nComp*sizeof(int));
  for(int i = 0; i < nComp-1; i++) population[idx].comp[i] = 0;
  population[idx].comp[nComp-1] = 1; // pongo en removidos
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

// populationFillSEIRVacc() pone los agentes en susceptible o refractario
// de su opinion de vacunacion previamente sorteada (mucho muy importante)

int populationFillSEIRVacc(epidemy* population, int* notRemoved, int lenNotRem)
{
  int nComp = 4;
  int idxNotRemoved = 0;
  for(int idx = 0; idx < lenNotRem; idx++){
    idxNotRemoved = notRemoved[idx];
    population[idxNotRemoved].comp[0] = 1;
    for(int i = 1; i < nComp; i++) population[idxNotRemoved].comp[i] = 0;
  }
  return 0;
}

// populationSEIRInfectFromList() infecta los agentes desde la lista

int populationSEIRInfectFromList(epidemy* population, int n, int nInf,
                                  int* notRemoved, int lenNotRem)
{
  // mezclo el array
  shuffleArray(notRemoved, lenNotRem);
  // infecto una cantidad nInf
  for(int idxInf = 0; idxInf < nInf; idxInf++){
    int i = notRemoved[idxInf];
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
              float nuI, float dt, int* notRemoved, int* lenNotRem)
{
  int whichComp; // aca va en que compartimiento esta cada agente
  float prob,r;
  int dInf = 0;
  int idxExp = 0;
  int newLen = *lenNotRem;
  int idx = notRemoved[idxExp];
  // para cada agente
  while(idx != -1 && idxExp < newLen){
    // busco en que compartimiento esta el agente
    whichComp = 0;
    while(population[idx].comp[whichComp] == 0) whichComp++;
    // calculo las probabilidades para cada estado
    prob = 0;
    r = (float)rand()/RAND_MAX; // tiro la moneda
    // si es susceptible
    if(whichComp == 0){
      float aux = 1;
      int z = epidemyCompNNeig(population, graph, idx, 2); // vecinos infectados
      for(int i = 0; i < z; i++) aux = aux*(1-dt*nuS);
      prob = 1-aux;
      // con probabilidad prob promuevo de un susceptible a expuesto
      if(r<prob){
        population[idx].comp[whichComp] = 0;
        population[idx].comp[whichComp + 1] = 1;
      }
      idxExp++;
    }
    // si es expuesto
    else if(whichComp == 1){
      prob = nuE*dt;
      // con probabilidad prob promuevo de un expuesto a infectado
      if(r<prob){
        population[idx].comp[whichComp] = 0;
        population[idx].comp[whichComp + 1] = 1;
        dInf++; // incremento en 1 el diferencial de infectados
      }
      idxExp++;
    }
    // si es infectado
    else if(whichComp == 2){
      prob = nuI*dt;
      // con probabilidad prob promuevo de un infectado a refractario
      if(r<prob){
        population[idx].comp[whichComp] = 0;
        population[idx].comp[whichComp + 1] = 1;
        notRemoved[idxExp] = notRemoved[newLen-1];
        notRemoved[newLen-1] = -1;
        newLen--;
      }
      else idxExp++;
    }
    idx = notRemoved[idxExp];
  }
  if(*lenNotRem != newLen) *lenNotRem = newLen;
  return dInf;
}

int SEIRFull(vertex* graphEpi, int n, int* notRemoved, int massNonVacc,
            int* infectedList, int lenInf,
            int nInf, float nuS, float nuE, float nuI, float dt)
{
  // inicializo las cosas para la epidemia
  epidemy* population = malloc(sizeof(epidemy)*n*n);
  // copio el tamaño del vector de no removidos
  int lenNotRem = massNonVacc;
  // copio la lista de no removidos
  int* notRemovedCp = malloc(lenNotRem*sizeof(int));
  for(int i = 0; i < lenNotRem; i++) notRemovedCp[i] = notRemoved[i];
  // inicializo el tipo population
  populationInitSEIR(population, n);
  // lleno la red con los no vacunados desde la lista not removed
  populationFillSEIRVacc(population, notRemoved, lenNotRem);
  // infecto desde la lista infectedList
  populationSEIRInfectFromList(population, n, nInf, infectedList, lenInf);
  // hago el avance temporal
  int stop = 0;
  int i = 0;
  int infTotal = nInf;
  while(stop == 0){
    infTotal = infTotal + stepSEIR(population, graphEpi, n, nuS, nuE, nuI, dt,
                                    notRemovedCp, &lenNotRem);
    stop = stopReachedSEIR(population, n);
    i++;
  }
  populationFree(population, n);
  free(population);
  free(notRemovedCp);
  return infTotal;
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

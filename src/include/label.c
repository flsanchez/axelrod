#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "axelrod.h"
#include "label.h"

// latticeLabel() identifica clusters en funcion de la homofilia

int latticeLabel(vertex* graph, agent* lattice, int n){

  int j;
  int f = lattice[0].f;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;
  for(int i = 1; i<n*n; i++) lattice[i].label = 0;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(commonTraits(lattice, idx, j) == f){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);
  return frag;
}

// latticeLabelFeatN() identifica clusters tomando el valor del featNIdx

int latticeLabelFeatN(vertex* graph, agent* lattice, int n, int featNIdx){

  int j;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;
  for(int i = 1; i<n*n; i++) lattice[i].label = 0;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(lattice[idx].feat[featNIdx] == lattice[j].feat[featNIdx]){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);
  return frag;
}

// latticeLabelVac() identifica clusters de noVacunadores

int latticeLabelVac(vertex* graph, agent* lattice, int n){
  int j;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;
  for(int i = 1; i<n*n; i++) lattice[i].label = 0;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(lattice[idx].vacc == lattice[j].vacc){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);

  // pongo a label 0 los vacunadores
  for(int idx = 0; idx<n*n; idx++){
    if(lattice[idx].vacc != 0) lattice[idx].label = 0;
  }

  return frag;
}

// latticeLabelImmu() identifica clusters de no Inmunizados

int latticeLabelImmu(vertex* graph, agent* lattice, int n){
  int j;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;
  for(int i = 1; i<n*n; i++) lattice[i].label = 0;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(lattice[idx].immu == lattice[j].immu){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);

  // pongo a label 0 los vacunadores
  for(int idx = 0; idx<n*n; idx++){
    if(lattice[idx].immu != 0) lattice[idx].label = 0;
  }

  return frag;
}

// latticeLabelCultural() identifica clusters en funcion de la homofilia cult

int latticeLabelCultural(vertex* graph, agent* lattice, int n){

  int j;
  int f = lattice[0].f;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;
  for(int i = 1; i<n*n; i++) lattice[i].label = 0;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(commonTraitsCultural(lattice, idx, j) == (f-1) ){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);
  return frag;
}

// latticeLabelMax() identifica el cluster mas grande y devuelve la etiqueta.
// por referencia devuelve el tamaño del cluster mas grande

int latticeLabelMax(agent *lattice, int n, int frag, int* Smax){

  //fragsz[i] contiene el tamaño del cluster de etiqueta i
  int *fragsz = malloc(frag*sizeof(int));
  //ns[i] contiene cuantos clusters de tamaño i-1 se encontraron en la red
  int *ns = malloc(n*n*sizeof(int));

  for(int i = 0; i<frag; i++) fragsz[i] = 0;
  for(int i = 0; i<n*n; i++) ns[i] = 0;

  clusterSize(lattice, n, frag, fragsz, ns);

  int mayor = 0;
  int labelMayor = 0;

  for(int i = 1; i<frag; i++){
    if(fragsz[i]>mayor){
      mayor = fragsz[i];
      labelMayor = i;
    }
  }

  free(fragsz);
  free(ns);

  *Smax = mayor;
  return labelMayor;

}

// latticeGetMaxClusterListVacc() devuelve el tamaño del cluster mas grande de no
// vacunadores, y por referencia llena una lista con los indices de los agentes
// que pertenecen al mismo.

int latticeGetMaxClusterListVacc(vertex* graph, agent* lattice, int n,
                              int** maxClusterList)
{
  int nMaxClusterList;
  // labeleo los clusters y hallo el mas grande, y una lista con sus integrantes
  int frag = latticeLabelVac(graph, lattice, n); // labeleo los noVacunadores
  // obtengo la etiqueta del cluster mas grande
  int labelClusMax = latticeLabelMax(lattice, n, frag, &nMaxClusterList);
  latticeClusterNList(lattice, n, labelClusMax, maxClusterList);
  return nMaxClusterList;
}

//latticeGetMaxClusterListImmu() devuelve el tamaño del cluster mas grande de no
// inmunizados, y por referencia llena una lista con los indices de los agentes
// que pertenecen al mismo.

int latticeGetMaxClusterListImmu(vertex* graph, agent* lattice, int n,
                              int** maxClusterList)
{
  int nMaxClusterList;
  // labeleo los clusters y hallo el mas grande, y una lista con sus integrantes
  int frag = latticeLabelImmu(graph, lattice, n); // labeleo los no Inmunizados
  // obtengo la etiqueta del cluster mas grande
  int labelClusMax = latticeLabelMax(lattice, n, frag, &nMaxClusterList);
  latticeClusterNList(lattice, n, labelClusMax, maxClusterList);
  return nMaxClusterList;
}

int falseLabel(agent *lattice, int *clase, int* commNeig, int nCommNeig, int idx){

  int* s = malloc(nCommNeig*sizeof(int));
  for(int i = 0; i<nCommNeig; i++) s[i] = lattice[commNeig[i]].label; // copio commNeig a s
  int minS = s[0]; //valor inicial

  for(int i = 0; i<nCommNeig; i++){
    while(clase[s[i]]<0) s[i] = -clase[s[i]];
    if(s[i]<minS) minS = s[i];
  }

  for(int i = 0; i<nCommNeig; i++){
    if(s[i] == minS) clase[s[i]] = s[i];
    else clase[s[i]] = -minS;
  }

  lattice[idx].label = minS;

  free(s);
  return 0;

}

int fixLabel(agent *lattice, int n, int *clase){

	int s;

	for(int i=0; i<n*n; i++){

		s = lattice[i].label;
		while(clase[s]<0) s = -clase[s];
		lattice[i].label = s;

	}

  return 0;

}

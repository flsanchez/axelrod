#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "agent.h"
#include "functions.h"

/* minDist() devuelve, dada una lista con las distancias y si esta marcado o no
  el vertice, el indice del vertice que tiene la minima distancia */
int minDist(int* dist, int* mark, int n){
  int minDistVal = INT_MAX;
  int minIdx;
  for(int idx = 0; idx < n*n; idx++){
    if(dist[idx]<=minDistVal && mark[idx] == 0){
      minDistVal = dist[idx];
      minIdx = idx;
    }
  }
  return minIdx;
}

int minPathLen(vertex* graph, int* dist, int n, int src){
  /* si mark[i] = 1 quiere decir que ya visite el nodo i. Si es 0,
    quiere decir que el nodo no ha sido visitado */
  int* mark = malloc(n*n*sizeof(int));
  int curr, newDist, neig;

  for(int i = 0; i<n*n; i++) dist[i] = INT_MAX;
  for(int i = 0; i<n*n; i++) mark[i] = 0;

  dist[src] = 0;

  for(int count = 0; count < n*n-1; count++){

    curr = minDist(dist, mark, n);
    mark[curr] = 1;

    for(int j = 0; j < graph[curr].nEdges; j++){ //para cada vecino
      neig = graph[curr].edges[j]; //indice del vecino;
      newDist = dist[curr] + 1; //distancia nueva es la distancia mas 1;
      /*si esta nueva distancia es menor que la distancia previamente guardada;*/
      if(newDist < dist[neig])
        dist[neig] = newDist; //guardo la nueva distancia como distancia al nodo
    }

  }

  free(mark);

  return 0;
}

float avMinPathLen(vertex* graph, int n){
  int* dist = malloc(n*n*sizeof(int));
  float l = 0;
  for(int idx = 0; idx<n*n; idx++){
    minPathLen(graph,dist,n,idx);
    for(int i = 0; i<n*n; i++) l = dist[i] + l;
  }
  free(dist);
  return l/(n*n*(n*n-1));
}

/* nonVaccinatorCount() suma 1 en la posicion i de vacAcum si el agente i de
  lattice es vacunador */

int nonVaccinatorCount(agent* lattice, int n, int* nonVacAcum){
  int f;
  for(int idx = 0; idx < n*n; idx++){
    f = lattice[idx].f;
    if(lattice[idx].feat[f-1] == 1) nonVacAcum[idx]++;
  }
  return 0;
}

/* nonVaccinatorTotal() simplemente cuenta la masa de no vacunadores */

int nonVaccinatorTotal(agent* lattice, int n){
  int nonVacTot = 0;
  int f;
  for(int idx = 0; idx < n*n; idx++){
    f = lattice[idx].f;
    nonVacTot = nonVacTot + lattice[idx].feat[f-1];
  }
  return nonVacTot;
}

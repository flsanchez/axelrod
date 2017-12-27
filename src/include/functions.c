#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "agent.h"
#include "graph.h"
#include "functions.h"

/* minDist() devuelve, dada una lista con las distancias y si esta marcado o no
  el vertice, el indice del vertice que tiene la minima distancia */
int minDist(int* dist, int* mark, int n){
  int minDistVal = INT_MAX;
  int minIdx = 0;
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
  for(int idx = 0; idx < n*n; idx++){
    if(lattice[idx].vacc == 0) nonVacAcum[idx]++;
  }
  return 0;
}

/* nonVaccinatorTotal() simplemente cuenta la masa de no vacunadores */

int nonVaccinatorTotal(agent* lattice, int n){
  int nonVacTot = 0;
  for(int idx = 0; idx < n*n; idx++){
    if(lattice[idx].vacc == 0) nonVacTot++;
  }
  return nonVacTot;
}

/* nonVaccinatorList() devuelve la cantidad de no vacunados y en una lista que
  se pasa como argumento se llena las posiciones de los no vacunadores */

int nonVaccinatorList(agent* lattice, int n, int** nonVaccList){
  int nonVacTot = nonVaccinatorTotal(lattice,n);
  int nonVacIdx = 0;
  *nonVaccList = malloc(nonVacTot*sizeof(int));
  for(int idx = 0; idx < n*n; idx++){
    if(lattice[idx].vacc == 0){
      (*nonVaccList)[nonVacIdx] = idx;
      nonVacIdx++;
    }
  }
  return nonVacTot;
}

// sqDistij() calcula la distancia cuadrada entre dos agentes i,j de la red

int sqDistij(int i, int j, int n){
  int dist, ix,iy, jx,jy;
  ix = i%n;
  iy = i/n;
  jx = j%n;
  jy = j/n;
  dist = (ix-jx)*(ix-jx) + (iy-jy)*(iy-jy);
  return dist;
}

/* cutDistantLinks() corta los links de distancia mayor que la distancia cuadra-
  da dist2 para cada agente en el grapho */

int cutDistantLinks(vertex* graph, int n, int dist2){
  int nEdges, nRewire, idxAux;
  for(int idx = 0; idx < n*n; idx++){
    nEdges = graph[idx].nEdges;
    nRewire = graph[idx].nRewire;
    // si hay links de rewire, me fijo de cortar estos primero
    if(nRewire > 0){
      for(int idxRew = 0; idxRew < nRewire; idxRew++){
        idxAux = graph[idx].rewire[idxRew]; //indice del vecino
        // si la distancia es mayor, corto el link, tanto rewire como normal
        if(sqDistij(idx,idxAux,n)>dist2){
          graphRewireRm(graph, idx, idxAux);
          graphEdgesRm(graph, idx, idxAux);
        }
      }
    }
    else{ // si no es hay links de rewire
      for(int idxEdges = 0; idxEdges < nEdges; idxEdges++){
        idxAux = graph[idx].edges[idxEdges]; //indice del vecino
        // si la distancia es mayor, corto el link
        if(sqDistij(idx,idxAux,n)>dist2) graphEdgesRm(graph, idx, idxAux);
      }
    }
  }
  return 0;
}

/* meanCalc() calcula el valor medio de un vector */

float meanCalc(int* vector, int n){
  float res = 0;
  for(int idx = 0; idx < n; idx++) res = res + vector[idx];
  return res/n;
}

/* stDevCalc() calcula y devuelve el desvio estandar de un vector y el valor
  medio por referencia */

float stDevCalc(int* vector, int n, float* mean){
  float res = 0;
  *mean = meanCalc(vector,n);
  for(int idx = 0; idx < n; idx++){
    res = res + (vector[idx]-*mean)*(vector[idx]-*mean);
  }
  return sqrt(res/n);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "agent.h"
#include "graph.h"
#include "misc.h"
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
  da dist2 para cada agente en el grapho, y devuelve cuantos links corto */

int cutDistantLinks(vertex* graph, int n, int dist2){
  int nRewire, idxAux;
  int cont = 0;
  for(int idx = 0; idx < n*n; idx++){
    nRewire = graph[idx].nRewire;
    // si hay links de rewire, me fijo de cortar estos primero
    if(nRewire > 0){
      int idxRew = 0;
      while(idxRew < graph[idx].nRewire){
        idxAux = graph[idx].rewire[idxRew]; //indice del vecino
        // si la distancia es mayor, corto el link, tanto rewire como normal
        // y no incremento idxRew
        if(sqDistij(idx,idxAux,n)>dist2){
          graphRewireRm(graph, idx, idxAux);
          graphEdgesRm(graph, idx, idxAux);
          cont++;
        }
        else idxRew++;
      }
    }
    else{ // si no hay links de rewire
      int idxEdges = 0;
      while(idxEdges < graph[idx].nEdges){
        idxAux = graph[idx].edges[idxEdges]; //indice del vecino
        // si la distancia es mayor, corto el link
        if(sqDistij(idx,idxAux,n)>dist2){
          graphEdgesRm(graph, idx, idxAux);
          cont++;
        }
        else idxEdges++;
      }
    }
  }
  return cont;
}

/* NofDistantLinks devuelve el numero de links a distancia dist2 que tiene el
  grafo graph */

int NofDistantLinks(vertex* graph, int n, int dist2){
  vertex* graphAux;
  graphCopy(graph, n, &graphAux);
  // calculo la cantidad de links totales
  int nLinksTot = cutDistantLinks(graphAux, n, dist2);
  graphFree(graphAux,n);
  free(graphAux);
  return nLinksTot;
}

/* listDistantLinks guarda en 2 vectores src y dist los correspondientes links
  que se encuentren a una distancia dist2 */

int listDistantLinks(vertex* graph, int n, int dist2, int** src, int** dest){
  // obtengo la cantidad de links totales, para poder asignar las listas
  int nLinksTot = NofDistantLinks(graph, n, dist2);
  // alloco la memoria para src y dest
  *src = malloc(sizeof(int)*nLinksTot);
  *dest = malloc(sizeof(int)*nLinksTot);
  // hago la copia sobre el grapho para poder laburar tranquilo
  vertex* graphAux;
  graphCopy(graph, n, &graphAux);
  // hago lo mismo que cutDistantLinks, pero ademas grabo
  int nRewire, idxAux;
  int cont = 0;
  for(int idx = 0; idx < n*n; idx++){
    nRewire = graphAux[idx].nRewire;
    // si hay links de rewire, me fijo de cortar estos primero
    if(nRewire > 0){
      int idxRew = 0;
      while(idxRew < graphAux[idx].nRewire){
        idxAux = graphAux[idx].rewire[idxRew]; //indice del vecino
        // si la distancia es mayor, corto el link, tanto rewire como normal
        // y no incremento idxRew
        if(sqDistij(idx,idxAux,n)>dist2){
          graphRewireRm(graphAux, idx, idxAux);
          graphEdgesRm(graphAux, idx, idxAux);
          (*src)[cont] = idx;
          (*dest)[cont] = idxAux;
          cont++;
        }
        else idxRew++;
      }
    }
    else{ // si no es hay links de rewire
      int idxEdges = 0;
      while(idxEdges < graphAux[idx].nEdges){
        idxAux = graphAux[idx].edges[idxEdges]; //indice del vecino
        // si la distancia es mayor, corto el link
        if(sqDistij(idx,idxAux,n)>dist2){
          graphEdgesRm(graphAux, idx, idxAux);
          (*src)[cont] = idx;
          (*dest)[cont] = idxAux;
          cont++;
        }
        else idxEdges++;
      }
    }
  }
  graphFree(graphAux,n);
  free(graphAux);
  return nLinksTot;
}

/* cutNDistantLinks corta nLinks de los links totales, devuelve 1 en el caso de
  que se este pidiendo cortar mas links que los totales */

int cutNDistantLinks(vertex* graph, int n, int dist2, int nLinks){
  // primero obtengo la lista de links distantes a dist2
  int* src;
  int* dest;
  int nSrcDest;
  nSrcDest = listDistantLinks(graph, n, dist2, &src, &dest);

  if(nLinks > nSrcDest) return 1;

  int idxSrc, idxDest, nRewire;
  // mezclo los arrays
  shuffleArrays(src, dest, nSrcDest);
  // ahora arranco con el proceso de corte
  for(int i = 0; i < nLinks; i++){
    idxSrc = src[i];
    idxDest = dest[i];
    nRewire = graph[idxSrc].nRewire;
    // si es de rewire, corto primero el links de rewire
    if(nRewire > 0) graphRewireRm(graph, idxSrc, idxDest);
    graphEdgesRm(graph, idxSrc, idxDest);
  }
  free(src);
  free(dest);
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

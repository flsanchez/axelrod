#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* vertexInit() inicializa los atributos del vertice idx y aloca la memoria
correspondiente */

int vertexInit(vertex* graph, int idx, int nEdges, int nRewire){
  graph[idx].nEdges = nEdges;
  graph[idx].edges = (int*) malloc(nEdges*sizeof(int));
  graph[idx].nRewire = nRewire;
  graph[idx].rewire = (int*) malloc(nRewire*sizeof(int));
  return 0;
}

/* vertexAssignNumberEdges() se encarga de decir cuantas conexiones
corresponden al vertice idx, dependiendo de si inicialmente el mismo
se encuentra en una punta, un borde o el interior del grafo */

int vertexAssignNumberEdges(int idx, int n, int nEdges){
  int i = idx/n;
  int j = idx%n;
  int puntas = 2;
  int bordes = 3;
  int interior = nEdges;
  if( (i == 0 || i == n-1) && (j == 0 || j == n-1) ) return puntas;
  else if( i == 0 || i == n-1 || j == 0 || j == n-1 ) return bordes;
  else return interior;
}

/* vertexFillEdges() llena el vector de conexiones del vertice, en funcion
de la topologia que se programe */

int vertexFillEdges(int* edges, int n, int idx){

  int i = idx/n;
  int j = idx%n;

  if(i == 0){
    if(j == 0){
      edges[0] = idx + 1;
      edges[1] = idx + n;
    }
    else if (j == n-1){
      edges[0] = idx - 1;
      edges[1] = idx + n;
    }
    else{
      edges[0] = idx - 1;
      edges[1] = idx + 1;
      edges[2] = idx + n;
    }
  }
  else if(i == n-1){
    if(j == 0){
      edges[0] = idx + 1;
      edges[1] = idx - n;
    }
    else if (j == n-1){
      edges[0] = idx - 1;
      edges[1] = idx - n;
    }
    else{
      edges[0] = idx - 1;
      edges[1] = idx + 1;
      edges[2] = idx - n;
    }
  }
  else{
    edges[0] = idx - n;
    edges[1] = idx - 1;
    edges[2] = idx + 1;
    edges[3] = idx + n;
  }
  return 0;
}

/* vertexFillRewire() llena el vector de rewire dependiendo de cuantas
conexiones aleatorias se hayan determinado */

int vertexFillRewire(int* rewire, int n, int idx){
  return 0;
}

/* vertexEdgesPrint() imprime todas las conexiones del vertice idx */

int vertexEdgesPrint(vertex* graph, int n, int idx){
  int nEdges = graph[idx].nEdges;
  printf("Vertex N. %d:\nEdges: [ ",idx);
  for(int i = 0; i<nEdges; i++) printf("%d ", graph[idx].edges[i]);
  printf("]\n");
  return 0;
}

/* vertexEdgesAdd() añade un elemento a la lista de edges del vertice
realocando la memoria en el medio y cambiando el atributo del numero de
conexiones */

int vertexEdgesAdd(vertex* graph, int idx, int edgeVal){
  return 0;
}

/* graphInit() inicializa todos los atributos de cada uno de los vertices del
grafo vertex* graph */

int graphInit(vertex* graph, int n, int nEdges, int nRewire){

  int nEdgesReal;
  for(int idx = 0; idx < n*n ; idx++){
    nEdgesReal = vertexAssignNumberEdges(idx, n, nEdges);
    vertexInit(graph, idx, nEdgesReal, nRewire);
  }

  return 0;
}

/* graphFill() se encarga de llenar el vector de conexiones y EL REWIRE para
cada uno de los vertices contenidos en el grafo */

int graphFill(vertex* graph, int n){
  for(int idx = 0; idx < n*n ; idx++){
    vertexFillEdges(graph[idx].edges, n, idx);
    //FALTA LLENAR REWIRE
  }
  return 0;
}

/* graphEdgesPrint() imprime el vector de conexiones para cada uno de los
vertices */

int graphEdgesPrint(vertex* graph, int n){
  for(int i = 0; i<n*n; i++) vertexEdgesPrint(graph,n,i);
  return 0;
}

/* graphFree() libera la memoria del grafo, liberando todos los mallocs hechos
en cada uno de los vertices primero */

int graphFree(vertex* graph, int n){
  for(int i = 0; i < n*n; i++){
    free(graph[i].edges);
    free(graph[i].rewire);
  }
  free(graph);
  return 0;
}

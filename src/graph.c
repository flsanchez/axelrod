#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int vertexInit(vertex* graph, int idx, int nEdges, int nRewire){
  graph[idx].nEdges = nEdges;
  graph[idx].edges = (int*) malloc(nEdges*sizeof(int));
  graph[idx].nRewire = nRewire;
  graph[idx].rewire = (int*) malloc(nRewire*sizeof(int));
  return 0;
}

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

int vertexFillEdges(int* edges, int n, int idx){
  int i = idx/n;
  int j = idx%n;
  int cont = 0;
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

int vertexFillRewire(int* rewire, int n, int idx){
  return 0;
}

int vertexEdgesPrint(vertex* graph, int n, int idx){
  int nEdges = graph[idx].nEdges;
  printf("Vertex N. %d:\nEdges: [ ",idx);
  for(int i = 0; i<nEdges; i++) printf("%d ", graph[idx].edges[i]);
  printf("]\n");
  return 0;
}

int vertexEdgesAdd(vertex* graph, int idx, int edgeVal){
  return 0;
}

int graphInit(vertex* graph, int n, int nEdges, int nRewire){

  int nEdgesReal;
  for(int idx = 0; idx < n*n ; idx++){
    nEdgesReal = vertexAssignNumberEdges(idx, n, nEdges);
    vertexInit(graph, idx, nEdgesReal, nRewire);
  }

  return 0;
}

int graphFill(vertex* graph, int n){
  for(int idx = 0; idx < n*n ; idx++){
    vertexFillEdges(graph[idx].edges, n, idx);
    //FALTA LLENAR REWIRE
  }
  return 0;
}

int graphEdgesPrint(vertex* graph, int n){
  for(int i = 0; i<n*n; i++) vertexEdgesPrint(graph,n,i);
  return 0;
}

int graphFree(vertex* graph, int n){
  for(int i = 0; i < n*n; i++){
    free(graph[i].edges);
    free(graph[i].rewire);
  }
  free(graph);
  return 0;
}

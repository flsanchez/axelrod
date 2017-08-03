#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex
{
  //struct agent* agent;//agente del nodo
  int nEdges;  //numero de conexiones
  int* edges;  //lista de adyacencias, con los indices de los vecinos en cada
               //componente
  int nRewire; //numero de conexiones que admiten rewire
  int *rewire; //vector de rewire, contiene los indices del vector de edges que
               //admiten rewire
} vertex;

int vertexCreate(vertex* graph, int idx, int nEdges, int nRewire);
int vertexFillEdges(int* edges, int n, int idx);
int vertexAssignNumberEdges(int idx, int n, int nEdges);
int vertexEdgesPrint(vertex* graph, int n, int idx);
int vertexEdgesAdd(vertex* graph, int idx, int edgeVal);
int graphFill(vertex* graph, int n, int nEdges, int nRewire);
int graphEdgesPrint(vertex* graph, int n);
int graphFree(vertex* graph, int n);



#endif

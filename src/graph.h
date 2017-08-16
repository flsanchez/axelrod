#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex
{
  int nEdges;  //numero de conexiones
  int* edges;  //lista de adyacencias, con los indices de los vecinos en cada
               //componente
  int nRewire; //numero de conexiones que admiten rewire
  int *rewire; //vector de rewire, contiene los edges que admiten rewire
} vertex;

int vertexInit(vertex* graph, int idx, int nEdges, int nRewire);
int vertexEdgesAssignNumber(int idx, int n, int neigOrd);
int vertexEdgesFill(int* edges, int n, int idx, int neigOrd);
int vertexRewireFill(vertex* graph, int idx);
int vertexEdgesPrint(vertex* graph, int idx);
int vertexRewirePrint(vertex* graph, int idx);
int vertexEdgeIsConnected(vertex* graph, int src, int dest);
int vertexRewireIsConnected(vertex* graph, int src, int dest);
int vertexEdgesAdd(vertex* graph, int src, int dest);
int vertexEdgesRm(vertex* graph, int src, int dest);
int vertexRewireAdd(vertex* graph, int src, int dest);
int vertexRewireRm(vertex* graph, int src, int dest);
int graphInit(vertex* graph, int n, int nRewire, int neigOrd);
int graphFill(vertex* graph, int n, int neigOrd);
int graphEdgesAdd(vertex* graph, int src, int dest);
int graphEdgesRm(vertex* graph, int src, int dest);
int graphRewireAdd(vertex* graph, int src, int dest);
int graphRewireRm(vertex* graph, int src, int dest);
int graphEdgesPrint(vertex* graph, int n);
int graphPrintToFile(vertex* graph, int n, FILE *fs);
int graphRewirePrint(vertex* graph, int n);
int graphFree(vertex* graph, int n);

#endif

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

int vertexEdgesInit(vertex* graph, int idx, int nEdges);
int vertexRewireInit(vertex* graph, int idx, int nRewire);
int vertexEdgesAssignNumber(int idx, int n, int neigOrdEdges);
int vertexEdgesFill(vertex* graph, int n, int* neigArray,
                    int nNeigArray, int idx);
int vertexRewireFill(vertex* graph, int idx, int* rewArray,
                    int nRewArray, int nRewire);
int vertexEdgesPrint(vertex* graph, int idx);
int vertexRewirePrint(vertex* graph, int idx);
int vertexEdgeIsConnected(vertex* graph, int src, int dest);
int vertexRewireIsConnected(vertex* graph, int src, int dest);
int vertexEdgesAdd(vertex* graph, int src, int dest);
int vertexEdgesRm(vertex* graph, int src, int dest);
int vertexRewireAdd(vertex* graph, int src, int dest);
int vertexRewireRm(vertex* graph, int src, int dest);

int graphInit(vertex* graph, int n);
int graphEdgesInit(vertex* graph, int n);
int graphRewireInit(vertex* graph, int n);
int graphEdgesFill(vertex* graph, int n, int neigOrdEdges);
int graphRewireFill(vertex* graph, int n, int nEdgeRew,
                          int nRewire, int neigOrdEdges, int neigOrdRewire);
int graphFill(vertex* graph, int n, int nEdgeRew, int nRewire,
                                        int neigOrdEdges, int neigOrdRewire);
int graphEdgesAdd(vertex* graph, int src, int dest);
int graphEdgesRm(vertex* graph, int src, int dest);
int graphRewireAdd(vertex* graph, int src, int dest);
int graphRewireRm(vertex* graph, int src, int dest);
int graphEdgesAddNRand(vertex* graph, int n, int nRandEdges);
int graphRewireAddNRand(vertex* graph, int n, int nRandRewire);
int graphEdgesPrint(vertex* graph, int n);
int graphRewirePrint(vertex* graph, int n);
int graphPickPassiveNeig(vertex* graph, int i);
int graphPickPassiveNotNeig(vertex* graph, int n, int i);
int graphSaveToFile(vertex* graph, int n, FILE* fs);
int graphLoadFromFile(vertex** graph, FILE* fs);
int graphCompare(vertex* graph1, vertex* graph2, int n);
int graphEdgesFree(vertex* graph, int n);
int graphRewireFree(vertex* graph, int n);
int graphFree(vertex* graph, int n);

#endif

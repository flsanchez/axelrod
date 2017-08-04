#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "agent.h"
#include "axelrod.h"

int main(){

  srand(time(NULL));

  int n = 3;
  vertex* graph = (vertex*) malloc(n*n*sizeof(vertex));
  int nEdges = 4;
  int nRewire = 0;
  int idx = 4;
  int neigOrd = 2;
  graphInit(graph, n, nRewire, neigOrd);
  graphFill(graph, n, neigOrd);
  graphEdgesPrint(graph, n);
  printf("El vecino al azar del agente %d es %d\n", idx, pickPassive(graph,idx));
  graphFree(graph,n);
}

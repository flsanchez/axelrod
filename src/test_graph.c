#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "axelrod.h"

int main(){

  srand(time(NULL));

  int n = 3;
  agent* lattice = (agent*)malloc(n*n*sizeof(agent));
  vertex* graph = (vertex*)malloc(n*n*sizeof(vertex));
  int f = 10;
  int q = 5;
  int nEdges = 4;
  int nRewire = 0;
  int idx = 4;
  latticeFill(lattice,n,f,q);
  graphFill(graph, n, nEdges, nRewire);
  graphEdgesPrint(graph, n);
  printf("El vecino al azar del agente %d es %d\n", idx, pickPassive(graph,idx));
  //agentPrint(lattice, n, idx);
  latticeFree(lattice,n);
  graphFree(graph,n);
}

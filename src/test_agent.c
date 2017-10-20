#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/agent.h"
#include "include/graph.h"
#include "include/label.h"
#include "include/axelrod.h"

/* este main hace una corrida simple de un axelrod y entrega el Smax y la
cantidad de pasos para llegar al stop por pantalla */

int main(){

  int n = 50;
  int f = 11;
  int q = 80;
  int qF = 2;
  int neigOrdEdges = 2;
  int neigOrdRewire = 2;
  int nRewire = 1;
  int nEdgeRew = 0*n*n;
  int nStub = 1;
  FILE *fs;

  srand(time(NULL));

  agent* lattice = (agent*) malloc(n * n * sizeof(agent));
  agent* lattice2;
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));

  int* idxList = malloc(sizeof(int));
  idxList[0] = 3;

  latticeInit(lattice, n, f);
  latticeFill(lattice, n, q, qF);
  latticeSetStubFromArray(lattice,n,idxList,nStub);
  graphInit(graph, n);
  graphFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);

  fs = fopen("test.lat","w");
  latticeSave(lattice, n, fs);
  fclose(fs);
  fs = fopen("test.lat","r");
  int N = latticeLoad(&lattice2, fs);
  fclose(fs);
  fs = fopen("test2.lat","w");
  latticeSave(lattice2, n, fs);
  fclose(fs);

  printf("Las redes son %d\n", latticeCompare(lattice, lattice2, n));
  printf("N = %d\n", N);

  latticeFree(lattice, n);
  free(lattice);
  latticeFree(lattice2, n);
  free(lattice2);
  graphFree(graph, n);
  free(graph);

  return 0;
}

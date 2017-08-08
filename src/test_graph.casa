#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "agent.h"
#include "misc.h"
#include "axelrod.h"

int main(){

  srand(time(NULL));

  int n = 3;
  vertex* graph = (vertex*) malloc(n*n*sizeof(vertex));
  int nRewire = 2;
  int t = time(NULL);
  int idx = 10;
  int neigOrd = 2;
  graphInit(graph, n, nRewire, neigOrd);
  printf("Attempts: %d\n", graphFill(graph, n, neigOrd));

  graphRewirePrint(graph,n);

  t = time(NULL)-t;
  printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", t/3600, (t/60)%60, t%60);
  graphFree(graph,n);
}

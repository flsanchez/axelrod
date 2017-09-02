#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "functions.h"

int main(){

  srand(time(NULL));

  int n = 50;
  int nRewire = 1;
  int t = time(NULL);
  int idx = 10;
  int neigOrdEdges = 2;
  int neigOrdRewire = 3;
  int nEdgeRew = n*n;
  char name[100];
  int cont;
  FILE *fs;


  vertex* graph = (vertex*) malloc(n*n*sizeof(vertex));
  for(int i = 0; i<100; i++){
    graphInit(graph, n, neigOrdEdges);
    graphEdgesFill(graph, n, neigOrdEdges);
    graphRewireFillNeig(graph, n, nEdgeRew, nRewire, neigOrdEdges);
    fs = fopen("net.net","w");
    graphPrintToFile(graph, n, fs);
    fclose(fs);
    graphFree(graph,n);
  }

  free(graph);

  /*for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++) printf("%d ", vertexEdgesAssignNumber(i*n+j,n,neigOrdRewire));
    printf("\n");
  }*/


  // fs = fopen("net.txt","w");
  // graphPrintToFile(graph, n, fs);
  // fclose(fs);
  //
  // printf("%f\n",avMinPathLen(graph, n));
  //
  // t = time(NULL)-t;
  // printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", t/3600, (t/60)%60, t%60);
  //
  // //free(dist);
  // //graphFree(graph,n);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"
#include "axelrod.h"

/* este main hace una corrida simple de un axelrod y entrega el Smax y la
cantidad de pasos para llegar al stop por pantalla */

int main(){

  int n = 50;
  int f = 10;
  int q = 10;
  int neigOrd = 2;
  int nRewire = 1;
  int nmbrOfRew = 0;
  int nEdgeRew = 0;
  int niter = 50E6;
  int paso = n*n;
  int frag,max;
  int end = 0;
  FILE *fs;
  char name[100];

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));

  latticeInit(lattice, n, f, q);
  latticeFill(lattice, n, q);
  graphInit(graph, n, neigOrd);
  graphFill(graph, n, neigOrd, nEdgeRew, nRewire);

  fs = fopen("netIni.txt","w");
  graphPrintToFile(graph,n,fs);
  fclose(fs);

  int i = 0;
  int stop = 0;
  int t = time(NULL);
  while(stop == 0){

    nmbrOfRew = nmbrOfRew + step(graph,lattice,n);

    if(i%paso==0){
      stop = stopReached(graph,lattice,n);
      if(stop == 1 && end == 0) end = i;
    }

    i++;

  }
  frag = latticeLabel(graph, lattice, n);
  max = maxCluster(lattice, NULL, n, frag);
  t = time(NULL)-t;
  printf("Smax = %d; t = %d; pasos = %d\n",max,t,i-1);

  fs = fopen("netFin.txt","w");
  graphPrintToFile(graph,n,fs);
  fclose(fs);

  latticeFree(lattice, n);
  graphFree(graph, n);

  return 0;
}

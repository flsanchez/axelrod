#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"
#include "axelrod.h"


int main(){

  int n = 50;
  int f = 10;
  int q = 100;
  int neigOrd = 2;
  int nRewire = 1;
  int niter = 20E6;
  int paso = niter/100;
  int frag,max;
  FILE *fs;
  char name[100];

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));

  latticeInit(lattice, n, f, q);
  latticeFill(lattice, n, q);
  graphInit(graph, n, nRewire, neigOrd);
  graphFill(graph, n, neigOrd);

  for(int i=0;i<niter;i++){

    if(i%paso==0){
      printf("Paso: %d\n",i);
      sprintf(name,"%d.txt",i/paso);
      fs = fopen(name,"w");
      fprintf(fs,"# paso\n# %d\n", paso);
      latticePrintToFile(lattice,n,fs);
      fclose(fs);
      frag = latticeLabel(lattice,n);
      max = maxCluster(lattice,n,frag);
      printf("%d\n",max);
    }

    //printf("Paso: %d\n",i);

    step(graph,lattice,n);

  }

  latticeFree(lattice, n);
  graphFree(graph, n);

  return 0;
}

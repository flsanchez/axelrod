#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "axelrod.h"
#include "label.h"

int main(){

  int n = 50;
  int f = 10;
  int niter = n*n*60000;
  int prom = 1;
  int *Sprom = malloc(prom*sizeof(int));
  int frag;
  int max;
  int nEdges = 4;
  int nRewire = 0;
  FILE *fs;
  char name[100];
  int qlen = 2;
  int *qVector = malloc(qlen*sizeof(int));
  int q;
  for(int i = 0; i<qlen; i++) qVector[i] = 2*i + 1;
  int tLoop,tTotal,tEst;
  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  latticeInit(lattice, n, f, q);
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));
  graphInit(graph, n, nEdges, nRewire);
  graphFill(graph, n);

  tTotal = time(NULL);

  for(int j = 0; j<qlen; j++){

    q = qVector[j];

    for(int i = 0; i<prom; i++){

      tLoop = time(NULL);
      printf("q = %d, prom = %d \n",q,i);
      latticeFill(lattice, n);
      for(int j=0; j<niter; j++) step(graph,lattice,n);
      frag = latticeLabel(lattice,n);
      max = maxCluster(lattice,n,frag);
      printf("%d\n",max);
      Sprom[i] = max;
      tLoop = time(NULL)-tLoop;
      printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", tLoop/3600, (tLoop/60)%60, tLoop%60);
      tEst = tLoop*prom*qlen - (time(NULL) - tTotal);
      printf("Tiempo estimado: %d:%d:%d\n", tEst/3600, (tEst/60)%60, tEst%60);
    }

    sprintf(name,"q_%d.txt",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q niter\n# %d %d %d %d\n",n,f,q,niter);
    for(int i = 0; i<prom; i++) fprintf(fs,"%d\n", Sprom[i]);
    fclose(fs);

  }
  tTotal = time(NULL) - tTotal;
  printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", tTotal/3600, (tTotal/60)%60, tTotal%60);

  latticeFree(lattice,n);
  graphFree(graph,n);
  free(Sprom);
  free(qVector);
  return 0;

}

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
  int niter = 30E6;
  int prom = 50;
  int *Sprom = malloc(prom*sizeof(int));
  int frag;
  int max;
  int neigOrd = 2;
  int nRewire = 1;
  int* term = malloc(prom*sizeof(int));
  FILE *fs;
  char name[100];
  int qlen = 120;
  int *qVector = malloc(qlen*sizeof(int));
  int q;
  for(int i = 0; i<qlen; i++) qVector[i] = 10*(i+1);
  int tLoop,tTotal;
  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  latticeInit(lattice, n, f, q);
  int k,stop;
  int paso = 1E3;

  tTotal = time(NULL);

  for(int j = 0; j<qlen; j++){

    q = qVector[j];

    for(int i = 0; i<prom; i++){

      tLoop = time(NULL);

      printf("q = %d, prom = %d \n",q,i);
      vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));
      graphInit(graph, n, nRewire, neigOrd);
      graphFill(graph, n, neigOrd);
      latticeFill(lattice, n, q);

      stop = 0;
      k = 0;
      while(stop == 0){
        step(graph,lattice,n);
        if(k%paso == 0) stop = stopReached(graph,lattice,n);
        k++;
      }

      term[i] = k-1;
      frag = latticeLabel(lattice,n);
      max = maxCluster(lattice,n,frag);
      Sprom[i] = max;
      printf("Smax = %d; Pasos = %d\n",max,k-1);
      tLoop = time(NULL)-tLoop;
      printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", tLoop/3600, (tLoop/60)%60, tLoop%60);
      graphFree(graph,n);

    }

    sprintf(name,"q_%d.txt",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q niter\n# %d %d %d %d\n",n,f,q,niter);
    for(int i = 0; i<prom; i++) fprintf(fs,"%d %d\n", Sprom[i],term[i]);
    fprintf(fs,"# Smax pasos\n");
    fclose(fs);

  }
  tTotal = time(NULL) - tTotal;
  printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", tTotal/3600, (tTotal/60)%60, tTotal%60);

  latticeFree(lattice,n);

  free(Sprom);
  free(qVector);
  free(term);
  return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"
#include "label.h"

int main(){

  int n = 50;
  int f = 10;
  int niter = n*n*60000;
  int prom = 20;
  int *Sprom = malloc(prom*sizeof(int));
  int frag;
  int max;
  FILE *fs;
  char name[100];
  int qlen = 50;
  int *qVector = malloc(qlen*sizeof(int));
  int q;
  for(int i = 0; i<qlen; i++) qVector[i] = 2*i+3;

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  for(int j = 0; j<qlen; j++){

    q = qVector[j];

    for(int i = 0; i<prom; i++){

      printf("q = %d, prom = %d \n",q,i);
      latticeFill(lattice, n, f, q);
      for(int j=0; j<niter; j++) step(lattice,n);
      frag = latticeLabel(lattice,n);
      max = maxCluster(lattice,n,frag);
      printf("%d\n",max);
      Sprom[i] = max;

    }

    sprintf(name,"q_%d.txt",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q niter\n# %d %d %d %d\n",n,f,q,niter);
    for(int i = 0; i<prom; i++) fprintf(fs,"%d\n", Sprom[i]);
    fclose(fs);

  }

  freeAll(lattice,n);
  free(Sprom);
  free(qVector);
  return 0;

}

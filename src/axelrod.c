#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int agentCreate(int **lattice, int idx, int f){

  lattice[idx] = malloc(f*sizeof(int));

  return 0;
}

int agentFill(int *feat, int f, int q){

  for(int i=0; i<f; i++) {
    feat[i] = (int) (q * ((float) rand() / (float) RAND_MAX));
  }

  return 0;
}

int latticeFill(int **lattice, int n, int f, int q){

  for(int i=0; i<n; i++){
    agentCreate(lattice, i, f);
    agentFill(lattice[i], f, q);
  }

  return 0;
}

int agentPrint(int **lattice, int n, int f, int idx){

  int *aux = lattice[idx];

  for(int i=0; i<f; i++) printf("Trait %d = %d\n",i,aux[i]);

  return 0;

}

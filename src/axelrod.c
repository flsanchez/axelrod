#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int agentCreate(agent *lattice, int idx, int f, int q){

  lattice[idx].f = f;
  lattice[idx].q = q;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));

  return 0;

}

int agentFill(int *feat, int f, int q){

  for(int i=0; i<f; i++) {
    feat[i] = (int) (q * ((float) rand() / (float) RAND_MAX));
  }

  return 0;
}

int latticeFill(agent *lattice, int n, int f, int q){

  for(int i=0; i<n*n; i++){
    agentCreate(lattice, i, f, q);
    agentFill(lattice[i].feat, lattice[i].f, lattice[i].q);
  }

  return 0;
}

int agentPrint(agent *lattice, int n, int idx){

  for(int i=0; i<lattice[idx].f; i++){
    printf("Trait %d = %d\n",i,lattice[idx].feat[i]);
  }

  return 0;

}

int free_all(agent *lattice, int n){

  for(int i=0;i<n*n;i++) free(lattice[i].feat);
  free(lattice);

  return 0;

}

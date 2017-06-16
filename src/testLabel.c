#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"
#include "label.h"

int main(){

  int n = 5;
  int f = 4;
  int q = 3;
  int niter = 500;
  int paso = 100;
  FILE *fs;
  char name[100];

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  latticeFill(lattice, n, f, q);

  /*latticePrintToFile(lattice,n,NULL);
  printf("\n");

  latticePrintLinks(lattice,n);
  printf("\n");

  latticeLabel(lattice,n);
  latticePrintLabels(lattice,n);*/

  printf("Hago %d pasos\n",niter);

  for(int i=0;i<niter;i++) step(lattice,n);

  latticePrintToFile(lattice,n,NULL);
  printf("\n");

  int frag = latticeLabel(lattice,n);
  latticePrintLabels(lattice,n);

  printf("Cluster mas grande: %d\n", maxCluster(lattice,n,frag));

  freeAll(lattice, n);

  return 0;
}

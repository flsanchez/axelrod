#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 5;
  int f = 5;
  int q = 10;
  int niter = 10000;

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  latticeFill(lattice, n, f, q);

  for(int i=0;i<niter;i++){
    step(lattice,n);
    if(i%1000 == 0){
      printf("Paso Numero %d: \n",i);
      latticePrint(lattice,n);
      printf("\n\n");
    }
  }
  printf("Paso Numero %d: \n",niter);
  latticePrint(lattice,n);
  printf("\n\n");


  freeAll(lattice, n);

  return 0;
}

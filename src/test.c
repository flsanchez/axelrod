#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 10;
  int f = 5;
  int q = 10;
  int niter = 100000;
  int paso = 100;
  FILE *fs;
  char name[100];

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  latticeFill(lattice, n, f, q);

  for(int i=0;i<niter;i++){

    if(i%paso==0){
      printf("Paso: %d\n",i);
      sprintf(name,"%d.txt",i/paso);
      fs = fopen(name,"w");
      latticePrintToFile(lattice,n,fs);
      fclose(fs);
    }

    step(lattice,n);

  }

  freeAll(lattice, n);

  return 0;
}

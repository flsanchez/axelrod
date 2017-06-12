#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 10;
  int f = 5;
  int q = 10;
  int niter = 100000;
  FILE *fs;
  char name[100];

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  latticeFill(lattice, n, f, q);

  for(int i=0;i<niter;i++){

    if(i%2000==0){
      sprintf(name,"test%f.txt",(float)i/(float)niter);
      fs = fopen(name,"w");
      latticePrintToFile(lattice,n,fs);
      fclose(fs);
    }

    step(lattice,n);

  }

  freeAll(lattice, n);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 2;
  int f = 4;
  int q = 10;

  srand(time(NULL));

  int **lattice = malloc(n * n * sizeof(int*));

  latticeFill(lattice, n, f, q);

  for(int i=0;i<n*n;i++){

    printf("Agent N. %d:\n",i);
    agentPrint(lattice, n, f, i);

  }

  return 0;
}

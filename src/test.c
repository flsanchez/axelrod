#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 3;
  int f = 4;
  int q = 10;

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));

  latticeFill(lattice, n, f, q);

  for(int i=0;i<n*n;i++){

    printf("Agent N. %d:\n",i);
    agentPrint(lattice, n, i);

  }

  free_all(lattice, n);

  return 0;
}

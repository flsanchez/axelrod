#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int main(){

  int n = 2;
  int f = 2;
  int q = 10;

  srand(time(NULL));

  int **lattice = malloc(n*n*sizeof(int *));

  latticeFill(lattice, n, f, q);
  agentPrint(lattice, n, f, 0);

  return 0;
}

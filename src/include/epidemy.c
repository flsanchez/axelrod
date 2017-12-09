#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "epidemy.h"

int epidemyInit(epidemy* population, int idx, int nComp){
  population[idx].comp = malloc(nComp*sizeof(int));
  population[idx].comp[0] = 1; // pongo a susceptible
  //pongo a 0 los otros compartimientos
  for(int i = 1; i < nComp; i++) population[idx].comp[i] = 0;
  return 0;
}

int populationInit(epidemy* population, int n, int nComp){
  for(int idx = 0; idx < n; idx++) epidemyInit(population, idx, nComp);
  return 0;
}

int populationInitSEIR(epidemy* population, int n){
  return 0;
}

#ifndef EPIDEMY_H
#define EPIDEMY_H

typedef struct epidemy
{
  int nComp;  //tamaño del vector de compartimiento
  int* comp;  //vector que contiene el estado de cada compartimiento
} epidemy;

int epidemyInit(epidemy* population, int idx, int nComp);
int epidemyNCompNeig(epidemy* population, vertex* graph, int idx, int iComp);
int populationInit(epidemy* population, int n, int nComp);
int populationInitSEIR(epidemy* population, int n);
int populationNCompTotal(epidemy* population, int n, int iComp);
int populationNCompNeig(epidemy* population, vertex* graph, int* infArray,
                        int n, int iComp);
int stepSEIR(epidemy* population, vertex* graph, int n, float nuS, float nuE,
              float nuI, float dt);
int stopReachedSEIR(epidemy* population, int n);

#endif

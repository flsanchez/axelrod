#ifndef EPIDEMY_H
#define EPIDEMY_H

typedef struct epidemy
{
  int nComp;  //tamaño del vector de compartimiento
  int* comp;  //vector que contiene el estado de cada compartimiento
} epidemy;

int epidemyInit(epidemy* population, int idx, int nComp);
int epidemyCompNNeig(epidemy* population, vertex* graph, int idx, int iComp);
int populationInit(epidemy* population, int n, int nComp);
int populationInitSEIR(epidemy* population, int n);
int populationFillSEIRVacc(epidemy* population, agent* lattice, int n,
                          int* notRemoved);
int populationSEIRInfectMaxCluster(epidemy* population, vertex* graph,
                                  agent* lattice, int n, int nInf);
int populationSEIRInfectAtRand(epidemy* population,agent* lattice, int n,
                                int nInf, int* notRemoved, int massNonVacc);
int populationFillRand(epidemy* population, int n, int nComp);
int populationCompNTotal(epidemy* population, int n, int iComp);
int populationCompNNeig(epidemy* population, vertex* graph, int* infArray,
                        int n, int iComp);
int populationSaveToFile(FILE* fs, epidemy* population, int n);
int stepSEIR(epidemy* population, vertex* graph, int n, float nuS, float nuE,
              float nuI, float dt, int* notRemoved, int* lenNotRem);
int populationSEIRFullMaxCluster(vertex* graph, vertex* graphEpi, agent* lattice, int n,
                                int nInf, float nuS, float nuE, float nuI, float dt, int massNonVacc);
int populationSEIRFullAtRand(vertex* graphEpi, agent* lattice, int n,
                        int nInf, float nuS, float nuE, float nuI, float dt,
                        int massNonVacc);
int stopReachedSEIR(epidemy* population, int n);
int populationFree(epidemy* population, int n);

#endif

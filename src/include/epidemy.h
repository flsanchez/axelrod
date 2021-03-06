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
int populationFillSEIRVacc(epidemy* population, int* notRemoved, int lenNotRem);
int populationSEIRInfectFromList(epidemy* population, int n, int nInf,
                                  int* notRemoved, int lenNotRem);
int populationFillRand(epidemy* population, int n, int nComp);
int populationCompNTotal(epidemy* population, int n, int iComp);
int populationCompNNeig(epidemy* population, vertex* graph, int* infArray,
                        int n, int iComp);
int populationSaveToFile(FILE* fs, epidemy* population, int n);
int stepSEIR(epidemy* population, vertex* graph, int n, float nuS, float nuE,
              float nuI, float dt, int* notRemoved, int* lenNotRem);
int SEIRFull(vertex* graphEpi, int n, int* notRemoved, int massNonVacc,
            int* infectedList, int lenInf,
            int nInf, float nuS, float nuE, float nuI, float dt);
int stopReachedSEIR(epidemy* population, int n);
int populationFree(epidemy* population, int n);

#endif

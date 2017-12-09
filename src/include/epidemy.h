#ifndef EPIDEMY_H
#define EPIDEMY_H

typedef struct epidemy
{
  int nComp;  //tamaño del vector de compartimiento
  int* comp;  //vector que contiene el estado de cada compartimiento
} epidemy;

int epidemyInit(epidemy* population, int idx, int nComp);
int populationInit(epidemy* population, int n, int nComp);

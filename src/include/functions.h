#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int minDist(int* dist, int* mark, int n);
int minPathLen(vertex* graph, int* dist, int n, int src);
float avMinPathLen(vertex* graph, int n);

int clustCoeff(vertex* graph, int n);

int nonVaccinatorCount(agent* lattice, int n, int* nonVacAcum);
int nonVaccinatorTotal(agent* lattice, int n);

#endif

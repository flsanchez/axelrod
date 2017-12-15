#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// DIJKSTRA
int minDist(int* dist, int* mark, int n);
int minPathLen(vertex* graph, int* dist, int n, int src);
float avMinPathLen(vertex* graph, int n);

int clustCoeff(vertex* graph, int n);

int nonVaccinatorCount(agent* lattice, int n, int* nonVacAcum);
int nonVaccinatorTotal(agent* lattice, int n);

int sqDistij(int i, int j, int n);
int cutDistantLinks(vertex* graph, int n, int dist2);

float meanCalc(int* vector, int n);
float stDevCalc(int* vector, int n, float* mean);

#endif

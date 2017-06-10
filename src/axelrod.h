#ifndef AXELROD_H
#define AXELROD_H

int agentCreate(int **lattice, int idx, int f);
int agentFill(int *feat, int f, int q);
int latticeFill(int **lattice, int n, int f, int q);
int agentPrint(int **lattice, int n, int f, int idx);

#endif

#ifndef AXELROD_H
#define AXELROD_H

typedef struct agent
{
  int f;
  int q;
  int *feat;
} agent;

int agentCreate(agent *lattice, int idx, int f, int q);
int agentFill(int *feat, int f, int q);
int latticeFill(agent *lattice, int n, int f, int q);
int agentPrint(agent *lattice, int n, int idx);
int freeAll(agent *lattice, int n);
int step(agent *lattice, int n);
int getRand(int max);
int pickPassive(int n, int k);
int commonTraits(agent *lattice, int k, int r);
int latticePrint(agent *lattice, int n);

#endif

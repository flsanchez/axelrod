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
int free_all(agent *lattice, int n);

#endif

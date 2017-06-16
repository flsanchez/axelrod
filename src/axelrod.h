#ifndef AXELROD_H
#define AXELROD_H

typedef struct agent
{
  int f;
  int q;
  int *feat;
  int label;
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
int latticePrintLinks(agent *lattice, int n);
int latticePrintToFile(agent *lattice, int n, FILE *fs);
int latticePrintLabels(agent *lattice, int n);
int maxCluster(agent *lattice, int n, int frag);
int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns);

#endif

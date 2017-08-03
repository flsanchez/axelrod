#ifndef AGENT_H
#define AGENT_H

typedef struct agent
{
  int f;      //numero de features
  int q;      //numero de traits
  int *feat;  //vector de features
  int label;  //etiqueta identificadora de cluster
  int baseq;  //codificacion unica del estado, en base q
} agent;

int agentCreate(agent *lattice, int idx, int f, int q);
int agentFill(int *feat, int f, int q);
int agentPrint(agent *lattice, int n, int idx);
int latticeFill(agent *lattice, int n, int f, int q);
int latticeBaseq(agent *lattice, int n);
int latticePrintLinks(agent *lattice, int n); //
int latticePrintToFile(agent *lattice, int n, FILE *fs); //
int latticePrintLabels(agent *lattice, int n); //
int freeAll(agent *lattice, int n); //

#endif

#ifndef AXELROD_H
#define AXELROD_H

typedef struct parameter
{
  // tipo lattice
  int n;
  int f;
  int q;
  int qF;
  int nStub;
  // tipo graph
  int neigOrdEdges;
  int neigOrdRewire;
  int nRewire;
  int nEdgeRew;
  int nEdgesAdd;
  // axelrod
  float phi;
} parameter;

int step(vertex* graph, agent *lattice, int n, float phi); //
int maxCluster(agent *lattice, int* nsAcum, int n, int frag); //
int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns); //
int opinionInteraction(agent* lattice, int i, int j, int hij, int th, float phi);
int socialInteraction(vertex* graph, int i, int j, int k);
int fieldInteraction(agent* lattice, int i);
int stopReached(vertex* graph, agent* lattice, int n);
int activeLinks(vertex* graph, agent* lattice, int n);

int axelrodInit(parameter* param, agent* lattice, vertex* graph);
int axelrodSingleRun(parameter* param, agent* lattice, vertex* graph, int v);

#endif

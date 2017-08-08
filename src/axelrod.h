#ifndef AXELROD_H
#define AXELROD_H

int step(vertex* graph, agent *lattice, int n); //
int maxCluster(agent *lattice, int n, int frag); //
int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns); //
int pickPassiveNeigh(vertex* graph, int k); //
int opinionInteraction(agent* lattice, int i, int j, int hij);

#endif

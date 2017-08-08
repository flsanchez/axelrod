#ifndef AXELROD_H
#define AXELROD_H

int step(vertex* graph, agent *lattice, int n); //
int maxCluster(agent *lattice, int n, int frag); //
int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns); //
int pickPassiveNeig(vertex* graph, int i); //
int pickPassiveNotNeig(vertex* graph, int n, int i);
int opinionInteraction(agent* lattice, int i, int j, int hij);
int socialInteraction(vertex* graph, int i, int j, int k);
int stopReached(vertex* graph, agent* lattice, int n);

#endif

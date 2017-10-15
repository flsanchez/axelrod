#ifndef AXELROD_H
#define AXELROD_H

int step(vertex* graph, agent *lattice, int n, float phi); //
int maxCluster(agent *lattice, int* nsAcum, int n, int frag); //
int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns); //
/*int pickPassiveNeig(vertex* graph, int i); //
int pickPassiveNotNeig(vertex* graph, int n, int i);*/
int opinionInteraction(agent* lattice, int i, int j, int hij, int th, float phi);
int socialInteraction(vertex* graph, int i, int j, int k);
int stopReached(vertex* graph, agent* lattice, int n);
int activeLinks(vertex* graph, agent* lattice, int n);

#endif

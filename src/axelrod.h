#ifndef AXELROD_H
#define AXELROD_H

int step(struct agent *lattice, int n); //
int commonTraits(struct agent *lattice, int k, int r); //
int maxCluster(struct agent *lattice, int n, int frag); //
int clusterSize(struct agent *lattice, int n, int frag, int *fragsz, int *ns); //

int pickPassive(int n, int k); //
int getRand(int max);



#endif

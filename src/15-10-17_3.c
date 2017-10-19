#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/agent.h"
#include "include/graph.h"
#include "include/label.h"
#include "include/misc.h"
#include "include/axelrod.h"
#include "include/functions.h"


int main(int argc, char *argv[]){

  int n = 50;
  int f = 11;
  int q = 180;
  int qF = 2;
  int neigOrdEdges = 2;
  int neigOrdRewire = 2;
  int nRewire = 1;
  int nmbrOfRew = 0;
  int nEdgeRew = 0*n*n;
  float phi = 0.05;
  int niter = 0.25E9;
  int paso = n*n;
  int frag,max;
  int nStub = n*n*0.01;
  FILE* fs;
  FILE* fs2;
  FILE* fs3;
  char name[100];
  int nEdgesAdd = 100;

  if(argc>3){
    sscanf(argv[1], "%d", &nEdgesAdd);
    sscanf(argv[2], "%f", &phi);
    sscanf(argv[3], "%d", &q);
  }

  srand(time(NULL));

  agent* lattice = (agent*) malloc(n * n * sizeof(agent));
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));

  latticeInit(lattice, n, f);
  latticeFill(lattice, n, q, qF);
  latticeSetStub(lattice,n,nStub);
  graphInit(graph, n);
  graphFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);
  graphEdgesAddNRand(graph, n, nEdgesAdd);

  sprintf(name, "noVac_vs_paso_q_%d_phi_%.2f.txt",q,phi);
  fs = fopen(name,"w");

  sprintf(name, "red_q_%d_phi_%.2f.red",q,phi);
  fs2 = fopen(name,"w");

  sprintf(name, "redCultural_q_%d_phi_%.2f.red",q,phi);
  fs3 = fopen(name,"w");

  int i = 0;
  int actLinks = 1;
  int massNonVac;
  int t = time(NULL);
  while(/*actLinks != 0  &&*/ i != niter){

    nmbrOfRew = nmbrOfRew + step(graph,lattice,n,phi);

    if(i%(5*paso)==0){
      //stop = stopReached(graph,lattice,n);
      actLinks = activeLinks(graph, lattice, n);
      massNonVac = nonVaccinatorTotal(lattice,n);
      latticePrintFeatNToFile(lattice, n, f-1, fs2);
      frag = latticeLabelCultural(graph,lattice,n);
      max = maxCluster(lattice, NULL, n, frag);
      latticePrintLabelsToFile(lattice,n,fs3);
      fprintf(fs, "%d %d %d\n", massNonVac, actLinks, max);
    }

    if(i%(int)1E6==0) printf("Paso %d; Active Links = %d; nonVacc = %d; Smax = %d; Phi = %f; q = %d\n", i, actLinks, massNonVac, max, phi,q);

    i++;

  }
  printf("Paso %d\n", i);

  frag = latticeLabel(graph, lattice, n);
  max = maxCluster(lattice, NULL, n, frag);
  t = time(NULL)-t;
  printf("Smax = %d; t = %d; pasos = %d\n",max,t,i-1);

  fclose(fs);
  fclose(fs2);
  fclose(fs3);
  latticeFree(lattice, n);
  free(lattice);
  graphFree(graph, n);
  free(graph);

  return 0;
}

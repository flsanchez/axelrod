#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"
#include "misc.h"
#include "axelrod.h"
#include "functions.h"


int main(int argc, char *argv[]){

  int n = 50;
  int f = 11;
  int q = 80;
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
  int end = 0;
  int nStub = n*n*0.01;
  FILE* fs;
  FILE* fs2;
  FILE* fs3;
  char name[100];

  if(argc>1){
    sscanf(argv[1], "%f", &phi);
  }

  srand(time(NULL));

  agent* lattice = (agent*) malloc(n * n * sizeof(agent));
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));

  latticeInit(lattice, n, f);
  latticeFill(lattice, n, q, qF);
  latticeSetStub(lattice,n,nStub);
  graphInit(graph, n);
  graphEdgesFill(graph, n, neigOrdEdges);
  graphRewireFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);

  sprintf(name, "noVac_vs_paso_phi_%.2f.txt",phi);
  fs = fopen(name,"w");

  sprintf(name, "red_phi_%.2f.red",phi);
  fs2 = fopen(name,"w");

  sprintf(name, "redCultural_phi_%.2f.red",phi);
  fs3 = fopen(name,"w");

  int i = 0;
  int stop = 0;
  int actLinks = 0;
  int t = time(NULL);
  while(/* stop == 0  && */i != niter){

    if( i >= (int)(150E6) ) phi = 0;

    nmbrOfRew = nmbrOfRew + step(graph,lattice,n,phi);

    if(i%(5*paso)==0){
      //stop = stopReached(graph,lattice,n);
      actLinks = activeLinks(graph, lattice, n);
      fprintf(fs, "%d %d\n", nonVaccinatorTotal(lattice, n), actLinks);
      latticePrintFeatNToFile(lattice, n, f-1, fs2);
      latticeLabelCultural(graph,lattice,n);
      latticePrintLabelsToFile(lattice,n,fs3);
    }

    if(i%(int)1E6==0) printf("Paso %d; Active Links = %d; Phi = %f\n", i, actLinks, phi);

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/agent.h"
#include "include/graph.h"
#include "include/label.h"
#include "include/axelrod.h"
#include "include/functions.h"
#include "include/misc.h"


/* este main hace una corrida simple de un axelrod y entrega el Smax y la
cantidad de pasos para llegar al stop por pantalla */

int main(int argc, char *argv[]){

  int n = 50;
  float phi = 0;
  int prom = 1000;
  if(argc > 1){
    sscanf(argv[1], "%d", &prom);
  }
  int* nsAcumVacc = malloc(n*n*sizeof(int));
  int frag;
  FILE *fs;
  FILE *fs1;
  FILE *fs2;

  fs1 = fopen("data.txt","w");
  fprintf(fs1, "# nonVacTot\n");

  fs2 = fopen("frag_dist.frag","w");
  fprintf(fs2, "# distribucion de fragmentos\n");

  srand(time(NULL));

  for(int i = 0; i < prom; i++){

    agent* lattice;
    vertex* graph;

    fs = fopen("stateFin.gra","r");
    n = graphLoadFromFile(&graph,fs);
    fclose(fs);
    fs = fopen("stateFin.lat","r");
    latticeLoadFromFile(&lattice,fs);
    fclose(fs);
    //transformo el ultimo feat a binario
    latticeTransformVaccToBinary(lattice, n, phi);
    frag = latticeLabelVac(graph, lattice, n);
    for(int i = 0; i < n*n; i++) nsAcumVacc[i] = 0;
    maxCluster(lattice, nsAcumVacc, n, frag);
    for(int i = 0; i < n*n; i++) fprintf(fs2, "%d ", nsAcumVacc[i]);
    fprintf(fs2, "\n");
    /*t = time(NULL)-t;
    printf("Smax = %d; t = %d; pasos = %d\n",max,t,i-1);*/
    printf("Paso %d\n", i);
    fprintf(fs1, "%d\n", nonVaccinatorTotal(lattice, n));

    latticeFree(lattice, n);
    free(lattice);
    graphFree(graph, n);
    free(graph);

  }
  fclose(fs1);
  fclose(fs2);
  free(nsAcumVacc);
  return 0;
}

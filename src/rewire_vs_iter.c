#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"
#include "axelrod.h"

/* graba en un txt la cantidad de rewires en funcion de los pasos e identifica 
el paso de stop */


int main(){

  int n = 50;
  int f = 10;
  int nmbrOfq = 40;
  int* qVector = malloc(nmbrOfq*sizeof(int));
  for(int i = 0; i<nmbrOfq; i++) qVector[i] = 800 + 10*(i+1);
  int q = qVector[0];
  int neigOrd = 2;
  int nRewire = 1;
  int nmbrOfRew = 0;
  int niter = 50E6;
  int paso = 1E3;
  int end;
  int frag,max;
  FILE *fs;
  char name[100];

  int i, stop, stepRes, t;

  srand(time(NULL));

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  latticeInit(lattice, n, f, q);

  for(int j = 0; j<nmbrOfq; j++){

    q = qVector[j];
    end = 0;

    latticeFill(lattice, n, q);
    vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));
    graphInit(graph, n, nRewire, neigOrd);
    graphFill(graph, n, neigOrd);

    sprintf(name,"iter_q%d.txt",j);
    fs = fopen(name,"w");
    fprintf(fs, "# paso q=%d\n",q);
    fprintf(fs,"0\n");

    i = 0;
    stop = 0;
    t = time(NULL);

    while(i < niter){

      if(i%paso==0){
        stop = stopReached(graph,lattice,n);
        if(stop == 1 && end == 0) end = i;
        //printf("Paso: %d; Stop = %d; q = %d\n",i,stop,q);
      }
      stepRes = step(graph,lattice,n);
      if( stepRes == 1 ){
        nmbrOfRew++;
        fprintf(fs, "%d\n", i);
      }

      i++;

    }

    fprintf(fs, "%d\n#end=%d\n",i, end);
    fclose(fs);

    frag = latticeLabel(lattice,n);
    max = maxCluster(lattice,n,frag);
    t = time(NULL)-t;
    printf("Smax = %d; t = %d; pasos = %d\n",max,t,i-1);
    graphFree(graph, n);

  }

  free(qVector);
  latticeFree(lattice, n);

  return 0;
}

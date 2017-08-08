#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "misc.h"
#include "axelrod.h"

int step(vertex* graph, agent *lattice, int n){

  int i, j, hij;
  i = getRand(n*n); //indice del activo
  j = pickPassiveNeigh(graph, i); //indice del pasivo(vecino al azar)
  hij = commonTraits(lattice, i, j);

  opinionInteraction(lattice, i, j, hij);

  return 0;

}

int pickPassiveNeigh(vertex* graph, int k){
  int idx = getRand(graph[k].nEdges);
  return graph[k].edges[idx];
}

int maxCluster(agent *lattice, int n, int frag){

  //fragsz[i] contiene el tamaño del cluster de etiqueta i
  int *fragsz = malloc(frag*sizeof(int));
  //ns[i] contiene cuantos clusters de tamaño i-1 se encontraron en la red
  int *ns = malloc(n*n*sizeof(int));

  for(int i = 0; i<frag; i++) fragsz[i] = 0;
  for(int i = 0; i<n*n; i++) ns[i] = 0;

  clusterSize(lattice, n, frag, fragsz, ns);

  int mayor = 0;

  for(int i = 1; i<frag; i++) if(fragsz[i]>mayor) mayor = fragsz[i];

  free(fragsz);
  free(ns);

  return mayor;

}

int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns){

	for(int i=0 ; i<n*n; i++) fragsz[lattice[i].label]++;
	fragsz[0] = 0;  //lo pongo a 0 a mano, ya que conte cuantos 0 hay en la red

	for(int i=1 ; i<frag; i++) if(fragsz[i]!=0) ns[fragsz[i]-1]++;

  return 0;

}

int opinionInteraction(agent* lattice, int i, int j, int hij){

  int uncomTrait, f;
  float prob;
  f = lattice[i].f;

  prob = (float) hij / f;

  if( ((float) rand() / (float) RAND_MAX) < prob){

    if(hij != f){

      int cont = 0;
      int uncomIdx = -1;
      uncomTrait = getRand(f-hij) + 1;
      while(cont != uncomTrait){
        uncomIdx++;
        if(lattice[i].feat[uncomIdx] != lattice[j].feat[uncomIdx]) cont++;
      }

      lattice[i].feat[uncomIdx] = lattice[j].feat[uncomIdx];

    }

  }

  return 0;
}

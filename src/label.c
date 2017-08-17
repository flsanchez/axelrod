#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"

int latticeLabel(vertex* graph, agent* lattice, int n){

  int j;
  int f = lattice[0].f;
  int frag = 2;
  int* clase = malloc(sizeof(int)*n*n);
  int* commNeig = malloc(sizeof(int)*n*n);
  int nCommNeig;

  clase[0] = 0;
  clase[1] = 1;
  for(int i = 2; i<n*n; i++) clase[i] = 0;
  lattice[0].label = 1;

  for(int idx = 1; idx<n*n; idx++){
    nCommNeig = 0;
    for(int idxj = 0; idxj<graph[idx].nEdges; idxj++){
      j = graph[idx].edges[idxj];
      if(j<idx){
        if(commonTraits(lattice, idx, j) == f){
          commNeig[nCommNeig] = j;
          nCommNeig++;
        }
      }
    }

    if(nCommNeig == 0){
      lattice[idx].label = frag;
      clase[frag] = frag;
      frag++;
    }
    else if(nCommNeig == 1){
      j = commNeig[0];
      lattice[idx].label = lattice[j].label;
    }
    else falseLabel(lattice, clase, commNeig, nCommNeig, idx);
  }

  fixLabel(lattice, n, clase);

  free(clase);
  free(commNeig);
  return frag;
}

int falseLabel(agent *lattice, int *clase, int* commNeig, int nCommNeig, int idx){

  int* s = malloc(nCommNeig*sizeof(int));
  for(int i = 0; i<nCommNeig; i++) s[i] = lattice[commNeig[i]].label; // copio commNeig a s
  int minS = s[0]; //valor inicial

  for(int i = 0; i<nCommNeig; i++){
    while(clase[s[i]]<0) s[i] = -clase[s[i]];
    if(s[i]<minS) minS = s[i];
  }

  for(int i = 0; i<nCommNeig; i++){
    if(s[i] == minS) clase[s[i]] = s[i];
    else clase[s[i]] = -minS;
  }

  lattice[idx].label = minS;

  free(s);
  return 0;

}

int fixLabel(agent *lattice, int n, int *clase){

	int s;

	for(int i=0; i<n*n; i++){

		s = lattice[i].label;
		while(clase[s]<0) s = -clase[s];
		lattice[i].label = s;

	}

  return 0;

}

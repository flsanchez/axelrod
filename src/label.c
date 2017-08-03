#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"

int latticeLabel(agent *lattice, int n){

  int frag = 2;
  int f = lattice[0].f;
  int *clase = malloc(n*n*sizeof(int));

  clase[0] = 0;
  clase[1] = 1;

  for(int i=2; i<n*n; i++) clase[i] = 0;

  lattice[0].label = 1; // primer elemento de la red

  for(int j=1;j<n;j++) updateLabel(lattice,clase,j-1,j,&frag); //primera fila

  for(int i=1;i<n;i++){

    updateLabel(lattice,clase,(i-1)*n,i*n,&frag); //primer elemento de cada fila

    for(int j=1;j<n;j++){

      if(commonTraits(lattice,(i-1)*n+j,i*n+j-1) == f){
        if(commonTraits(lattice,(i-1)*n+j,i*n+j) == f){
          falseLabel(lattice,clase,(i-1)*n+j,i*n+j-1,i*n+j);
        }
          else updateLabel(lattice,clase,(i-1)*n+j,i*n+j,&frag);
        }
      else{
        if(commonTraits(lattice,(i-1)*n+j,i*n+j) == f){
          updateLabel(lattice,clase,(i-1)*n+j,i*n+j,&frag);
        }
        else updateLabel(lattice,clase,i*n+j-1,i*n+j,&frag);
      }

    }
  }

  fixLabel(lattice, clase, n);
  free(clase);

  return frag;

}

int updateLabel(agent *lattice, int *clase, int idx1, int idx2, int *frag){	 //cambia la red por numeros de etiqueta

  int f = lattice[0].f;

	if (commonTraits(lattice,idx1,idx2) != f){
		lattice[idx2].label = *frag;
    clase[*frag] = *frag;
		*frag = *frag + 1;
	}
	else lattice[idx2].label = lattice[idx1].label;

  return 0;

}

int falseLabel(agent *lattice, int *clase, int idx1, int idx2, int idx){

  int s1 = lattice[idx1].label;
  int s2 = lattice[idx2].label;

	while(clase[s1]<0) s1=-clase[s1];
	while(clase[s2]<0) s2=-clase[s2];

	if(s1<s2) {
		clase[s2]=-s1;
		clase[s1]=s1;
		lattice[idx].label=s1;
	}
	else{
		clase[s1]=-s2;
		clase[s2]=s2;
		lattice[idx].label=s2;
	}

  return 0;

}

int fixLabel(agent *lattice, int *clase, int n){

	int s;

	for(int i=0; i<n*n; i++){

		s = lattice[i].label;
		while(clase[s]<0) s = -clase[s];
		lattice[i].label = s;

	}

  return 0;

}

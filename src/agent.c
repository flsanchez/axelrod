#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"
#include "agent.h"

int agentInit(agent *lattice, int idx, int f, int q){

  lattice[idx].f = f;
  lattice[idx].q = q;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));
  lattice[idx].label = 0;
  lattice[idx].baseq = 0;

  return 0;

}

int agentFill(int *feat, int f, int q){

  for(int i=0; i<f; i++) {

    feat[i] = q;
    while(feat[i] == q){
      feat[i] = (int) (q * ((float) rand() / (float) RAND_MAX));
    }

  }

  return 0;
}

int agentPrint(agent *lattice, int n, int idx){

  printf("Agent N. %d:\n",idx);
  for(int i=0; i<lattice[idx].f; i++){
    printf("Trait %d = %d\n",i,lattice[idx].feat[i]);
  }

  return 0;

}

int latticeInit(agent *lattice, int n, int f, int q){

  for(int i=0; i<n*n; i++) agentInit(lattice, i, f, q);

  return 0;
}

int latticeFill(agent *lattice, int n, int q){

  for(int i=0; i<n*n; i++){
    lattice[i].q = q;
    agentFill(lattice[i].feat, lattice[i].f, lattice[i].q);
  }

  return 0;
}

int latticeBaseq(agent *lattice, int n){

  int f = lattice[0].f;
  int q = lattice[0].q;

  int *base = malloc(f*sizeof(int));

  base[0] = 1;

  for(int i=1;i<f;i++) base[i] = base[i-1] * q;

  for(int i=0;i<n*n;i++){
    lattice[i].baseq = 0;
    for(int j=0;j<f;j++) lattice[i].baseq = lattice[i].baseq + base[j] * lattice[i].feat[j];
  }

  free(base);
  return 0;

}

int latticePrint(agent *lattice, int n){
  for(int i = 0; i<n; i++){
    for(int j = 0; j<n; j++) printf("%d ", lattice[i*n+j].feat[0]);
    printf("\n");
  }
  return 0;
}

int latticePrintLinks(agent *lattice, int n){

  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-1;j++){
      printf("* ");
      printf("%d ",commonTraits(lattice,i*n+j,i*n+j+1));
    }
    printf("*\n");
    for(int j=0;j<n;j++){
      printf("%d   ",commonTraits(lattice,i*n+j,(i+1)*n+j));
    }
    printf("\n");
  }

  for(int j=0;j<n-1;j++){
    printf("* ");
    printf("%d ",commonTraits(lattice,(n-1)*n+j,(n-1)*n+j+1));
  }
  printf("*\n");

}

int latticePrintBaseqToFile(agent *lattice, int n, FILE *fs){

  int f = lattice[0].f;
  int q = lattice[0].q;

  latticeBaseq(lattice,n);

  if(fs != NULL){

    fprintf(fs,"# n f q\n# %d %d %d\n",n,f,q);

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        fprintf(fs,"%llu",lattice[i*n+j].baseq);
        fprintf(fs," ");
      }
      fprintf(fs,"\n");
    }

  }
  else{

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        printf("%llu",lattice[i*n+j].baseq);
        printf(" ");
      }
      printf("\n");
    }

  }

  return 0;

}

int latticePrintLabels(agent *lattice, int n){

  for(int i = 0; i<n; i++){

    for(int j = 0; j<n; j++) printf("%d ",lattice[i*n+j].label);
    printf("\n");

  }

  return 0;

}

int commonTraits(agent *lattice, int i, int j){

  int f = lattice[i].f;
  int res = 0;

  for(int idx=0; idx < f; idx++){
    if(lattice[i].feat[idx] == lattice[j].feat[idx]) res++;
  }

  return res;

}

int latticeFree(agent *lattice, int n){

  for(int i=0;i<n*n;i++) free(lattice[i].feat);
  return 0;

}

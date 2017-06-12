#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int agentCreate(agent *lattice, int idx, int f, int q){

  lattice[idx].f = f;
  lattice[idx].q = q;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));

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

int latticeFill(agent *lattice, int n, int f, int q){

  for(int i=0; i<n*n; i++){
    agentCreate(lattice, i, f, q);
    agentFill(lattice[i].feat, lattice[i].f, lattice[i].q);
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

int freeAll(agent *lattice, int n){

  //for(int i=0;i<n*n;i++) free(lattice[i].feat);
  free(lattice);

  return 0;

}

int step(agent *lattice, int n){

  int k,r,nkr,f, uncomTrait;
  int uncomIdx = -1;
  int cont = 0;
  float prob;
  k = getRand(n*n); //indice del activo
  r = pickPassive(n,k); //indice del pasivo(vecino al azar, CC periodicas)
  f = lattice[k].f;

  nkr = commonTraits(lattice,k,r);
  prob = (float) nkr / f;

  if( ((float) rand() / (float) RAND_MAX) < prob){

    if(nkr != f){

      uncomTrait = getRand(f-nkr) + 1;
      while(cont != uncomTrait){
        uncomIdx++;
        if(lattice[k].feat[uncomIdx] != lattice[r].feat[uncomIdx]) cont++;
      }

      lattice[k].feat[uncomIdx] = lattice[r].feat[uncomIdx];

    }

  }

  return 0;

}

int getRand(int max){

  int res = max;
  while(res == max) res = (int) (max * ((float) rand() / (float) RAND_MAX));
  return res;

}

int pickPassive(int n, int k){

  int i,j,aux,r;

  i = k/n;
  j = k%n;

  if(i==0){
    if(j==0){
      aux = getRand(2);
      if(aux==0) i++;
      else j++;
    }
    else if(j==n-1){
      aux = getRand(2);
      if(aux==0) i++;
      else j--;
    }
    else{
      aux = getRand(3);
      if(aux==0) i++;
      else if(aux==1) j++;
      else j--;
    }
  }else if(i==n-1){
    if(j==0){
      aux = getRand(2);
      if(aux==0) i--;
      else j++;
    }
    else if(j==n-1){
      aux = getRand(2);
      if(aux==0) i--;
      else j--;
    }else{
      aux = getRand(3);
      if(aux==0) i--;
      else if(aux==1) j++;
      else j--;
    }
  }else{
    if(j==0){
      aux = getRand(3);
      if(aux==0) i++;
      else if(aux==1) i--;
      else j++;
    }else if(j==n-1){
      aux = getRand(3);
      if(aux==0) i++;
      else if(aux==1) i--;
      else j--;
    }else{
      aux = getRand(4);
      if(aux==0) i++;
      else if(aux==1) i--;
      else if(aux==2)j++;
      else j--;
    }
  }

  r = i*n + j;

  return r;

}

int commonTraits(agent *lattice, int k, int r){

  int f = lattice[k].f;
  int res = 0;

  for(int i=0; i < f; i++) if(lattice[k].feat[i] == lattice[r].feat[i]) res++;

  return res;

}

int latticePrint(agent *lattice, int n){

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

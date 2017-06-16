#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"

int agentCreate(agent *lattice, int idx, int f, int q){

  lattice[idx].f = f;
  lattice[idx].q = q;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));
  lattice[idx].label = 0;

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

  for(int i=0;i<n*n;i++) free(lattice[i].feat);
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

int latticePrintToFile(agent *lattice, int n, FILE *fs){

  int f = lattice[0].f;
  int q = lattice[0].q;

  if(fs != NULL){

    fprintf(fs,"# n f q\n# %d %d %d\n",n,f,q);

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        for(int k=0;k<f;k++) fprintf(fs,"%d",lattice[i*n+j].feat[k]);
        fprintf(fs," ");
      }
      fprintf(fs,"\n");
    }
  }
  else{
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        for(int k=0;k<f;k++) printf("%d",lattice[i*n+j].feat[k]);
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

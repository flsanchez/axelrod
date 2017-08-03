#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "axelrod.h"
#include "agent.h"

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

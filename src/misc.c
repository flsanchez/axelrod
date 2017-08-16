#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"

/* getRand() elige un numero aleatorio equiprobable en [0,max-1] */

int getRand(int max){
  int res = max;
  while(res == max){
    res = (int) (max * ((float) rand() / (float) RAND_MAX));
  }
  return res;

}

/* shuffleArray() mezcla los elementos del array */

int shuffleArray(int* shuffled,int n){
  int* res = (int*) malloc(sizeof(int)*n);
  for(int i = 0; i<n;i++) res[i] = shuffled[i];
  int idx,aux;
  for(int i = 0; i<n; i++){
    idx = getRand(n-i);
    shuffled[i] = res[idx];
    aux = res[idx];
    res[idx] = res[n-i-1];
    res[n-i-1] = aux;
    res = (int*) realloc(res,sizeof(int)*(n-i-1));
  }
  free(res);
  return 0;
}

/* isElemInArray() devuelve 1 si elem esta en el array y 0 sino */

int isElemInArray(int* array, int n, int elem){
  for(int i = 0; i<n; i++) if(array[i] == elem) return 1;
  return 0;
}

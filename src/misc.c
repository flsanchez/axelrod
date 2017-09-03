#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"

/* getRand() elige un numero aleatorio equiprobablemente en [0,max-1] */

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

int patternFill(int** patterni, int** patternj, int n, int neigOrd){
  int idxPattern;
  int nPattern;
  if(neigOrd == 1){
    nPattern = 4;
    *patterni = malloc(nPattern*sizeof(int));
    *patternj = malloc(nPattern*sizeof(int));

    (*patterni)[0] = -1;
    (*patterni)[1] = -1;
    (*patterni)[2] = 1;
    (*patterni)[3] = 1;

    (*patternj)[0] = -1;
    (*patternj)[1] = 1;
    (*patternj)[2] = -1;
    (*patternj)[3] = 1;
  }
  else if(neigOrd == 2){
    nPattern = 8;
    *patterni = malloc(nPattern*sizeof(int));
    *patternj = malloc(nPattern*sizeof(int));

    idxPattern = 0;
    for(int i = -1; i < 2; i++){
      for(int j = -1; j < 2; j++){
        if(i!=0 || j!=0){
          (*patterni)[idxPattern] = i;
          (*patternj)[idxPattern] = j;
          idxPattern++;
        }
      }
    }
  }
  else if(neigOrd == 3){
    nPattern = 16;
    *patterni = malloc(nPattern*sizeof(int));
    *patternj = malloc(nPattern*sizeof(int));

    idxPattern = 0;
    int i,j;
    i = -2;
    for(int j = -2; j < 3; j++){
      (*patterni)[idxPattern] = i;
      (*patternj)[idxPattern] = j;
      idxPattern++;
    }
    j = 2;
    for(int i = -1; i < 2; i++){
      (*patterni)[idxPattern] = i;
      (*patternj)[idxPattern] = j;
      idxPattern++;
    }
    i = 2;
    for(int j = 2; j > -3; j--){
      (*patterni)[idxPattern] = i;
      (*patternj)[idxPattern] = j;
      idxPattern++;
    }
    j = -2;
    for(int i = 1; i > -2; i--){
      (*patterni)[idxPattern] = i;
      (*patternj)[idxPattern] = j;
      idxPattern++;
    }
  }

  return nPattern;
}

int fillNeigArray(int* patterni, int* patternj, int nPattern, int** neigArray, int idx, int n){
  int i = idx/n;
  int j = idx%n;
  int iPattern;
  int jPattern;
  int iNeig;
  int jNeig;
  int idxPattern;


  for(int k = 0; k<nPattern; k++){
    iPattern = patterni[k];
    jPattern = patternj[k];
    iNeig = i + iPattern;
    jNeig = j + jPattern;
    if( iNeig >= 0 && iNeig < n && jNeig >= 0 && jNeig < n ){
      //(*neigArray) = realloc( idx, iNeig*n + jNeig);
    }
  }

  return 0;
}

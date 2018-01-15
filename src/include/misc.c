#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"

/* getRand() elige un numero aleatorio equiprobablemente en [0,max-1] */

int getRand(int max){
  int res = max;
  while(res == max && max != 0){
    res = (int) (max * ((float) rand() / (float) RAND_MAX));
  }
  return res;

}

/* shuffleArray() mezcla los elementos del array */

int shuffleArray(int* shuffled, int n){
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

/* shuffleArrays() mezcla los elementos de 2 arrays de manera sincronica */

int shuffleArrays(int* shuffled1, int* shuffled2, int n){
  int* res1 = malloc(sizeof(int)*n);
  int* res2 = malloc(sizeof(int)*n);
  for(int i = 0; i<n;i++){
    res1[i] = shuffled1[i];
    res2[i] = shuffled2[i];
  }
  int idx,aux;
  for(int i = 0; i<n; i++){
    // obtengo el indice random
    idx = getRand(n-i);
    // hago la copia para el primer array
    shuffled1[i] = res1[idx];
    aux = res1[idx];
    res1[idx] = res1[n-i-1];
    res1[n-i-1] = aux;
    res1 = (int*) realloc(res1,sizeof(int)*(n-i-1));
    // hago la copia para el segundo array, con el mismo indice
    shuffled2[i] = res2[idx];
    aux = res2[idx];
    res2[idx] = res2[n-i-1];
    res2[n-i-1] = aux;
    res2 = (int*) realloc(res2,sizeof(int)*(n-i-1));
  }
  free(res1);
  free(res2);
  return 0;
}

/* isElemInArray() devuelve 1 si elem esta en el array y 0 sino */

int isElemInArray(int* array, int n, int elem){
  for(int i = 0; i<n; i++) if(array[i] == elem) return 1;
  return 0;
}

/* patternFill() llena el vector de patterni y patternj con las posibles
  conexiones que puede hacer cada nodo dependiendo de la topologia asignada
  dada por el neigOrd (neigOrd = 1: vecindad de von Neumann orden 1;
  neigOrd = 2: vecindad de Moore orden 1; neigOrd = 3: vecindad de Moore o. 2)*/

int patternFill(int** patterni, int** patternj, int n, int neigOrd){
  int idxPattern;
  int nPattern = -1;
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

/* fillNeigArray() llena, para el nodo idx, a partir de patterni y patternj,
  el vector neigArray con las posibles conexiones dadas las CC no-periodicas*/

int fillNeigArray(int* patterni, int* patternj, int nPattern, int** neigArray,
                  int idx, int n){

  int i = idx/n; // componente i de idx
  int j = idx%n; // componente j de idx
  int iPattern; // guardo la componente i del patron
  int jPattern; // guardo la componente j del patron
  int iNeig; // voy a guardar la comp i del posible vecino resultante
  int jNeig; // idem con j
  int nNeigArray = 0; // tamaño del neigArray
  *neigArray = NULL; // inicializo el neigArray

  // para cada elemento de los vectores de pattern
  for(int k = 0; k<nPattern; k++){
    iPattern = patterni[k];
    jPattern = patternj[k];
    iNeig = i + iPattern; // componente i del vecino final
    jNeig = j + jPattern; // componente j del vecino final
    // si el elemento resultante se encuentra dentro de la red, lo agrego a
    // neigArray como posible conexion
    if( iNeig >= 0 && iNeig < n && jNeig >= 0 && jNeig < n ){
      *neigArray = realloc( *neigArray, sizeof(int)*(nNeigArray + 1) );
      (*neigArray)[nNeigArray] = iNeig*n + jNeig;
      nNeigArray++;
    }
  }
  return nNeigArray;
}

// loadFromTxt() se encarga de leer un archivo en filas a un vector previamente
// definido
int loadFromTxt(FILE* fs, int* array){
  int i = 0, n = 0;
  while( fscanf(fs, "%d ", &n) > 0 ) array[i++] = n;
  return 0;
}

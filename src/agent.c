#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"
#include "agent.h"

/* agentInit() inicializa el agente idx con los valores dados en el input*/

int agentInit(agent *lattice, int idx, int f){

  lattice[idx].f = f;
  //lattice[idx].q = q;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));
  lattice[idx].label = 0;
  //lattice[idx].qF = qF;
  lattice[idx].stub = 0; //por default, inicializan como vacunadores
  return 0;

}

/* agentFill() llena el vector de feats, llenando desde la pos 0 a f-2 con
  numeros aleatorios de [0,q-1] y la pos f-1 con numeros aleatorios de
  [0,qF-1] */

int agentFill(int *feat, int f, int q, int qF){

  for(int i=0; i<f-1; i++) feat[i] = getRand(q);
  feat[f-1] = getRand(qF)*0;

  return 0;
}

/* agentPrint() imprime en pantalla los valores de los traits para el agente
  idx */

int agentPrint(agent *lattice, int n, int idx){

  printf("Agent N. %d:\n",idx);
  for(int i=0; i<lattice[idx].f; i++){
    printf("Trait %d = %d\n",i,lattice[idx].feat[i]);
  }

  return 0;

}

/* latticeInit() inicializa la red de agentes con f features, q traits para
  los features [0,f-2] y qF traits para el feature f-1 */

int latticeInit(agent *lattice, int n, int f){

  for(int i=0; i<n*n; i++) agentInit(lattice, i, f);

  return 0;
}

/* latticeFill() llena los traits de la red entera */

int latticeFill(agent *lattice, int n, int q, int qF){

  for(int i=0; i<n*n; i++){
    lattice[i].q = q;
    lattice[i].qF = qF;
    lattice[i].stub = 0;
    agentFill(lattice[i].feat, lattice[i].f, q, qF);
  }

  return 0;
}

/* latticeSetStub() settea una cantidad de agentes nStub de la red como
  talibanes elegidos al azar de toda la red */

int latticeSetStub(agent* lattice, int n, int nStub){
  int* idxList = malloc(sizeof(int)*n*n);
  for(int i = 0; i < n*n; i++) idxList[i] = i;
  shuffleArray(idxList, n*n);
  latticeSetStubFromArray(lattice, n, idxList, nStub);
  free(idxList);
  return 0;
}

/* latticeSetStubFromArray() settea como talibanes los agentes dados en el
  array */

int latticeSetStubFromArray(agent* lattice, int n, int* idxList, int nArray){
  int idx;
  int f = lattice[0].f;
  for(int i = 0; i < nArray; i++){
    idx = idxList[i];
    lattice[idx].stub = 1;
    lattice[idx].feat[f-1] = 1;
  }
  return 0;
}

/* latticePrintFeats() imprime en pantalla todos los feats para cada agente */

int latticePrintFeats(agent *lattice, int n){
  for(int idx = 0; idx < n*n; idx++) agentPrint(lattice,n,idx);
  return 0;
}

/* latticePrintFeatN() imprime en pantalla solamente el valor del featNIdx */

int latticePrintFeatN(agent *lattice, int n, int featNIdx){
  int f = lattice[0].f;
  for(int i = 0; i<n; i++){
    for(int j = 0; j<n; j++) printf("%d ", lattice[i*n+j].feat[featNIdx]);
    printf("\n");
  }
  return 0;
}

/* latticePrintLabels() imprime en pantalla las etiquetas identificadoras de
  cluster de cada agente */

int latticePrintLabels(agent *lattice, int n){

  for(int i = 0; i<n; i++){

    for(int j = 0; j<n; j++) printf("%d ",lattice[i*n+j].label);
    printf("\n");

  }

  return 0;

}

/* latticePrintLabelsToFile() imprime en un archivo las etiquetas identificadoras de
  cluster de cada agente */

int latticePrintLabelsToFile(agent *lattice, int n, FILE *fs){
  for(int idx = 0; idx<n*n; idx++) fprintf(fs, "%d ",lattice[idx].label);
  fprintf(fs,"\n");
  return 0;
}

/* latticePrintStub() imprime en pantalla los talibanes */

int latticePrintStub(agent* lattice, int n){
  int idx;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      idx = i*n+j;
      if(lattice[idx].stub == 1) printf("* ");
      else printf("0 ");
    }
    printf("\n");
  }
  return 0;
}

/* latticePrintFeatsToFile() guarda los valores de cada feat de cada agente. */

int latticePrintFeatsToFile(agent* lattice, int n, FILE* fs){
  int f;
  for(int i = 0; i < n*n; i++){
    f = lattice[i].f;
    for(int fIdx = 0; fIdx < f-1; fIdx++) fprintf(fs, "%d,",lattice[i].feat[fIdx]);
    fprintf(fs, "%d ",lattice[i].feat[f-1]);
  }
  fprintf(fs, "\n");
  return 0;
}

int latticePrintFeatNToFile(agent *lattice, int n, int featNIdx, FILE* fs){
  int f;
  for(int i = 0; i < n*n; i++){
    f = lattice[i].f;
    fprintf(fs, "%d ",lattice[i].feat[featNIdx]);
  }
  fprintf(fs,"\n");
  return 0;
}

/* latticeFree() libera las alocaciones de memoria hechas dentro
de la estructura lattice */

int latticeFree(agent *lattice, int n){

  for(int i=0;i<n*n;i++) free(lattice[i].feat);
  return 0;

}

/* commonTraits() cuenta cuantos features tienen en comun los agentes i y j,
  devolviendo el resultado */

int commonTraits(agent *lattice, int i, int j){

  int f = lattice[i].f;
  int res = 0;

  for(int idx = 0; idx < f; idx++){
    if(lattice[i].feat[idx] == lattice[j].feat[idx]) res++;
  }

  return res;

}

/* commonTraits() cuenta cuantos features tienen en comun los agentes i y j,
  devolviendo el resultado */

int commonTraitsCultural(agent *lattice, int i, int j){

  int f = lattice[i].f;
  int res = 0;

  for(int idx = 0; idx < f-1; idx++){
    if(lattice[i].feat[idx] == lattice[j].feat[idx]) res++;
  }

  return res;

}

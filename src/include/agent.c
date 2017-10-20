#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"
#include "agent.h"

/* agentInit() inicializa el agente idx con los valores dados en el input*/

int agentInit(agent *lattice, int idx, int f){

  lattice[idx].f = f;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));
  lattice[idx].label = 0;
  lattice[idx].stub = 0; //por default, inicializan como vacunadores
  return 0;

}

/* agentFill() llena el vector de feats, llenando desde la pos 0 a f-2 con
  numeros aleatorios de [0,q-1] y la pos f-1 con numeros aleatorios de
  [0,qF-1] */

int agentFill(int *feat, int f, int q, int qF){

  for(int i=0; i<f-1; i++) feat[i] = getRand(q);
  feat[f-1] = getRand(qF);

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

/* latticePrintFeatsToFile() guarda en un archivo
  los valores de cada feat de cada agente. */

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

/* latticePrintFeatNToFile() guarda los valores del feat Nesimo de cada agente
  en un archivo. */

int latticePrintFeatNToFile(agent *lattice, int n, int featNIdx, FILE* fs){
  for(int i = 0; i < n*n; i++){
    fprintf(fs, "%d ",lattice[i].feat[featNIdx]);
  }
  fprintf(fs,"\n");
  return 0;
}

/* latticeSave() guarda en un archivo el estado completo de la red de agentes */

int latticeSave(agent *lattice, int n, FILE* fs){
  int f;
  //imprimo el numero de agentes por fila o columna
  fprintf(fs, "N %d\n", n);

  //imprimo el f
  fprintf(fs, "f ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].f);
  fprintf(fs, "%d\n", lattice[n*n-1].f);

  //imprimo el q
  fprintf(fs, "q ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].q);
  fprintf(fs, "%d\n", lattice[n*n-1].q);

  //imprimo el qF
  fprintf(fs, "qF ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].qF);
  fprintf(fs, "%d\n", lattice[n*n-1].qF);

  //imprimo el label
  fprintf(fs, "label ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].label);
  fprintf(fs, "%d\n", lattice[n*n-1].label);

  //imprimo la stubborness
  fprintf(fs, "stub ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].stub);
  fprintf(fs, "%d\n", lattice[n*n-1].stub);

  //imprimo el vector de features
  fprintf(fs, "feat ");
  for(int i = 0; i<n*n-1; i++){
    f = lattice[i].f;
    for(int idxF = 0; idxF<f-1; idxF++){
      fprintf(fs, "%d,", lattice[i].feat[idxF]);
    }
    fprintf(fs, "%d ", lattice[i].feat[f-1]);
  }
  f = lattice[n*n-1].f;
  for(int idxF = 0; idxF<f-1; idxF++){
    fprintf(fs, "%d,", lattice[n*n-1].feat[idxF]);
  }
  fprintf(fs, "%d\n", lattice[n*n-1].feat[f-1]);

  return 0;
}

/* latticeLoad() lee la data de una red guardada con la funcion latticeSave() */

int latticeLoad(agent** lattice, FILE* fs){
  int st = 1; //guardo el status del scanf
  int n; //aca voy a guardar el numero de filas o columnas

  st = fscanf(fs, "N %d\n", &n); //leo el numero de filas o cols

  /* con este n ya puedo hacer el malloc de la red, y lo hago sobre una auxiliar
    por las dudas */
  agent* auxLatt = (agent*) malloc(n*n*sizeof(agent));

  /* voy a leer las f */
  st = fscanf(fs, "f ");
  int f;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &f);
    agentInit(auxLatt, idx, f);
  }
  st = fscanf(fs, "%d\n", &f);
  agentInit(auxLatt, n*n-1, f);

  /* voy a leer los q */
  st = fscanf(fs, "q ");
  int q;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &q);
    auxLatt[idx].q = q;
  }
  st = fscanf(fs, "%d\n", &q);
  auxLatt[n*n-1].q = q;

  /* voy a leer los qF */
  st = fscanf(fs, "qF ");
  int qF;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &qF);
    auxLatt[idx].qF = qF;
  }
  st = fscanf(fs, "%d ", &qF);
  auxLatt[n*n-1].qF = qF;

  /* voy a leer los label */
  st = fscanf(fs, "label ");
  int label;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &label);
    auxLatt[idx].label = label;
  }
  st = fscanf(fs, "%d\n", &label);
  auxLatt[n*n-1].label = label;

  /* voy a leer la stubborness */
  st = fscanf(fs, "stub ");
  int stub;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &stub);
    auxLatt[idx].stub = stub;
  }
  st = fscanf(fs, "%d\n", &stub);
  auxLatt[n*n-1].stub = stub;

  /* voy a leer los feats */
  st = fscanf(fs, "feat ");
  int featN;
  for(int idx = 0; idx<n*n-1; idx++){
    f = auxLatt[idx].f;
    for(int idxF = 0; idxF<f-1; idxF++){
      st = fscanf(fs, "%d,", &featN);
      auxLatt[idx].feat[idxF] = featN;
    }
    st = fscanf(fs, "%d ", &featN);
    auxLatt[idx].feat[f-1] = featN;
  }
  f = auxLatt[n*n-1].f;
  for(int idxF = 0; idxF<f-1; idxF++){
    st = fscanf(fs, "%d,", &featN);
    auxLatt[n*n-1].feat[idxF] = featN;
  }
  st = fscanf(fs, "%d\n", &featN);
  auxLatt[n*n-1].feat[f-1] = featN;

  if(st == 0) st = 1;

  * lattice = auxLatt;
  return n;
}

/* latticeCompare() compara 2 redes de agentes a ver si son iguales en el
  sentido de una comparacion entre todos los elementos que componen la
  estructura del agente */

int latticeCompare(agent* lattice1, agent* lattice2, int n){
  for(int idx = 0; idx<n*n; idx++){
    if(lattice1[idx].f != lattice2[idx].f) return 0;
    if(lattice1[idx].q != lattice2[idx].q) return 0;
    if(lattice1[idx].qF != lattice2[idx].qF) return 0;
    if(lattice1[idx].label != lattice2[idx].label) return 0;
    if(lattice1[idx].stub != lattice2[idx].stub) return 0;
  }
  for(int idx = 0; idx<n*n; idx++){
    int f = lattice1[idx].f;
    for(int idxF = 0; idxF<f; idxF++){
      if(lattice1[idx].feat[idxF] != lattice2[idx].feat[idxF]) return 0;
    }
  }
  return 1;
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

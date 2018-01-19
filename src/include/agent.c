#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "functions.h"
#include "misc.h"

/* agentInit() inicializa el agente idx con los valores dados en el input*/

int agentInit(agent *lattice, int idx, int f){

  lattice[idx].f = f;
  lattice[idx].feat = malloc((lattice[idx].f) * sizeof(int));
  lattice[idx].label = 0;
  lattice[idx].stub = 0; //por default, inicializan como vacunadores
  lattice[idx].vacc = 1; // idem
  lattice[idx].immu = 1; // iniciliza como inmunizado por defecto
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
    lattice[idx].feat[f-1] = 0;
    lattice[idx].vacc = 0;
  }
  return 0;
}

/* latticeClusterNList() devuelve una lista con los indices de los integrantes
  del cluster con etiqueta lableClusN, previamente deben estar labeleados
  para que ande */

int latticeClusterNList(agent* lattice, int n, int labelClusN, int** clusterArray){
  int nArray = 0;
  // cuento cuantos en la red hay con la etiqueta labelClusN
  for(int idx = 0; idx < n*n; idx++){
    if(lattice[idx].label == labelClusN) nArray++;
  }
  // asigno la memoria para el vector
  int* clusterNList = malloc(sizeof(int)*nArray);
  int idxCluster = 0;
  // lleno clusterNList con las posiciones de la red correspondientes
  for(int idx = 0; idx < n*n; idx++){
    if(lattice[idx].label == labelClusN){
      clusterNList[idxCluster] = idx;
      idxCluster++;
    }
  }
  *clusterArray = clusterNList;
  return nArray;
}

// latticeSetNonVacc() setea como no vacunadores una cantidad nonVacc al azar,
// pero dentro de estos nonVacc se encuentran los nStub, o sea, setteo al azar
// una cantidad de agentes nonVacc-nStub

int latticeSetNonVacc(agent* lattice, int n, int nonVacc, int nStub){
  int nonVaccToSet = nonVacc-nStub; // la cantidad de noVacunadores neta a settear
  int* auxList = malloc(n*n*sizeof(int));
  // array con indices
  for(int idx = 0; idx < n*n; idx++) auxList[idx] = idx;
  shuffleArray(auxList,n*n); // mezclo el array
  int countNonVacc = 0; // contador de no vacunadores no talibanes
  int idxList = 0; // indice para recorrer auxList
  int idx;
  // asigno como no vacunadores una cantidad de agentes nonVaccToSet
  while(countNonVacc < nonVaccToSet){
    idx = auxList[idxList];
    // si el agente no es taliban, sumo 1 a la cuenta
    if(lattice[idx].stub != 1) countNonVacc++;
    lattice[idx].vacc = 0;
    idxList++;
  }
  // asigno el resto de los agentes que sobran como vacunadores, salvo que sean
  // talibanes, en cuyo caso los pongo como no vacunadores
  for(int i = idxList; i < n*n; i++){
    idx = auxList[i];
    if(lattice[idx].stub != 1) lattice[idx].vacc = 1;
    else lattice[idx].vacc = 0;
  }
  free(auxList);
  return 0;
}

// latticeSetNonImmu() setea como no inmunizados una cantidad nonImmu al azar,
// pero dentro de estos nonImmu se encuentran los nStub, o sea, setteo al azar
// una cantidad de agentes nonVacc-nStub

int latticeSetNonImmu(agent* lattice, int n, int nonImmu, int nStub){
  int nonImmuToSet = nonImmu-nStub; // la cantidad de noVacunadores neta a settear
  int* auxList = malloc(n*n*sizeof(int));
  // array con indices
  for(int idx = 0; idx < n*n; idx++) auxList[idx] = idx;
  shuffleArray(auxList,n*n); // mezclo el array
  int countNonImmu = 0; // contador de no inmunizados no talibanes
  int idxList = 0; // indice para recorrer auxList
  int idx;
  // asigno como no inmunizados una cantidad de agentes nonImmuToSet
  while(countNonImmu < nonImmuToSet){
    idx = auxList[idxList];
    // si el agente no es taliban, sumo 1 a la cuenta
    if(lattice[idx].stub != 1) countNonImmu++;
    lattice[idx].immu = 0;
    idxList++;
  }
  // asigno el resto de los agentes que sobran como inmunizados, salvo que sean
  // talibanes, en cuyo caso los pongo como no inmunizados
  for(int i = idxList; i < n*n; i++){
    idx = auxList[i];
    if(lattice[idx].stub != 1) lattice[idx].immu = 1;
    else lattice[idx].immu = 0;
  }
  free(auxList);
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

/* latticeTransformVaccToBinary() settea como vacunador o no vacunador
  en funcion del valor del ultimo feature. Por defecto asume 100% eficiencia de
  vacuna e inmuniza o no en funcion de si esta vacunado o no respectivamente */

int latticeTransformVaccToBinary(agent* lattice, int n){
  int f, q;
  float r, prob;
  for(int idx = 0; idx < n*n; idx++){
    f = lattice[idx].f;
    q = lattice[idx].q;
    prob = ((float)(lattice[idx].feat[f-1]))/(q-1);
    r = ((float) rand() / (float) RAND_MAX);
    //si el agente no es taliban
    if(lattice[idx].stub == 0){
      //pongo el ultimo feat a 1 con probabilidad prob
      if(r<prob){
        lattice[idx].vacc = 1;
        lattice[idx].immu = 1;
      }
      else{
        lattice[idx].vacc = 0;
        lattice[idx].immu = 0;
      }
    }
    else{
      lattice[idx].vacc = 0;
      lattice[idx].immu = 0;
    }
  }
  return 0;
}

/* latticeVaccEfficiencyFromList() settea como vacunador o no vacunador
  en funcion del valor del ultimo feature */

int latticeVaccEfficiencyFromList(agent* lattice, int n, float* effList,
                                          float* effProp, int nEffList)
{
  float r, eff;
  // obtengo la lista de vacunados
  int vacTot;
  int* vaccList;
  vacTot = vaccinatorList(lattice, n, &vaccList);

  // hago la lista de probabilidades en base a las eficiencias
  // y las proporciones dadas para cada eficiencia
  float* probArray = malloc(sizeof(float)*vacTot); // probas de inmunizar para
                                                   // cada agente
  int* effPropTot = malloc(sizeof(int)*nEffList); // numero de agentes con cada
                                                  // eficiencia
  // asigno los numeros de agentes con cada eficiencia
  int effPropCumSum = 0; // suma acumulada de la cantidad de agentes asignada
  for(int effIdx = 0; effIdx < nEffList-1; effIdx++){
    effPropTot[effIdx] = effProp[effIdx]*vacTot;
    effPropCumSum = effPropCumSum + effPropTot[effIdx];
  }
  // el ultimo lugar lo guardo en funcion de los que faltan, para evitar
  // inconsistencias por redondeo
  effPropTot[nEffList-1] = vacTot - effPropCumSum;

  // voy a asignar las probabilidades con las proporciones dadas
  int effCount; // cuantos vacunados va a haber con una eficiencia
  int effCountCumSum = 0; // acumula la cantidad asignada
  int probIdx = 0; // este indice me mueve en el vector probArray
  for(int effIdx = 0; effIdx < nEffList; effIdx++){
    effCount = effPropTot[effIdx];
    effCountCumSum = effCount + effCountCumSum;
    for(int idx = probIdx; idx < effCountCumSum; idx++){
      probArray[idx] = effList[effIdx]; // asigno las probabilidades
    }
    probIdx = effCountCumSum;
  }
  // una vez asignadas, las mezclo
  shuffleArrayFloat(probArray, vacTot);

  /*printf("effPropTot = [ ");
  for(int i = 0; i < nEffList; i++) printf("%d ", effPropTot[i]);
  printf("]\n");
  printf("probArray = [ ");
  for(int i = 0; i < vacTot; i++) printf("%.3f ", probArray[i]);
  printf("]\n");*/

  // inmunizo con la probabilidad de probArray
  for(int idx = 0; idx < vacTot; idx++){
    int idxVac = vaccList[idx];
    eff = probArray[idx];
    r = ((float) rand() / (float) RAND_MAX);
    if(r<eff) lattice[idxVac].immu = 1;
    else lattice[idxVac].immu = 0;
  }
  free(vaccList);
  free(effPropTot);
  free(probArray);
  return 0;
}

/* latticeSave() guarda en un archivo el estado completo de la red de agentes */

int latticeSaveToFile(agent *lattice, int n, FILE* fs){
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

  // grabo la vacc
  fprintf(fs, "vacc ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].vacc);
  fprintf(fs, "%d\n", lattice[n*n-1].vacc);

  // grabo la immu
  fprintf(fs, "immu ");
  for(int i = 0; i<n*n-1; i++) fprintf(fs, "%d ", lattice[i].immu);
  fprintf(fs, "%d\n", lattice[n*n-1].immu);

  return 0;
}

/* latticeLoad() lee la data de una red guardada con la funcion latticeSave() */

int latticeLoadFromFile(agent** lattice, FILE* fs){
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
  st = fscanf(fs, "%d\n", &qF);
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

  /* voy a leer los vacc */
  st = fscanf(fs, "vacc ");
  int vacc;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &vacc);
    auxLatt[idx].vacc = vacc;
  }
  st = fscanf(fs, "%d\n", &vacc);
  auxLatt[n*n-1].vacc = vacc;

  /* voy a leer los immu */
  st = fscanf(fs, "immu ");
  int immu;
  for(int idx = 0; idx<n*n-1; idx++){
    st = fscanf(fs, "%d ", &immu);
    auxLatt[idx].immu = immu;
  }
  st = fscanf(fs, "%d\n", &immu);
  auxLatt[n*n-1].immu = immu;

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
    if(lattice1[idx].vacc != lattice2[idx].vacc) return 0;
    if(lattice1[idx].immu != lattice2[idx].immu) return 0;
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

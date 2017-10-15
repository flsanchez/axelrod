#include <stdio.h>
#include <stdlib.h>
#include "misc.h"
#include "graph.h"

/* vertexEdgesInit() inicializa los edges del vertice idx y aloca la memoria
correspondiente */

int vertexEdgesInit(vertex* graph, int idx, int nEdges){

  graph[idx].nEdges = nEdges;
  graph[idx].edges = (int*) malloc(nEdges*sizeof(int));

  return 0;
}


/* vertexRewireInit() inicializa los edges del vertice idx y aloca la memoria
correspondiente */

int vertexRewireInit(vertex* graph, int idx, int nRewire){

  graph[idx].nRewire = nRewire;
  graph[idx].rewire = (int*) malloc(nRewire*sizeof(int));

  return 0;
}

/* vertexEdgesFill() llena las conexiones del nodo idx a partir de un array
  neigArray que contiene las conexiones que le corresponden */

int vertexEdgesFill(vertex* graph, int n, int* neigArray,
                    int nNeigArray, int idx){
  int idxNeig;
  for(int k = 0; k<nNeigArray; k++){
    idxNeig = neigArray[k];
    vertexEdgesAdd(graph, idx, idxNeig);
  }
  return 0;
}

/* vertexRewireFill() llena el vector de rewire con una cantidad nRewire de
  conexiones nuevas de entre los posibles candidatos disponibles en la lista
  rewArray. Si no se pudo asignar nRewire conexiones nuevas al nodo idx, se
  devuelve 1 y el fill del rewire fallo */

int vertexRewireFill(vertex* graph, int idx, int* rewArray,
                    int nRewArray, int nRewire){

  // armo un array shuffled con los indices de los vecinos de mi agente
  // y la mezclo con dist de proba uniforme
  int* shuffled = (int*) malloc(sizeof(int)*nRewArray);
  for(int i = 0; i < nRewArray; i++) shuffled[i] = rewArray[i];
  shuffleArray(shuffled, nRewArray);

  // este while se encarga de agarrar un vecino de idx para hacer
  // rewire que no este haciendo rewire previamente con el
  int cont = 0; // cuenta cuantos elementos hay dentro de graph[idx].rewire
  int shuffledIdx = 0; // recorre los indices de shuffled
  int idxj;
  while(cont < nRewire && shuffledIdx < nRewArray){

    // idxj es el vertice j que intento poner como rewire de idx
    idxj = shuffled[shuffledIdx];

    // si no esta conectado previamente, lo conecto, sino no hago nada
    if(vertexRewireIsConnected(graph, idxj, idx) == 0){
      graphEdgesAdd(graph, idxj, idx);
      graphRewireAdd(graph, idxj, idx);
      cont++;
    }

    shuffledIdx++;

  }

  free(shuffled);

  return (1-cont/nRewire);
}

/* vertexEdgesPrint() imprime todas las conexiones del vertice idx */

int vertexEdgesPrint(vertex* graph, int idx){

  int nEdges = graph[idx].nEdges;
  printf("Vertex N. %d:\nEdges: [ ",idx);
  for(int i = 0; i<nEdges; i++) printf("%d ", graph[idx].edges[i]);
  printf("]\n");
  return 0;

}

/* vertexRewirePrint() imprime todas los rewire del vertice idx */

int vertexRewirePrint(vertex* graph, int idx){

  int nRewire = graph[idx].nRewire;
  printf("Vertex N. %d:\nRewire: [ ",idx);
  for(int i = 0; i<nRewire; i++) printf("%d ", graph[idx].rewire[i]);
  printf("]; nRewire = %d\n", nRewire);
  return 0;

}

/* vertexEdgeIsConnected() devuelve 1 o 0 dependiendo de si el vertice src
esta o no conectado al vertice dest respectivamente */

int vertexEdgeIsConnected(vertex* graph, int src, int dest){

  for(int i = 0; i<graph[src].nEdges; i++){
    if(graph[src].edges[i] == dest) return 1;
  }

  return 0;
}

/* vertexRewireIsConnected() chequea si src tiene a dest como rewire
OJO: IMPORTA ORDEN! (igualmente, si i tiene como rewiring a j, dentro
de la lista de rewiring de i esta j y en la de j esta i, por eso
chequeo solo las conexiones de uno de los dos nodos, pues grafo undirected) */

int vertexRewireIsConnected(vertex* graph, int src, int dest){

  for(int i = 0; i<graph[src].nRewire; i++){
    if(graph[src].rewire[i] == dest) return 1;
  }

  return 0;
}

/* vertexEdgesAdd() añade un elemento a la lista de edges del vertice
realocando la memoria en el medio y cambiando el atributo del numero de
conexiones en los vertices src y dest, (NO CHEQUEA SI HAY CONEXION)*/

int vertexEdgesAdd(vertex* graph, int src, int dest){

  graph[src].edges = (int*) realloc(graph[src].edges,
                                    sizeof(int)*(graph[src].nEdges+1));
  graph[src].edges[graph[src].nEdges] = dest;
  graph[src].nEdges++;

  return 0;
}

/* vertexEdgesRm() remueve la conexion dest del vector de conexiones del
vertice src */

int vertexEdgesRm(vertex* graph, int src, int dest){

  int i = 0;
  int swap, aux;
  int idx = -1;
  //busco el indice de dest dentro de la lista de conexiones de graph[src] y
  //hago un swap entre dest y el ultimo elemento
  if(graph[src].nEdges != 0){
    while(idx == -1){
      if(graph[src].edges[i] == dest) {
        idx = i;
        aux = graph[src].edges[idx];
        graph[src].edges[idx] = graph[src].edges[graph[src].nEdges-1];
        graph[src].edges[graph[src].nEdges-1] = aux;
      }
      else i++;
    }

    graph[src].edges = (int*) realloc(graph[src].edges,
                                      sizeof(int)*(graph[src].nEdges-1));
    graph[src].nEdges--;
  }

  return 0;

}

/* vertexRewireAdd() añade un elemento a la lista de rewire del vertice
realocando la memoria en el medio y cambiando el atributo del numero de
conexiones en los vertices src y dest, (NO CHEQUEA SI HAY CONEXION) */

int vertexRewireAdd(vertex* graph, int src, int dest){

  graph[src].rewire = (int*) realloc(graph[src].rewire,
                                      sizeof(int)*(graph[src].nRewire+1));
  graph[src].rewire[graph[src].nRewire] = dest;
  graph[src].nRewire++;

  return 0;
}

/* vertexRewireRm() remueve la conexion dest de la lista de rewire del agente
src */

int vertexRewireRm(vertex* graph, int src, int dest){

  int i = 0;
  int swap, aux;
  int idx = -1;
  //busco el indice de dest dentro de la lista de rewire de graph[src] y
  //hago un swap entre dest y el ultimo elemento
  if(graph[src].nRewire != 0){
    while(idx == -1){
      if(graph[src].rewire[i] == dest) {
        idx = i;
        aux = graph[src].rewire[idx];
        graph[src].rewire[idx] = graph[src].rewire[graph[src].nRewire-1];
        graph[src].rewire[graph[src].nRewire-1] = aux;
      }
      else i++;
    }

    graph[src].rewire = (int*) realloc(graph[src].rewire,
                                        sizeof(int)*(graph[src].nRewire-1));
    graph[src].nRewire--;
  }

  return 0;

}

/* graphInit() inicializa todos los atributos de cada uno de los vertices del
  grafo vertex* graph, poniendo todo a cero y con NULL los vectores de rewire y
  edges */

int graphInit(vertex* graph, int n){
  graphEdgesInit(graph, n);
  graphRewireInit(graph, n);
  return 0;
}

/* graphEdgesInit() inicializa a 0 los edges de cada vertice */

int graphEdgesInit(vertex* graph, int n){
  for(int i = 0; i < n*n; i++) vertexEdgesInit(graph,i,0);
  return 0;
}

/* graphRewireInit() inicializa a 0 los rewire de cada vertice */

int graphRewireInit(vertex* graph, int n){
  for(int i = 0; i < n*n; i++) vertexRewireInit(graph,i,0);
  return 0;
}

/* graphEdgesFill() se encarga de llenar el vector de conexiones */

int graphEdgesFill(vertex* graph, int n, int neigOrdEdges){
  int* patterni; // guardo los indices i de los vecinos admitidos
  int* patternj; // guardo los indices j de los vecinos admitidos
  int nNeigArray; // tamaño de neigArray
  int nPattern; // el tamaño de los vectores patterni y patternj

  //lleno los pattern dependiendo de la topologia de la red (orden de vecinos)
  nPattern = patternFill(&patterni, &patternj, n, neigOrdEdges);

  // lleno los edges con sus respectivos vecinos
  for(int idx = 0; idx < n*n ; idx++){
    int* neigArray; // lista con vecinos admitidos para cada idx
    // lleno la lista con los vecinos que admite cada idx
    nNeigArray = fillNeigArray(patterni, patternj, nPattern, &neigArray, idx, n);
    // lleno los edges desde la lista de vecinos neigArray
    vertexEdgesFill(graph, n, neigArray, nNeigArray, idx);
    free(neigArray);
  }
  free(patterni);
  free(patternj);
  return 0;
}

/* graphRewireFill() se encarga de llenar el vector de REWIRE para
  una cantidad nEdgeRew de vertices contenidos en el grafo, eligiendo para
  cada vertice seleccionado un numero nRewire de vecinos o no vecinos de orden
  neigOrdRewire para asignar. Si neigOrdRewire = neigOrdEdges, elige de vecinos
  sino elige del orden de vecinos de neigOrdRewire */

int graphRewireFill(vertex* graph, int n, int nEdgeRew, int nRewire,
                    int neigOrdEdges, int neigOrdRewire){

  /* idxList guarda en la posicion i el valor i */
  int idx;
  int* idxList = malloc(n*n*sizeof(int));
  for(int i = 0; i<n*n; i++) idxList[i] = i; // lleno con los indices de la red
  shuffleArray(idxList, n*n); //mezclo el array

  int* patterni; // guardo los indices i de los vecinos admitidos
  int* patternj; // guardo los indices j de los vecinos admitidos
  int nNeigArray; // tamaño de neigArray
  int nPattern; // el tamaño de los vectores patterni y patternj
  //lleno los pattern dependiendo de la topologia de la red (orden de vecinos)
  nPattern = patternFill(&patterni, &patternj, n, neigOrdRewire);

  int control = 0; // flag de control, por si vertexRewireFill sale mal, se
                   // pone a 1 y se repite el loop de llenado de rewire
  int i = 0;
  while(i < nEdgeRew){
    idx = idxList[i];
    int* neigArray; // lista con vecinos admitidos para cada idx
    // lleno la lista con los vecinos que admite cada idx
    nNeigArray = fillNeigArray(patterni, patternj, nPattern, &neigArray, idx, n);
    control = vertexRewireFill(graph, idx, neigArray, nNeigArray, nRewire);
    free(neigArray);
    i++;
    // si control se pone a 1 o el nodo idx tiene todos sus links de rewire,
    // se arranca de nuevo con el llenado desde el 0
    if(control == 1 || graph[idx].nRewire == graph[idx].nEdges){
      // libero los vectores de rewire y edges
      graphFree(graph, n);
      // inicializo de nuevo
      graphInit(graph, n);
      graphEdgesFill(graph, n, neigOrdEdges);
      i = 0;
    }
  }

  free(patterni);
  free(patternj);
  free(idxList);

  return 0;
}

int graphFill(vertex* graph, int n, int nEdgeRew, int nRewire,
              int neigOrdEdges, int neigOrdRewire)
{
  graphEdgesFill(graph, n, neigOrdEdges);
  graphRewireFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);
  return 0;
}

/* graphEdgesAdd() añade el elemento conecta los vertices src y dest
(pues grafo undirected) */

int graphEdgesAdd(vertex* graph, int src, int dest){

  if(vertexEdgeIsConnected(graph,src,dest) == 0 && (src != dest)){
    vertexEdgesAdd(graph, src, dest);
    vertexEdgesAdd(graph, dest, src);
    return 0;
  }

  return 1;

}

/* graphEdgesRm() elimina la conexion entre src y dest en caso de existir */

int graphEdgesRm(vertex* graph, int src, int dest){

  if(vertexEdgeIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexEdgesRm(graph, src, dest);
    vertexEdgesRm(graph, dest, src);
    return 0;
  }

  return 1;

}

/* graphRewireAdd() agrega el link src-dest como link de reconexion */

int graphRewireAdd(vertex* graph, int src, int dest){
  //pregunto ademas si esta conectado para que no haya problemas
  if(vertexRewireIsConnected(graph,src,dest) == 0 &&
      vertexEdgeIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexRewireAdd(graph, src, dest);
    vertexRewireAdd(graph, dest, src);
    return 0;
  }

  return 1;

}

/* graphRewireRm() elimina el link src-dest como link de reconexion */

int graphRewireRm(vertex* graph, int src, int dest){

  if(vertexRewireIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexRewireRm(graph, src, dest);
    vertexRewireRm(graph, dest, src);
    return 0;
  }

  return 1;

}

/* graphEdgesAddNRand() añade sobre la red una cantidad de links nRandEdges al
  azar sobre la red entre no vecinos */

int graphEdgesAddNRand(vertex* graph, int n, int nRandEdges){
  int i = 0;
  int j = 0;
  for(int cont = 0; cont<nRandEdges; cont++){
    i = getRand(n*n); //elijo un agente al azar
    j = graphPickPassiveNotNeig(graph, n, i);  //elijo un no vecino del agente i azar
    graphEdgesAdd(graph, i, j);
  }
  return 0;
}

/* graphEdgesPrint() imprime el vector de conexiones para cada uno de los
vertices */

int graphEdgesPrint(vertex* graph, int n){
  for(int i = 0; i<n*n; i++) vertexEdgesPrint(graph,i);
  return 0;
}

/* graphPrintToFile() imprime la lista de adyacencias a un archivo */

int graphPrintToFile(vertex* graph, int n, FILE *fs){

  int nEdges,nRewire;
  fprintf(fs, "# n %d\n",n);
  for(int idx = 0; idx<n*n; idx++){
    nEdges = graph[idx].nEdges;
    for(int j=0; j<nEdges; j++) fprintf(fs, "%d,%d ", idx,graph[idx].edges[j]);
  }
  fprintf(fs, "\n");
  for(int idx = 0; idx<n*n; idx++){
    nRewire = graph[idx].nRewire;
    for(int j=0; j<nRewire; j++) fprintf(fs, "%d,%d ", idx,graph[idx].rewire[j]);
  }
  fprintf(fs, "\n");

  return 0;
}

/* graphRewirePrint() imprime el vector de rewire para cada uno de los
vertices */

int graphRewirePrint(vertex* graph, int n){
  for(int i = 0; i<n*n; i++) vertexRewirePrint(graph,i);
  return 0;
}

/* graphPickPassiveNeig() agarra un vecino al azar del agente i, usando la lista de
conexiones */

int graphPickPassiveNeig(vertex* graph, int i){
  int idx = getRand(graph[i].nEdges);
  return graph[i].edges[idx];
}

/* graphPickPassiveNotNeig() agarra un NO vecino al azar del agente i */

int graphPickPassiveNotNeig(vertex* graph, int n, int i){
  int idx = getRand(n*n);
  while((vertexEdgeIsConnected(graph,i,idx) || idx == i)){
    idx = getRand(n*n);
  }
  return idx;
}

/* graphEdgesFree() libera todos los array de edges */

int graphEdgesFree(vertex* graph, int n){
  for(int i = 0; i < n*n; i++) free(graph[i].edges);
  return 0;
}

/* graphRewireFree() libera todos los arrays de rewire */

int graphRewireFree(vertex* graph, int n){
  for(int i = 0; i < n*n; i++) free(graph[i].rewire);
  return 0;
}

/* graphFree() libera la memoria del grafo, liberando todos los mallocs hechos
en cada uno de los vertices primero */

int graphFree(vertex* graph, int n){
  graphEdgesFree(graph, n);
  graphRewireFree(graph, n);
  return 0;
}

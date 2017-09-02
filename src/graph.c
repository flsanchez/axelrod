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

/* vertexEdgesAssignNumber() se encarga de decir cuantas conexiones
corresponden al vertice idx, dependiendo de si inicialmente el mismo
se encuentra en una punta, un borde o el interior del grafo, con neigOrdEdges
poniendo conexiones a neigOrdEdges = 1 (1eros) o neigOrdEdges = 2 (2dos) vecinos*/

int vertexEdgesAssignNumber(int idx, int n, int neigOrdEdges){
  int i = idx/n;
  int j = idx%n;
  int puntas, bordes, interior,casiPuntas;
  if(neigOrdEdges == 1){
    puntas = 2;
    bordes = 3;
    interior = 4;
  }
  else if(neigOrdEdges == 2){
    puntas = 3;
    bordes = 5;
    interior = 8;
  }
  else if(neigOrdEdges == 3){
    puntas = 5;
    casiPuntas = 6;
    bordes = 9;
    interior = 16;
  }

  if(neigOrdEdges == 1 || neigOrdEdges == 2){
    if( (i == 0 || i == n-1) && (j == 0 || j == n-1) ) return puntas;
    else if( i == 0 || i == n-1 || j == 0 || j == n-1 ) return bordes;
    else return interior;
  }
  else if(neigOrdEdges == 3){
    if( (i == 0 || i == n-1) && (j == 0 || j == n-1) ) return puntas;
    else if( (i == 1 || i == n-2) && (j == 0 || j == n-1) ||
             (i == 0 || i == n-1) && (j == 1 || j == n-2) ) return casiPuntas;
    else if( i == 0 || i == n-1 || j == 0 || j == n-1 ) return bordes;
    else return interior;
  }
}

/* vertexEdgesFill() llena el vector de conexiones del vertice, en funcion
de la topologia que se programe , con neigOrdEdges poniendo conexiones a
neigOrdEdges = 1 (1eros) o neigOrdEdges = 2 (2dos) vecinos */

int vertexEdgesFill(int* edges, int n, int idx, int neigOrdEdges){

  int i = idx/n;
  int j = idx%n;

  if(neigOrdEdges == 1){
    if(i == 0){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx + n;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx + n;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx + n;
      }
    }
    else if(i == n-1){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx - n;
      }
    }
    else{
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
      }
      else{
        edges[0] = idx - n;
        edges[1] = idx - 1;
        edges[2] = idx + 1;
        edges[3] = idx + n;
      }
    }
  }
  if(neigOrdEdges == 2){
    if(i == 0){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx + n;
        edges[2] = idx + n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx + n;
        edges[2] = idx + n - 1;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx + n;
        edges[3] = idx + n - 1;
        edges[4] = idx + n + 1;
      }
    }
    else if(i == n-1){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
        edges[2] = idx - n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
        edges[2] = idx - n - 1;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx - n;
        edges[3] = idx - n + 1;
        edges[4] = idx - n - 1;
      }
    }
    else{
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
        edges[3] = idx - n + 1;
        edges[4] = idx + n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
        edges[3] = idx - n - 1;
        edges[4] = idx + n -1;
      }
      else{
        edges[0] = idx - n;
        edges[1] = idx - 1;
        edges[2] = idx + 1;
        edges[3] = idx + n;
        edges[4] = idx - n + 1;
        edges[5] = idx - n - 1;
        edges[6] = idx + n + 1;
        edges[7] = idx + n - 1;
      }
    }
  }
  if(neigOrdEdges == 3){
    if(i == 0){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx + n;
        edges[2] = idx + n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx + n;
        edges[2] = idx + n - 1;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx + n;
        edges[3] = idx + n - 1;
        edges[4] = idx + n + 1;
      }
    }
    else if(i == n-1){
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
        edges[2] = idx - n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
        edges[2] = idx - n - 1;
      }
      else{
        edges[0] = idx - 1;
        edges[1] = idx + 1;
        edges[2] = idx - n;
        edges[3] = idx - n + 1;
        edges[4] = idx - n - 1;
      }
    }
    else{
      if(j == 0){
        edges[0] = idx + 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
        edges[3] = idx - n + 1;
        edges[4] = idx + n + 1;
      }
      else if (j == n-1){
        edges[0] = idx - 1;
        edges[1] = idx - n;
        edges[2] = idx + n;
        edges[3] = idx - n - 1;
        edges[4] = idx + n -1;
      }
      else{
        edges[0] = idx - n;
        edges[1] = idx - 1;
        edges[2] = idx + 1;
        edges[3] = idx + n;
        edges[4] = idx - n + 1;
        edges[5] = idx - n - 1;
        edges[6] = idx + n + 1;
        edges[7] = idx + n - 1;
      }
    }
  }
  return 0;
}

/* vertexRewireFill() llena el vector de rewire dependiendo de cuantas
conexiones aleatorias se hayan determinado, y ademas teniendo en cuenta de
que no haya conexiones mutuas disponibles para el rewire (i.e., evita que
i tenga a j como rewire y j a i al mismo tiempo). En caso de que no haya
rewiring posible (porque idx tiene a todos sus vecinos conectados), esta
funcion devuelve 1 */

/* tengo que agregar el vector de posibles rewire(y su tamaño), y eso copiarlo en shuffled*/

int vertexRewireFill(vertex* graph, int idx, int* rewArray, int nRewArray, int nRewire){

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

  graph[src].edges = (int*) realloc(graph[src].edges,sizeof(int)*(graph[src].nEdges+1));
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

    graph[src].edges = (int*) realloc(graph[src].edges,sizeof(int)*(graph[src].nEdges-1));
    graph[src].nEdges--;
  }

  return 0;

}

/* vertexRewireAdd() añade un elemento a la lista de rewire del vertice
realocando la memoria en el medio y cambiando el atributo del numero de
conexiones en los vertices src y dest, (NO CHEQUEA SI HAY CONEXION) */

int vertexRewireAdd(vertex* graph, int src, int dest){

  graph[src].rewire = (int*) realloc(graph[src].rewire,sizeof(int)*(graph[src].nRewire+1));
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

    graph[src].rewire = (int*) realloc(graph[src].rewire,sizeof(int)*(graph[src].nRewire-1));
    graph[src].nRewire--;
  }

  return 0;

}

/* graphInit() inicializa todos los atributos de cada uno de los vertices del
grafo vertex* graph, con neigOrdEdges poniendo conexiones a neigOrdEdges = 1 (1eros)
o neigOrdEdges = 2 (2dos) vecinos */

int graphInit(vertex* graph, int n, int neigOrdEdges){

  int nEdgesReal;

  for(int idx = 0; idx < n*n ; idx++){
    nEdgesReal = vertexEdgesAssignNumber(idx, n, neigOrdEdges);
    vertexEdgesInit(graph, idx, nEdgesReal);
  }
  graphRewireInit(graph, n);

  return 0;
}

int graphRewireInit(vertex* graph, int n){
  for(int i = 0; i < n*n; i++) vertexRewireInit(graph,i,0);
  return 0;
}

/* graphEdgesFill() se encarga de llenar el vector de conexiones */

int graphEdgesFill(vertex* graph, int n, int neigOrdEdges){
  // lleno los edges con sus respectivos vecinos
  for(int idx = 0; idx < n*n ; idx++){
    vertexEdgesFill(graph[idx].edges, n, idx, neigOrdEdges);
  }
  return 0;
}

/* graphRewireFillNeig() se encarga de llenar el vector de REWIRE para
una cantidad nEdgeRew de vertices contenidos en el grafo, eligiendo para
cada vertice seleccionado un numero nRewire de vecinos */

int graphRewireFillNeig(vertex* graph, int n, int nEdgeRew, int nRewire, int neigOrdEdges){

  /* idxList guarda en la posicion i el valor i */
  int idx;
  int* idxList = malloc(n*n*sizeof(int));
  for(int i = 0; i<n*n; i++) idxList[i] = i;
  shuffleArray(idxList, n*n); //mezclo el array

  int control = 0; // flag de control, por si vertexRewireFill sale mal, se
                   // pone a 1 y se repite el loop de llenado de rewire
  int i = 0;

  while(i < nEdgeRew){
    idx = idxList[i];
    control = vertexRewireFill(graph, idx, graph[idx].edges, graph[idx].nEdges, nRewire);
    i++;
    // si control se pone a 1 o el nodo idx tiene todos sus links de rewire,
    // se arranca de nuevo con el llenado desde el 0
    if(control == 1 || graph[idx].nRewire == graph[idx].nEdges){
      // libero los vectores de rewire y edges
      graphFree(graph, n);
      // inicializo de nuevo
      graphInit(graph, n, neigOrdEdges);
      graphEdgesFill(graph, n, neigOrdEdges);
      i = 0;
    }
  }

  free(idxList);

  return 0;
}

/* graphRewireFillNeigAux() llena los rewires con los vecinos para cada agente de la
  red, teniendo en cuenta que haya efectivamente N links en el sistema, i.e.,
  que no haya conexiones mutuas. Si tengo algun vertice donde todos los edges
  pueden hacer rewire, se devuelve 1 y se tiene que correr de nuevo. sino
  se devuelve 0 */


/* graphRewireFillNotNeig() llena el vector de rewire de una cantidad nEdgeRew
  de vertices del grafo, eligiendo nRewire no vecinos de orden neigOrdEdges*/

int graphRewireFillNotNeig(vertex* graph, int n, int nEdgeRew, int nRewire, int neigOrdEdges){

  /* idxList guarda en la posicion i el valor i */
/*  int idx, neigNmbr;
  int* rewire = NULL;
  int* idxList = malloc(n*n*sizeof(int));
  for(int i = 0; i<n*n; i++) idxList[i] = i;
  shuffleArray(idxList, n*n); //mezclo el array

  // inicializo los array de rewire
  graphRewireInit(graph, n, idxList, nEdgeRew, nRewire);

  for(int i = 0; i < nEdgeRew; i++){
    idx = idxList[i];
    neigNmbr = vertexEdgesAssignNumber(idx, n, neigOrdEdges);
    rewire = realloc(rewire,neigNmbr*sizeof(int));
    vertexEdgesFill(rewire, n, idx, neigOrdEdges); // me llena con los neigOrdEdges vecinos
    shuffleArray(rewire, neigNmbr); // mezclo los rewire
    for(int neigIdx = 0; neigIdx < nRewire; neigIdx++){
      graphEdgesAdd(graph, idx, rewire[neigIdx]);
      graphRewireAdd(graph, idx, rewire[neigIdx]);
    }
  }

  free(rewire);
  free(idxList);

  return 0;*/
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

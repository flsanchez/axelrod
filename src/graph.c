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
  if(graph[idx].rewire != NULL){
    free(graph[idx].rewire);
  }
  graph[idx].nRewire = nRewire;
  graph[idx].rewire = (int*) malloc(nRewire*sizeof(int));

  return 0;
}

/* vertexEdgesAssignNumber() se encarga de decir cuantas conexiones
corresponden al vertice idx, dependiendo de si inicialmente el mismo
se encuentra en una punta, un borde o el interior del grafo, con neigOrd
poniendo conexiones a neigOrd = 1 (1eros) o neigOrd = 2 (2dos) vecinos*/

int vertexEdgesAssignNumber(int idx, int n, int neigOrd){
  int i = idx/n;
  int j = idx%n;
  int puntas;
  int bordes;
  int interior;
  if(neigOrd == 1){
   puntas = 2;
   bordes = 3;
   interior = 4;
  }
  else if(neigOrd == 2){
   puntas = 3;
   bordes = 5;
   interior = 8;
  }
  if( (i == 0 || i == n-1) && (j == 0 || j == n-1) ) return puntas;
  else if( i == 0 || i == n-1 || j == 0 || j == n-1 ) return bordes;
  else return interior;
}

/* vertexEdgesFill() llena el vector de conexiones del vertice, en funcion
de la topologia que se programe , con neigOrd poniendo conexiones a
neigOrd = 1 (1eros) o neigOrd = 2 (2dos) vecinos */

int vertexEdgesFill(int* edges, int n, int idx, int neigOrd){

  int i = idx/n;
  int j = idx%n;

  if(neigOrd == 1){
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
  else if(neigOrd == 2){
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

int vertexRewireFill(vertex* graph, int idx){

  // armo un array shuffled con los indices de los vecinos de mi agente
  // y la mezclo con dist de proba uniforme

  int* shuffled = (int*) malloc(sizeof(int)*graph[idx].nEdges);
  for(int i = 0; i<graph[idx].nEdges; i++) shuffled[i] = graph[idx].edges[i];
  shuffleArray(shuffled,graph[idx].nEdges);

  // este while anidado se encarga de agarrar un vecino de idx para hacer
  // rewire que no este haciendo rewire previamente

  int cont = 0; // cuenta cuantos elementos hay dentro de graph[idx].rewire
  int shuffledIdx = 0; // recorre los indices de shuffled
  int flag,rewIdx,idxj;
  while(cont < graph[idx].nRewire && shuffledIdx < graph[idx].nEdges){
    // si el de la lista al azar es mayor a idx, lo guardo directamente pues
    // el rewire con un indice mayor a idx no trae problemas. Si el de la lista
    // es menor, tengo que chequear posibles problemas de conexion mutua
    if(shuffled[shuffledIdx] > idx){
      graph[idx].rewire[cont] = shuffled[shuffledIdx];
      cont++;
    }
    else{
      // idxj es el agente j con el que intento poner como rewire de idx
      idxj = shuffled[shuffledIdx];

      // recorro graph[idxj].rewire para ver si esta conectdo a idx por rewire
      flag = 0;
      rewIdx = 0;
      while(rewIdx < graph[idxj].nRewire && flag == 0){
        // si hay conexion, rompo el loop y descarto el elemento
        if(graph[idxj].rewire[rewIdx] == idx) flag = 1;
        rewIdx++;
      }

      // si no esta conectado previamente, lo conecto, sino no hago nada
      if(flag == 0){
        graph[idx].rewire[cont] = shuffled[shuffledIdx];
        cont++;
      }

    }

    shuffledIdx++;

  }

  free(shuffled);

  return shuffledIdx/graph[idx].nEdges;
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
grafo vertex* graph, con neigOrd poniendo conexiones a neigOrd = 1 (1eros)
o neigOrd = 2 (2dos) vecinos */

int graphInit(vertex* graph, int n, int neigOrd){

  int nEdgesReal;

  for(int idx = 0; idx < n*n ; idx++){
    nEdgesReal = vertexEdgesAssignNumber(idx, n, neigOrd);
    vertexEdgesInit(graph, idx, nEdgesReal);
  }

  return 0;
}

/* graphFill() se encarga de llenar el vector de conexiones y EL REWIRE para
cada uno de los vertices contenidos en el grafo, con neigOrd poniendo
conexiones a neigOrd = 1 (1eros) o neigOrd = 2 (2dos) vecinos */

int graphFill(vertex* graph, int n, int neigOrd, int nEdgeRew, int nRewire){

  // lleno los edges con sus respectivos vecinos

  for(int idx = 0; idx < n*n ; idx++){
    vertexEdgesFill(graph[idx].edges, n, idx, neigOrd);
  }

  /* idxList guarda en la posicion i el valor i */

  int* idxList = malloc(n*n*sizeof(int));
  for(int i = 0; i<n*n; i++) idxList[i] = i;
  shuffleArray(idxList,n*n); //mezclo el array
  int rewireFlag = 1; // si este flag se pone a 0, es seguro que cada nodo tiene
                      // al menos un link que no es de rewire

  //int try = 0;
  while(rewireFlag == 1){

    /* inicializo los primeros nEdgeRew con nRewire links de rewire */
    for(int idx = 0; idx < nEdgeRew ; idx++) vertexRewireInit(graph,idx,nRewire);
    /* inicializo n*n-nEdgeRew nodos de idxList con 0 links de rewire */
    for(int idx = nEdgeRew; idx < n*n; idx++) vertexRewireInit(graph,idx,0);
    /* proceso de llenado de rewire */
    rewireFlag = graphFillRewire(graph, n);
    /*try++;
    printf("Try %d\n", try);*/

  }

  free(idxList);

  return 0;
}

/* graphFillRewire() llena los rewires con los vecinos para cada agente de la
  red, teniendo en cuenta que haya efectivamente N links en el sistema, i.e.,
  que no haya conexiones mutuas. Si tengo algun vertice donde todos los edges
  pueden hacer rewire, se devuelve 1 y se tiene que correr de nuevo. sino
  se devuelve 0 */

int graphFillRewire(vertex* graph, int n){

  int control = 0; // flag de control, por si vertexRewireFill sale mal, se
                   // pone a 1 y se repite el loop de llenado de rewire
  int idx = 0;
  //int tries = 0;
  while(idx < n*n){
    control = vertexRewireFill(graph, idx);
    idx++;
    // si control se pone a 1, se arranca de nuevo con el llenado desde el 0
    if(control == 1){
      idx = 0;
      //tries++;
    }
  }

  /* para cada agente i, miro los vecinos j de este y si i esta en la lista de
  rewire de j, agrego j a la lista de rewire de i */

  int j;
  for(int i = 0; i<n*n; i++){

    for(int idxj = 0; idxj<graph[i].nEdges; idxj++){
      j = graph[i].edges[idxj]; //vecino j
      for(int idxRew = 0; idxRew<graph[j].nRewire ; idxRew++){
        if(graph[j].rewire[idxRew] == i && vertexRewireIsConnected(graph,i,j) == 0){
          vertexRewireAdd(graph, i, j);
        }
      }
    }

    // si todos los links son de rewire, devuelvo 1
    if(graph[i].nEdges == graph[i].nRewire) return 1;

  }

  // si todo salio bien, devuelvo 0
  return 0;

}

/* graphEdgesAdd() añade el elemento conecta los vertices src y dest
(pues grafo undirected) */

int graphEdgesAdd(vertex* graph, int src, int dest){

  if(vertexEdgeIsConnected(graph,src,dest) == 0 && (src != dest)){
    vertexEdgesAdd(graph, src, dest);
    vertexEdgesAdd(graph, dest, src);
  }

  return 0;

}

/* graphEdgesRm() elimina la conexion entre src y dest en caso de existir */

int graphEdgesRm(vertex* graph, int src, int dest){

  if(vertexEdgeIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexEdgesRm(graph, src, dest);
    vertexEdgesRm(graph, dest, src);
  }

  return 0;

}

/* graphRewireAdd() agrega el link src-dest como link de reconexion */

int graphRewireAdd(vertex* graph, int src, int dest){
  //pregunto ademas si esta conectado para que no haya problemas
  if(vertexRewireIsConnected(graph,src,dest) == 0 &&
      vertexEdgeIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexRewireAdd(graph, src, dest);
    vertexRewireAdd(graph, dest, src);
  }

  return 0;

}

/* graphRewireRm() elimina el link src-dest como link de reconexion */

int graphRewireRm(vertex* graph, int src, int dest){

  if(vertexRewireIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexRewireRm(graph, src, dest);
    vertexRewireRm(graph, dest, src);
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

/* graphFree() libera la memoria del grafo, liberando todos los mallocs hechos
en cada uno de los vertices primero */

int graphFree(vertex* graph, int n){
  for(int i = 0; i < n*n; i++){
    free(graph[i].edges);
    free(graph[i].rewire);
  }
  free(graph);
  return 0;
}

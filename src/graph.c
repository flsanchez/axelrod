#include <stdio.h>
#include <stdlib.h>
#include "misc.h"
#include "graph.h"

/* vertexInit() inicializa los atributos del vertice idx y aloca la memoria
correspondiente */

int vertexInit(vertex* graph, int idx, int nEdges, int nRewire){
  graph[idx].nEdges = nEdges;
  graph[idx].edges = (int*) malloc(nEdges*sizeof(int));

  if(nRewire>nEdges) graph[idx].nRewire = nEdges;
  else graph[idx].nRewire = nRewire;

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
conexiones aleatorias se hayan determinado */

int vertexRewireFill(vertex* graph, int idx){

  int* shuffled = (int*) malloc(sizeof(int)*graph[idx].nEdges);
  for(int i = 0; i<graph[idx].nEdges; i++) shuffled[i] = graph[idx].edges[i];
  shuffleArray(shuffled,graph[idx].nEdges);
  for(int i = 0; i<graph[idx].nRewire; i++) graph[idx].rewire[i] = shuffled[i];
  free(shuffled);

  return 0;
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
  printf("]\n");
  return 0;

}

/* vertexIsConnected() devuelve 1 o 0 dependiendo de si el vertice src
esta o no conectado al vertice dest respectivamente */

int vertexIsConnected(vertex* graph, int src, int dest){

  for(int i = 0; i<graph[src].nEdges; i++){
    if(graph[src].edges[i] == dest) return 1;
  }

  return 0;
}

/* vertexEdgesAdd() añade un elemento a la lista de edges del vertice
realocando la memoria en el medio y cambiando el atributo del numero de
conexiones en los vertices src y dest, (NO CHEQUEA SI HAY CONEXION)*/

int vertexEdgesAdd(vertex* graph, int src, int dest){

  /*int* newEdges = (int*) malloc( sizeof(int) * (graph[src].nEdges+1) );
  for(int i = 0; i<graph[src].nEdges; i++) newEdges[i] = graph[src].edges[i];
  newEdges[graph[src].nEdges] = dest;
  graph[src].nEdges++;
  free(graph[src].edges);
  graph[src].edges = newEdges;*/

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

  return 0;

}

/* graphInit() inicializa todos los atributos de cada uno de los vertices del
grafo vertex* graph, con neigOrd poniendo conexiones a neigOrd = 1 (1eros)
o neigOrd = 2 (2dos) vecinos */

int graphInit(vertex* graph, int n, int nRewire, int neigOrd){

  int nEdgesReal;
  for(int idx = 0; idx < n*n ; idx++){
    nEdgesReal = vertexEdgesAssignNumber(idx, n, neigOrd);
    vertexInit(graph, idx, nEdgesReal, nRewire);
  }

  return 0;
}

/* graphFill() se encarga de llenar el vector de conexiones y EL REWIRE para
cada uno de los vertices contenidos en el grafo, con neigOrd poniendo
conexiones a neigOrd = 1 (1eros) o neigOrd = 2 (2dos) vecinos */

int graphFill(vertex* graph, int n, int neigOrd){
  for(int idx = 0; idx < n*n ; idx++){
    vertexEdgesFill(graph[idx].edges, n, idx, neigOrd);
    vertexRewireFill(graph, idx);
  }
  return 0;
}

/* graphEdgesAdd() añade el elemento conecta los vertices src y dest
(pues grafo undirected) */

int graphEdgesAdd(vertex* graph, int src, int dest){

  if(vertexIsConnected(graph,src,dest) == 0 && (src != dest)){
    vertexEdgesAdd(graph, src, dest);
    vertexEdgesAdd(graph, dest, src);
  }

  return 0;

}

/* graphEdgesRm() elimina la conexion entre src y dest en caso de existir */

int graphEdgesRm(vertex* graph, int src, int dest){

  if(vertexIsConnected(graph,src,dest) == 1 && (src != dest)){
    vertexEdgesRm(graph, src, dest);
    vertexEdgesRm(graph, dest, src);
  }

  return 0;

}

/* graphEdgesPrint() imprime el vector de conexiones para cada uno de los
vertices */

int graphEdgesPrint(vertex* graph, int n){
  for(int i = 0; i<n*n; i++) vertexEdgesPrint(graph,i);
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

#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex
{
  struct agent* Agent;//agente del nodo
  int nEdges;  //numero de conexiones
  struct adjList* edges;  //lista de adyacencias, con los indices de los vecinos en cada
               //componente
  int nRewire; //numero de conexiones que admiten rewire
  int *rewire; //vector de rewire, contiene los indices del vector de edges que
               //admiten rewire
} vertex;



#endif

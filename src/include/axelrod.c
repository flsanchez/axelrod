#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "misc.h"
#include "axelrod.h"

/* step() es la funcion encargada de realizar el paso tempora de axelrod, si
hubo rewiring devuelve 1, si hubo imitacion devuelve 0 */

int step(vertex* graph, agent *lattice, int n, float phi){

  int i, j, hij;
  int th = 1; //threshold de interaccion
  i = getRand(n*n); //indice del activo

  float r = ((float) rand() / (float) RAND_MAX);
  // con probabilidad phi interactuo con el campo
  if(r < phi) return fieldInteraction(lattice, i);
  // sino interactua con el campo, hago el proceso de axelrod convencional
  else{
    while(graph[i].nEdges == 0) i = getRand(n*n); //elijo un agente CON vecinos
    j = graphPickPassiveNeig(graph, i); //indice del pasivo(vecino al azar)

    hij = commonTraits(lattice, i, j);

    if(vertexRewireIsConnected(graph, i, j)){

      int k = graphPickPassiveNotNeig(graph, n, i);
      int hik = commonTraits(lattice, i, k);

      if(hij < hik) return socialInteraction(graph, i, j, k);
      else opinionInteraction(lattice, i, j, hij, th, phi);

    }
    else opinionInteraction(lattice, i, j, hij, th, phi);
  }

  return 0;

}

/* maxCluster() devuelve el tamanio del cluster mas grande */

int maxCluster(agent *lattice, int* nsAcum, int n, int frag){

  //fragsz[i] contiene el tamaño del cluster de etiqueta i
  int *fragsz = malloc(frag*sizeof(int));
  //ns[i] contiene cuantos clusters de tamaño i-1 se encontraron en la red
  int *ns = malloc(n*n*sizeof(int));

  for(int i = 0; i<frag; i++) fragsz[i] = 0;
  for(int i = 0; i<n*n; i++) ns[i] = 0;

  clusterSize(lattice, n, frag, fragsz, ns);

  if(nsAcum != NULL) for(int i = 0; i<n*n; i++) nsAcum[i] = ns[i] + nsAcum[i];

  int mayor = 0;

  for(int i = 1; i<frag; i++) if(fragsz[i]>mayor) mayor = fragsz[i];

  free(fragsz);
  free(ns);

  return mayor;

}

/* clusterSize() hace la distribucion de fragmentos sobre la red labeleada*/

int clusterSize(agent *lattice, int n, int frag, int *fragsz, int *ns){

	for(int i=0 ; i<n*n; i++) fragsz[lattice[i].label]++;
	fragsz[0] = 0;  //lo pongo a 0 a mano, ya que conte cuantos 0 hay en la red

	for(int i=1 ; i<frag; i++) if(fragsz[i]!=0) ns[fragsz[i]-1]++;

  return 0;

}

/* opinionInteraction() realiza el intercambio de opiniones entre los agentes
i y j con homofilia hij */

int opinionInteraction(agent* lattice, int i, int j, int hij, int th, float phi){

  int uncomTrait, f;
  float prob;
  float r;
  f = lattice[i].f;

  if(hij >= th) prob = (float) hij / f;
  else prob = 0;

  r = ((float) rand() / (float) RAND_MAX);

  if( r < prob ){

    if(hij != f){

      int cont = 0;
      int uncomIdx = -1;
      uncomTrait = getRand(f-hij) + 1;
      while(cont != uncomTrait){
        uncomIdx++;
        if(lattice[i].feat[uncomIdx] != lattice[j].feat[uncomIdx]) cont++;
      }

      /* si el feat elegido es el f-1 */
      if(uncomIdx == f-1){
        /* si el agente es taliban */
        if(lattice[i].stub == 1) return 0;
        /* sino hace la imitacion */
        else lattice[i].feat[uncomIdx] = lattice[j].feat[uncomIdx];

      }else lattice[i].feat[uncomIdx] = lattice[j].feat[uncomIdx];

    }

  }

  return 0;
}

/* socialInteraction() hace el rewire de i/j -> i/k, modificando
  el rewire de i, devuelve siempre 1 */

int socialInteraction(vertex* graph, int i, int j, int k){
  graphEdgesRm(graph, i, j); // desconecto la conexion entre i y j para los dos
  graphEdgesAdd(graph, i, k); // conecto i y k en ambos agentes
  graphRewireRm(graph, i, j); // desconecto el rewire entre i y j
  graphRewireAdd(graph, i, k); // conecto el rewire entre i y k
  return 1;
}

/* fieldInteraction() hace la interaccion con el campo */

int fieldInteraction(agent* lattice, int i){
  int f = lattice[i].f;
  // qInt guarda el q maximo que se va a sortear
  int qInt = lattice[i].q - lattice[i].feat[f-1];
  // si es taliban entonces 1-lattice[i].stub = 0 y el agenta queda igual
  lattice[i].feat[f-1] = lattice[i].feat[f-1] + (1-lattice[i].stub)*getRand(qInt);
  return 1;
}

/* stopReached() devuelve 0 o 1 si hay o no transiciones disponibles
respectivamente (si no hay, la interaccion es terminada) */

int stopReached(vertex* graph, agent* lattice, int n){
  int h;
  int th = 1; //threshold de la interaccion
  int f = lattice[0].f;

  for(int idx = 0; idx < n*n; idx++){
    for(int edgesIdx = 0; edgesIdx<graph[idx].nEdges; edgesIdx++){
      h = commonTraits(lattice,idx,graph[idx].edges[edgesIdx]);
      if( h != f && h >= th ) return 0;
    }
  }
  return 1;
}

/* activeLinks() devuelve la cantidad de links activos */

int activeLinks(vertex* graph, agent* lattice, int n){
  int h;
  int th = 1; //threshold de la interaccion
  int f = lattice[0].f;
  int actLinks = 0;

  for(int idx = 0; idx < n*n; idx++){
    for(int edgesIdx = 0; edgesIdx<graph[idx].nEdges; edgesIdx++){
      h = commonTraits(lattice,idx,graph[idx].edges[edgesIdx]);
      if( h != f && h >= th ) actLinks++;
    }
  }
  return actLinks/2;
}

/* initAxelrod() inicializa el axelrod con los parametros dados en param */

int axelrodInit(parameter* param, agent* lattice, vertex* graph){
  int n = param->n;
  int f = param->f;
  int q = param->q;
  int qF = param->qF;
  int nStub = param->nStub;
  int neigOrdEdges = param->neigOrdEdges;
  int neigOrdRewire = param->neigOrdRewire;
  int nRewire = param->nRewire;
  int nEdgeRew = param->nEdgeRew;
  int nEdgesAdd = param->nEdgesAdd;

  latticeInit(lattice, n, f);
  latticeFill(lattice, n, q, qF);
  latticeSetStub(lattice, n, nStub);

  graphInit(graph, n);
  graphFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);
  graphEdgesAddNRand(graph, n, nEdgesAdd);

  return 0;
}

/* singleAxelrod() toma los parametros y realiza una corrida de axelrod.
  Si el flag de verbose es 1, ademas arroja informacion acerca de los pasos
  y los links activos */

int axelrodSingleRun(parameter* param, agent* lattice, vertex* graph, int v){
  int n = param->n;
  float phi = param->phi;
  int paso = n*n;
  int t = time(NULL);

  int i = 0;
  int stop = 0;
  while(stop == 0){
    step(graph,lattice,n,phi);
    if(i%paso==0) stop = stopReached(graph,lattice,n);
    if(i%(int)(1E6) == 0 && v == 1){
      printf("Paso %d, Links = %d\n", i, activeLinks(graph,lattice,n));
    }
    i++;
  }

  if(v == 1){
    printf("Paso %d, Links = %d\n", i, activeLinks(graph,lattice,n));
  }
  t = time(NULL) - t;
  printf("t = %d\n", t);

  return 0;
}

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
  int k = 2; //threshold de interaccion
  i = getRand(n*n); //indice del activo
  while(graph[i].nEdges == 0) i = getRand(n*n); //elijo un agente CON vecinos
  j = pickPassiveNeig(graph, i); //indice del pasivo(vecino al azar)

  hij = commonTraits(lattice, i, j);

  // si la homofilia es mayor que el threshold
  if(hij >= k){
    if(vertexRewireIsConnected(graph, i, j)){

      int k = pickPassiveNotNeig(graph, n, i);
      int hik = commonTraits(lattice, i, k);

      if(hij < hik) return socialInteraction(graph, i, j, k);
      else opinionInteraction(lattice, i, j, hij, phi);

    }
    else opinionInteraction(lattice, i, j, hij, phi);
  }

  return 0;

}

/* pickPassiveNeig() agarra un vecino al azar del agente i, usando la lista de
conexiones */

int pickPassiveNeig(vertex* graph, int i){
  int idx = getRand(graph[i].nEdges);
  return graph[i].edges[idx];
}

/* pickPassiveNotNeig() agarra un NO vecino al azar del agente i */

int pickPassiveNotNeig(vertex* graph, int n, int i){
  int idx = getRand(n*n);
  while((vertexEdgeIsConnected(graph,i,idx) || idx == i)){
    idx = getRand(n*n);
  }
  return idx;
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

int opinionInteraction(agent* lattice, int i, int j, int hij, float phi){

  int uncomTrait, f;
  float prob;
  f = lattice[i].f;

  prob = (float) hij / f;

  if( ((float) rand() / (float) RAND_MAX) < prob){

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
        /* si el agente no es taliban y cumple la condicion del campo */
        if(lattice[i].stub != 1 && ((float) rand() / (float) RAND_MAX) < (1-phi)){
          lattice[i].feat[uncomIdx] = lattice[j].feat[uncomIdx];
        }
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

/* stopReached() devuelve 0 o 1 si hay o no transiciones disponibles
respectivamente (si no hay, la interaccion es terminada) */

int stopReached(vertex* graph, agent* lattice, int n){
  int h;
  int k = 2; //threshold de la interaccion
  int f = lattice[0].f;

  for(int idx = 0; idx < n*n; idx++){
    for(int edgesIdx = 0; edgesIdx<graph[idx].nEdges; edgesIdx++){
      h = commonTraits(lattice,idx,graph[idx].edges[edgesIdx]);
      if( !(h == f || h < k) ) return 0;
    }
  }
  return 1;
}

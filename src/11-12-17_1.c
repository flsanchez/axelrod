#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/graph.h"
#include "include/agent.h"
#include "include/axelrod.h"
#include "include/misc.h"
#include "include/epidemy.h"
#include "include/functions.h"
#include "include/label.h"

// en este main se mide la cantidad de infectados para un outbreak particular

int main(int argc, char *argv[]){

  parameter* param = (parameter*) malloc(sizeof(parameter));
  int n = 50;
  int niter = 50;
  param->n = n;
  param->f = 11;
  param->phi = 0.001;
  param->q = 90;
  param->neigOrdEdges = 2;
  param->neigOrdRewire = 2;
  param->nRewire = 1;
  param->nEdgeRew = 0;
  param->nEdgesAdd = 0;
  param->nRewireAdd = 100;
  param->nStub = n*n*0.01;
  float nStub;
  if(argc > 3){
   sscanf(argv[1], "%f", &param->phi);
   //sscanf(argv[2], "%d", &param->q);
   sscanf(argv[2], "%f", &nStub);
   sscanf(argv[3], "%d", &niter);
  }
  param->nStub = (int)(nStub*n*n);
  param->qF = param->q;
  int nProm = 100;
  int dist2 = 2;
  //char name[100];
  int t = time(NULL);
  // parametros del modelo SEIR
  int nInf = 1;
  float nuS = 2.8/8;
  float nuE = 1.0/8;
  float nuI = 1.0/8;
  float dt = 0.5;
  FILE* fs;
  int tLoop;
  //FILE* fs1;
  //FILE* fs2;

  fs = fopen("infected.txt","w");

  srand(time(NULL));

  for(int iter = 0; iter < niter; iter++){
    tLoop = time(NULL);
    printf("Paso total %d\n", iter);
    // inicializo lo necesario para axelrod
    agent* lattice = (agent*) malloc(n * n * sizeof(agent));
    vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));
    axelrodInit(param, lattice, graph, 1);

    // hago axelrod
    printf("Axelrod...\n");
    axelrodSingleRun(param, lattice, graph, 0);
    printf("OK!\n");

    // copio el grapho y corto los links de largo rango en la copia
    vertex* graphEpi;
    graphCopy(graph, n, &graphEpi);
    cutDistantLinks(graphEpi,n,dist2);

    //inicio la corrida del modelo epidemiologico, sorteando cada vez
    printf("Modelo epidemiologico...\n");
    float infStep, infTotal = 0;
    for(int prom = 0; prom < nProm; prom++){
      /*sprintf(name, "population_%d.epi", prom);
      fs1 = fopen(name,"w");
      sprintf(name, "lattice_%d.lat", prom);
      fs2 = fopen(name,"w");
      latticeSaveToFile(lattice, n, fs2);*/
      infStep = populationSEIRFull(graph,graphEpi,lattice,n,nInf,nuS,nuE,nuI,dt);
      if(prom%25 == 0)printf("Paso Epidemiologico %d; Inf: %.2f\n", prom, infStep);
      fprintf(fs, "%.4f ", infStep);
      infTotal = infTotal + infStep;
      /*fclose(fs1);
      fclose(fs2);*/
    }
    infTotal = infTotal/nProm;
    printf("OK! t = %d\n",(int)time(NULL)-tLoop);
    printf("Infectados = %.4f\n", infTotal);
    fprintf(fs, "\n");
    //libero las cosas
    graphFree(graph,n);
    graphFree(graphEpi,n);
    latticeFree(lattice,n);
    free(graph);
    free(graphEpi);
    free(lattice);
  }
  fclose(fs);

  t = time(NULL)-t;
  printf("Tiempo transcurrido total: %d:%d:%d\n", t/3600, (t/60)%60, t%60);
}

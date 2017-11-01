#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/agent.h"
#include "include/graph.h"
#include "include/label.h"
#include "include/axelrod.h"
#include "include/functions.h"
#include "include/misc.h"


/* este main hace una corrida simple de un axelrod y entrega el Smax y la
cantidad de pasos para llegar al stop por pantalla */

int main(int argc, char *argv[]){
  parameter* param = (parameter*) malloc(sizeof(parameter));
  int n = 50;
  param->n = n;
  param->f = 11;
  param->phi = 0;
  param->q = 116;
  int prom = 2500;
  int niter = 50;
  param->neigOrdEdges = 2;
  param->neigOrdRewire = 2;
  param->nRewire = 1;
  param->nEdgeRew = 0*n*n;
  param->nEdgesAdd = 100;
  param->nStub = n*n*0.01;
  int m = 10;
  if(argc > 2){
    sscanf(argv[1], "%f", &param->phi);
    sscanf(argv[2], "%d", &m);
  }
  param->qF = param->q;
  int* nsAcumVacc = malloc(n*n*sizeof(int));
  int frag;
  float max,nmbrNonVac;
  int qlen = 30, b = 0;
  int* qVector = malloc(sizeof(int)*qlen);
  for(int i = 0; i<qlen; i++) qVector[i] = m*(i+1) + b;
  int q,t;
  int* vacFeat = malloc(n*n*sizeof(int)); //guarda el feat de vacunacion cada paso
  char name[100];

  srand(time(NULL));

  FILE* fs;
  FILE* fsFrag;
  FILE* fsFragNoProm;
  FILE* fsMass;
  FILE* fsMassNoProm;

  fs = fopen("run.log","w");
  fprintf(fs, "# numero_de_qs prom m b nRewire nEdgeRew phi promedios\n");
  fprintf(fs, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n%d\n",qlen,niter,m,b,param->nRewire,param->nEdgeRew,param->nStub,param->phi,prom);
  fclose(fs);

  for(int qIdx=0; qIdx<qlen; qIdx++){
    q = qVector[qIdx];
    param->q = q;

    sprintf(name,"q_%d.frag",q);
    fsFrag = fopen(name,"w");
    fprintf(fsFrag,"# n f q\n# %d %d %d\n# fragmentos\n"
            ,param->n,param->f,param->q);

    sprintf(name,"q_%d_noProm.frag",q);
    fsFragNoProm = fopen(name,"w");
    fprintf(fsFragNoProm,"# n f q\n# %d %d %d\n# fragmentos\n"
            ,param->n,param->f,param->q);

    sprintf(name,"q_%d.txt",q);
    fsMass = fopen(name,"w");
    fprintf(fsMass,"# n f q\n# %d %d %d\n# maximoCluster masaNoVac\n"
            ,param->n,param->f,param->q);

    sprintf(name,"q_%d_noProm.txt",q);
    fsMassNoProm = fopen(name,"w");
    fprintf(fsMassNoProm,"# n f q\n# %d %d %d\n# maximoCluster masaNoVac\n"
            ,param->n,param->f,param->q);

    for(int iter=0; iter<niter; iter++){
      t = time(NULL);
      printf("Paso %d/%d:\nq = %d\n", iter+1,niter,param->q);
      agent* lattice = (agent*) malloc(n * n * sizeof(agent));
      vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));
      axelrodInit(param, lattice, graph);

      // pongo a cero las cosas acumuladativas
      for(int i = 0; i<n*n; i++) nsAcumVacc[i] = 0;
      nmbrNonVac = 0;
      max = 0;

      // hago axelrod
      printf("Axelrod...\n");
      axelrodSingleRun(param, lattice, graph, 0);
      printf("OK!\n");
      printf("Promedios...\n");

      // guardo la data sin binarizar
      frag = latticeLabelVac(graph, lattice, n);
      max = maxCluster(lattice, nsAcumVacc, n, frag);
      nmbrNonVac = nonVaccinatorTotal(lattice, n);
      fprintf(fsMassNoProm, "%f %f\n", max, nmbrNonVac);

      // guardo los fragmentos sin binarizar
      for(int i = 0; i<n*n; i++) fprintf(fsFragNoProm,"%d ",nsAcumVacc[i]);
      fprintf(fsFragNoProm, "\n");

      // guardo el valor del feature de vacunacion
      for(int j = 0; j<n*n; j++) vacFeat[j] = lattice[j].feat[lattice[j].f-1];

      for(int i = 0; i<n*n; i++) nsAcumVacc[i] = 0;
      nmbrNonVac = 0;
      max = 0;

      // hago prom promedios
      for(int j = 0; j<prom; j++){
        latticeTransformVaccToBinary(lattice, n);
        frag = latticeLabelVac(graph, lattice, n);
        max = max + (float)maxCluster(lattice, nsAcumVacc, n, frag)/prom;
        nmbrNonVac = nmbrNonVac + (float)nonVaccinatorTotal(lattice, n)/prom;
        // cargo el valor del feature de vacunacion
        for(int j = 0; j<n*n; j++) lattice[j].feat[lattice[j].f-1] = vacFeat[j];
      }

      printf("OK!\n");
      printf("Smax = %.4f; Mass = %.4f; t = %d\n",max, nmbrNonVac, (int)time(NULL)-t );
      // guardo los fragmentos
      for(int i = 0; i<n*n; i++) fprintf(fsFrag,"%d ",nsAcumVacc[i]);
      fprintf(fsFrag, "\n");

      // guardo otra data
      fprintf(fsMass, "%f %f\n", max, nmbrNonVac);

      latticeFree(lattice, n);
      free(lattice);
      graphFree(graph, n);
      free(graph);
    }

    fclose(fsFrag);
    fclose(fsFragNoProm);
    fclose(fsMass);
    fclose(fsMassNoProm);
  }

  free(nsAcumVacc);
  free(qVector);
  free(param);
  free(vacFeat);

  return 0;
}

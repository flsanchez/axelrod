#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "graph.h"
#include "label.h"
#include "axelrod.h"

/* para una lista de q's, y para un numero prom de repeticiones para cada q,
se ejecutan pasos temporales de axelrod hasta alcanzar la condicion de stop.
La data se guarda en diferentes txt para cada q, y adentro se guardan, para
cada repeticion Smax, iteraciones hasta llegar al stop y numero de rewires
hasta llegar al stop */

int main(int argc, char *argv[]){

  int n = 50;
  int f = 11;
  int prom = 50;
  int niter = 300E6; /* condicion de escape, por si se queda trabado el
                        programa por algun motivo desconocido */
  int* Sprom = malloc(prom*sizeof(int));
  int* SpromLastFeat = malloc(prom*sizeof(int));
  int* nmbrOfRew = malloc(prom*sizeof(int));
  int* nsAcum = malloc(n*n*sizeof(int));
  int* nsAcumLastFeat = malloc(n*n*sizeof(int));

  int frag;
  int max;
  int neigOrdEdges = 2;
  int neigOrdRewire = 2;
  int nEdgeRew =  0;
  int nRewire = 1;
  int* term = malloc(prom*sizeof(int));
  FILE *fs;
  char name[100];
  int qlen = 20;
  int *qVector = malloc(qlen*sizeof(int));
  int q;
  int qF = 2;
  int m = 13;
  int b = 0;
  float phi = 0;
  int nStub = n*n*0.01;

  if(argc>3){
    sscanf(argv[1], "%d", &nEdgeRew);
    sscanf(argv[2], "%d", &m);
    sscanf(argv[3], "%d", &prom);
    sscanf(argv[4], "%f", &phi);
  }

  for(int i = 0; i<qlen; i++) qVector[i] = m*(i+1) + b;

  int tLoop,tTotal;
  srand(time(NULL));

  fs = fopen("run.log","w");
  fprintf(fs, "# numero_de_qs prom m b nRewire nEdgeRew\n");
  fprintf(fs, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n",qlen,prom,m,b,nRewire,nEdgeRew,nStub,phi);
  fclose(fs);

  agent *lattice = (agent*) malloc(n * n * sizeof(agent));
  latticeInit(lattice, n, f);
  vertex* graph = (vertex*) malloc(n * n * sizeof(vertex));


  int k,stop;
  int paso = n*n;

  tTotal = time(NULL);

  for(int j = 0; j<qlen; j++){

    q = qVector[j];

    for(int k=0; k<n*n; k++){
      nsAcum[k] = 0;
      nsAcumLastFeat[k] = 0;
    }

    for(int i = 0; i<prom; i++){

      tLoop = time(NULL);

      printf("q = %d, prom = %d \n",q,i);

      graphInit(graph, n);
      graphFill(graph, n, nEdgeRew, nRewire, neigOrdEdges, neigOrdRewire);

      /*sprintf(name,"q_%d_%d_Ini.net",q,i);
      fs = fopen(name,"w");
      graphPrintToFile(graph,n,fs);
      fclose(fs);*/

      latticeFill(lattice, n, q, qF);
      latticeSetStub(lattice,n,nStub);

      stop = 0;
      k = 0;
      nmbrOfRew[i] = 0;
      while(stop == 0 &&  k < niter ){
        nmbrOfRew[i] = nmbrOfRew[i] + step(graph,lattice,n,phi);
        if(k%paso == 0) stop = stopReached(graph,lattice,n);
        k++;
      }

      term[i] = k-1;
      frag = latticeLabel(graph, lattice, n);
      max = maxCluster(lattice, nsAcum, n, frag);
      Sprom[i] = max;

      frag = latticeLabelFeatN(graph, lattice, n, f-1);
      max = maxCluster(lattice, nsAcumLastFeat, n, frag);
      SpromLastFeat[i] = max;

      printf("Smax = %d; SmaxLastFeat = %d; Pasos = %d; Rewires = %d\n",Sprom[i],SpromLastFeat[i],k-1,nmbrOfRew[i]);

      /*sprintf(name,"q_%d_%d_Fin.net",q,i);
      fs = fopen(name,"w");
      graphPrintToFile(graph,n,fs);
      fclose(fs);*/

      graphFree(graph,n);

      tLoop = time(NULL)-tLoop;
      printf("Tiempo transcurrido en el Loop: %d:%d:%d\n", tLoop/3600, (tLoop/60)%60, tLoop%60);

    }

    sprintf(name,"q_%d.txt",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q\n# %d %d %d\n",n,f,q);
    for(int i = 0; i<prom; i++){
      fprintf(fs,"%d %d %d %d\n", Sprom[i], SpromLastFeat[i], term[i],nmbrOfRew[i]);
    }
    fprintf(fs,"# Smax SmaxLastFeat pasos nmbrOfRew\n");
    fclose(fs);

    sprintf(name,"q_%d.frag",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q\n# %d %d %d\n# tamaño_de_fragmento frecuencia\n"
            ,n,f,q);
    for(int i = 0; i<n*n; i++){
      fprintf(fs,"%d %d\n", i+1, nsAcum[i]);
    }
    fclose(fs);

    sprintf(name,"q_%d_LastFeat.frag",q);
    fs = fopen(name,"w");
    fprintf(fs,"# n f q\n# %d %d %d\n# tamaño_de_fragmento frecuencia\n"
            ,n,f,q);
    for(int i = 0; i<n*n; i++){
      fprintf(fs,"%d %d\n", i+1, nsAcum[i]);
    }
    fclose(fs);

  }
  tTotal = time(NULL) - tTotal;
  printf("Tiempo transcurrido total: %d:%d:%d\n", tTotal/3600, (tTotal/60)%60, tTotal%60);

  latticeFree(lattice,n);
  free(lattice);
  free(graph);
  free(nsAcum);
  free(nmbrOfRew);
  free(Sprom);
  free(SpromLastFeat);
  free(qVector);
  free(term);
  return 0;

}

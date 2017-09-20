#ifndef AGENT_H
#define AGENT_H

typedef struct agent
{
  int f;      //numero de features
  int q;      //numero de traits
  int *feat;  //vector de features
  int label;  //etiqueta identificadora de cluster
  int qF;     //numero de traits del feat f
  int stub;   /* etiqueta de taliban ( 0 si proVacunador,
              1 si antiVacunador(taliban) ) */
} agent;

int agentInit(agent *lattice, int idx, int f);
int agentFill(int *feat, int f, int q, int qF);
int agentPrint(agent *agent, int n, int idx);
int latticeInit(agent *lattice, int n, int f);
int latticeFill(agent *lattice, int n, int q, int qF);
int latticeSetStub(agent* lattice, int n, int nStub);
int latticeSetStubFromArray(agent* lattice, int n, int* idxList, int nArray);
int latticePrintFeats(agent *lattice, int n);
int latticePrintFeatN(agent *lattice, int n, int featNIdx);
int latticePrintLabels(agent *lattice, int n); //
int latticePrintToFile(agent* lattice, int n, FILE* fs, int labelFlag);
int latticeFree(agent *lattice, int n); //
int commonTraits(agent *lattice, int i, int j);


#endif

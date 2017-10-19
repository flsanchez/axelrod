#ifndef LABEL_H
#define LABEL_H

/* labelea los clusters y devuelve la etiqueta del maximo fragmento */
int latticeLabel(vertex* graph, agent *lattice, int n);
int latticeLabelFeatN(vertex* graph, agent* lattice, int n, int featNIdx);
int latticeLabelVac(vertex* graph, agent* lattice, int n);
int latticeLabelCultural(vertex* graph, agent* lattice, int n);
int fixLabel(agent *lattice, int n, int *clase);
int falseLabel(agent *lattice, int *clase, int* commNeig, int nCommNeig, int idx);


#endif

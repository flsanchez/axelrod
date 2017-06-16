#ifndef LABEL_H
#define LABEL_H

int latticeLabel(agent *lattice, int n); //labelea los clusters y devuelve
                                         //la etiqueta del maximo fragmento
int updateLabel(agent *lattice, int *clase, int idx1, int idx2, int *frag);
int fixLabel(agent *lattice, int *clase, int n);
int falseLabel(agent *lattice,int *clase, int idx1, int idx2, int idx);

#endif

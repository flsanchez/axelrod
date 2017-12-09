#ifndef MISC_H
#define MISC_H

int getRand(int max);
int shuffleArray(int* shuffled, int n);
int isElemInArray(int* array, int n, int elem);
int patternFill(int** patterni, int** patternj, int n, int neigOrd);
int fillNeigArray(int* patterni, int* patternj, int nPattern, int** neigArray,
                  int idx, int n);
int loadFromTxt(FILE* fs, int* array);

#endif

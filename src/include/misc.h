#ifndef MISC_H
#define MISC_H

int getRand(int max);
int shuffleArray(int* shuffled, int n);
int shuffleArrayFloat(float* shuffled, int n);
int shuffleArrays(int* shuffled1, int* shuffled2, int n);
int isElemInArray(int* array, int n, int elem);
int patternFill(int** patterni, int** patternj, int n, int neigOrd);
int fillNeigArray(int* patterni, int* patternj, int nPattern, int** neigArray,
                  int idx, int n);
int loadFromTxt(FILE* fs, int* array);
struct tm* printDate();

#endif

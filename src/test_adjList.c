#include <stdio.h>
#include <stdlib.h>
#include "adjList.h"

int main(){
  adjList* list = (adjList*) malloc(sizeof(adjList));
  adjListCreate(list);
  for(int i = 0; i<3 ; i++) adjListAddNode(list,i,4*i);
  printAdjList(list);
  adjListFree(list);
  for(int i = 0; i<3 ; i++) adjListAddNode(list,i,123*i);
  printAdjList(list);
  adjListFree(list);
  if(list->head == NULL) printf("OK\n");
  free(list);
  return 0;
}

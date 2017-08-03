#include <stdio.h>
#include <stdlib.h>
#include "adjList.h"

int adjListCreate(adjList* list){
  list->head = NULL;
  list->len = 0;
  return 0;
}

adjListNode* adjListNodeCreate(int value, int rewire){
    adjListNode* node = (adjListNode*) malloc(sizeof(adjListNode));
    node->value = value;
    node->rewire = rewire;
    node->next = NULL;
    return node;
}

int adjListAddNode(adjList* list, int value, int rewire){

  adjListNode *newNode = adjListNodeCreate(value,rewire);
  newNode->next = list->head;
  list->head = newNode;
  list->len++;
  return 0;

}

int adjListRemNode(adjList list, int n){
  if(list.len<n){

  }
}

int printAdjList(adjList* list){
  adjListNode *curr = (adjListNode*) malloc(sizeof(adjListNode));
  curr = list->head;
  while(curr != NULL){
    printf("(%d, %d)\n",curr->value,curr->rewire);
    curr = curr->next;
  }
  return 0;
}

int adjListFree(adjList* list){
  adjListNode* next = NULL;
  for(adjListNode* link = list->head; link != NULL; link = next)
  {
    next = link->next;
    free(link);
  }
  free(next);
  list->head = NULL;
  list->len = 0;
  return 0;
}

#ifndef ADJLIST_H
#define ADJLIST_H

typedef struct adjListNode
{
  int value;
  int rewire;
  struct adjListNode *next;
} adjListNode;

typedef struct adjList
{
  struct adjListNode *head;
  int len;
} adjList;

adjListNode* adjListNodeCreate(int value, int rewire);
int adjListCreate(adjList* list);
int adjListAddNode(adjList* list, int value, int rewire);
int printAdjList(adjList* list);
int adjListFree(adjList* list);
int adjListRemNode(adjList list, int n);

#endif

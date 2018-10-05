/*
 * DataStructure.h
 *
 *  Created on: 13 Aðu 2018
 *      Author: enes.aydin
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef size_t Type;
typedef size_t * pType;

// struct for data-specific operations
typedef struct _DataFuncsPointers{
	Type SumSize;
	void (*dataClear)(void *);
	void * (*dataCreat)(const Type);
	void * (*dataCopy)(void *, const void *, const Type);
	int (*dataEqual)(const void *, const void *, const Type);	// Eþitse return 0 büyükse 1 küçükse -1
} DataFuncsPointers;

// DynamicArray

typedef struct _ItemDA{
	void ** Data;
	Type Count, Capacity;
} ItemDA;

typedef struct _DynamicArray{
	ItemDA Array;
	DataFuncsPointers Funcs;
} DynamicArray;

void dtDynamicArrayInit(DynamicArray *, DataFuncsPointers);
void dtDynamicArrayClear(DynamicArray *);

void dtDynamicArraySort(DynamicArray *);
Type dtDynamicArrayGetCount(const DynamicArray *);
Type dtDynamicArrayGetCapacity(const DynamicArray *);
_Bool dtDynamicArrayGetFrom(DynamicArray *, void *, const Type);
void dtDynamicArrayRemove(DynamicArray *, const void *);
void dtDynamicArrayRemoveAt(DynamicArray *, const Type);
_Bool dtDynamicArrayAdd(DynamicArray *, const void *);
_Bool dtDynamicArrayInsert(DynamicArray *, const void *, const Type);

// LinkedList

typedef struct _ItemLL{
	void * Data;
	struct _ItemLL * Next;
} ItemLL;

typedef struct _LinkedList{
	ItemLL * Head, * Tail;
	DataFuncsPointers Funcs;
} LinkedList;

void dtLinkedListInit(LinkedList *, DataFuncsPointers);
void dtLinkedListClear(LinkedList *);
int dtLinkedListIsEmpty(const LinkedList *);
int dtLinkedListGet(LinkedList *, void *); // and delete
int dtLinkedListInsert(LinkedList *, const void *); //sorted
int dtLinkedListPeek(const LinkedList *, void *);

/*
// Stack
struct stack{
	Item top;
};
typedef struct stack * Stack;
Stack createStack();
void clearStack(Stack);
int isEmptyStack(Stack);
int pop(Stack, Data *);
int push(Stack, Data *);
int peekStack(Stack, Data *);
// Queue
struct queue{
	Item front;
	Item rear;
};
typedef struct queue * Queue;
Queue createQueue();
void clearQueue(Queue);
int isEmptyQueue(Queue);
int dequeue(Queue, Data *);
int enqueue(Queue, Data *);
int peekQueue(Queue, Data *);
// Node
struct t{
	Data element;
	DynamicArray child;
	DynamicArray sibling;
};
typedef struct t Mytip;
// Tree
struct tree{
	DynamicArray level;
	DataFunctions func;
};
typedef struct tree Tree;
*/
/*
// Node
struct node{
	DataAddress element;
	DynamicArray childs; //Node0, Node1, Node2, ...,
};
typedef struct node * Node;
// Tree
struct tree{
	Node root;
	Node selected;
	Strct4DataPointer func;
};
typedef struct tree Tree;
void initTree(Tree *, Strct4DataPointer);
void clearTree(Tree *);
int isEmptyTree(const Tree *);
*/
/*
void setNodes(Node, int, int);
Tree initMyTree(int);
*/


#endif /* DATASTRUCTURE_H_ */

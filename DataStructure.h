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

// struct for data-specific operations
typedef struct _DataFuncsPointers{
	size_t SumSize;
	void (*dataClear)(void *);
	void * (*dataCreat)(const size_t);
	void * (*dataCopy)(void *, const void *, const size_t);
	int (*dataEqual)(const void *, const void *, const size_t);	// Eþitse return 0 büyükse 1 küçükse -1
} DataFuncsPointers;

// DynamicArray

typedef struct _DynamicArray{
	void ** Data;
	size_t Count, Capacity;
	DataFuncsPointers Funcs;
} DynamicArray;

void dtDynamicArrayInit(DynamicArray *, DataFuncsPointers);
void dtDynamicArrayClear(DynamicArray *);

void dtDynamicArraySort(DynamicArray *);
size_t dtDynamicArrayGetCount(const DynamicArray *);
size_t dtDynamicArrayGetCapacity(const DynamicArray *);
int dtDynamicArrayGetFrom(DynamicArray *, void *, const size_t);
void dtDynamicArrayRemove(DynamicArray *, const void *);
void dtDynamicArrayRemoveAt(DynamicArray *, const size_t);
int dtDynamicArrayAdd(DynamicArray *, const void *);
int dtDynamicArrayInsert(DynamicArray *, const void *, const size_t);

// LinkedList

typedef struct _ItemLL{
	void * Data;
	struct _ItemLL * Next;
} ItemLL;

typedef struct _LinkedList{
	ItemLL * Head;
	ItemLL * Tail;
	DataFuncsPointers Funcs;
} LinkedList;

void dtLinkedListInit(LinkedList *, DataFuncsPointers);
void dtLinkedListClear(LinkedList *);

int dtLinkedListIsEmpty(const LinkedList *);
int dtLinkedListGet(LinkedList *, void *); // and delete
int dtLinkedListInsert(LinkedList *, const void *); //sorted
int dtLinkedListPeek(const LinkedList *, void *);

/*
// Node
struct t{
	Data element;
	DynamicArray child;
	DynamicArray sibling;
};
size_tdef struct t Mytip;
// Tree
struct tree{
	DynamicArray level;
	DataFunctions func;
};
size_tdef struct tree Tree;
*/
/*
// Node
struct node{
	DataAddress element;
	DynamicArray childs; //Node0, Node1, Node2, ...,
};
size_tdef struct node * Node;
// Tree
struct tree{
	Node root;
	Node selected;
	Strct4DataPointer func;
};
size_tdef struct tree Tree;
void initTree(Tree *, Strct4DataPointer);
void clearTree(Tree *);
int isEmptyTree(const Tree *);
*/
/*
void setNodes(Node, int, int);
Tree initMyTree(int);
*/

/*
// Stack
struct stack{
	Item top;
};
size_tdef struct stack * Stack;
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
size_tdef struct queue * Queue;
Queue createQueue();
void clearQueue(Queue);
int isEmptyQueue(Queue);
int dequeue(Queue, Data *);
int enqueue(Queue, Data *);
int peekQueue(Queue, Data *); */
#endif /* DATASTRUCTURE_H_ */

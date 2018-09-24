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
#include <time.h>

typedef size_t Type;
typedef size_t * pType;

// struct for data-specific operations
typedef struct _DataFuncsPointers{
	Type SumSize;
	void (*dataClear)(void *);
	void * (*dataCreat)(const Type);
	void * (*dataCopy)(void *, const void *, const Type);
	int (*dataEqual)(const void *, const void *, const Type);
} DataFuncsPointers;
/*
void dtMemClear(void *);
void * dtMemCreat(const Type);
void dtMemCopy(void *, const void *, const Type);
int dtMemEqual(const void *, const void *, const Type);
*/
// DynamicArray

typedef struct _ItemDA{
	void * data;
} ItemDA;

typedef struct _DynamicArray{
	ItemDA * ArrayData; //void **
	Type ArraySize, ArrayCapacity;
	DataFuncsPointers Funcs;
} DynamicArray;

void dtDynamicArrayInit(DynamicArray *, DataFuncsPointers);
void dtDynamicArrayClear(DynamicArray *);
int dtDynamicArrayIsEmpty(const DynamicArray *);
int dtDynamicArrayGetFrom(DynamicArray *, void *, const Type); // not delete
int dtDynamicArrayInsert(DynamicArray *, const void *); //sorted
int dtDynamicArrayPeek(const DynamicArray *, void *);

// Item
typedef struct _ItemLL{
	void * data;
	struct item * next;
} ItemLL;

// LinkedList
typedef struct linked_list{
	ItemLL * head, * tail;
	DataFuncsPointers func;
} LinkedList;

void dtLinkedListInit(LinkedList *, Strct4DataPointer);
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

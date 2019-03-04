/*
 * DataStructure.h
 *
 *  Created on: 13 Ağu 2018
 *      Author: enes.aydin
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#include <stddef.h>

/*
 * struct for data-specific operations
 */

typedef struct _StructDataInfo{
	size_t SumSize;
	void (*dataClear)(void *);
	void * (*dataCreat)(const size_t);
	void * (*dataCopy)(void *, const void *, const size_t);
	int (*dataEqual)(const void *, const void *, const size_t);	/* Eşitse 0 büyükse 1 küçükse -1*/
} StructDataInfo;

/*
 * DynamicArray
 */

typedef struct _DynamicArray{
	void ** Data;
	size_t Count, Capacity;
	StructDataInfo Info;
} DynamicArray;

void dtDynamicArrayInit(DynamicArray * dynamicArray, StructDataInfo Info);
void dtDynamicArrayReset(DynamicArray * dynamicArray);
void dtDynamicArrayClear(DynamicArray * dynamicArray);

void dtDynamicArraySort(DynamicArray * dynamicArray);

size_t dtDynamicArrayGetCount(const DynamicArray * dynamicArray);
size_t dtDynamicArrayGetCapacity(const DynamicArray * dynamicArray);

int dtDynamicArrayAdd(DynamicArray * dynamicArray, const void * data);
int dtDynamicArrayRemove(DynamicArray * dynamicArray, const void * data);
int dtDynamicArrayRemoveAt(DynamicArray * dynamicArray, const size_t index);
int dtDynamicArrayInsert(DynamicArray * dynamicArray, const void * data, const size_t index);
int dtDynamicArrayGetFrom(const DynamicArray * dynamicArray, void * data, const size_t index);

/*
 * LinkedList
 */

typedef struct _ItemLL{
	void * Data;
	struct _ItemLL * Next;
} ItemLL;

typedef struct _LinkedList{
	ItemLL * Head;
	ItemLL * Tail;
	StructDataInfo Funcs;
} LinkedList;

void dtLinkedListInit(LinkedList * linkedList, StructDataInfo Info);
void dtLinkedListReset(LinkedList * linkedList);
void dtLinkedListClear(LinkedList * linkedList);

void dtLinkedListSort(LinkedList * linkedList);

int dtLinkedListIsEmpty(const LinkedList * linkedList);

int dtLinkedListAdd(LinkedList * linkedList, const void * data);
int dtLinkedListRemove(LinkedList * linkedList, const void * data);
int dtLinkedListRemoveAt(LinkedList * linkedList, const size_t index);
int dtLinkedListInsert(LinkedList * linkedList, const void * data, const size_t index);
int dtLinkedListGetFrom(const LinkedList * linkedList, void * data, const size_t index);

/*
 * Tree
 */

typedef struct _Node{
	void * Data;
	DynamicArray childs;
} Node;

typedef struct _Tree{
	Node * Root;
	StructDataInfo Info;
} Tree;

void dtTreeInit(Tree * tree, StructDataInfo Info);
void dtTreeReset(Tree * tree);
void dtTreeClear(Tree * tree);


/*

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

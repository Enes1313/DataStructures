/*
 * vy.h
 *
 *  Created on: 13 Ağu 2018
 *      Author: NS
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

// Data
typedef struct d{
	void * addres;
} DataAddress;

// DataFunctions
typedef struct d_f{
	Type sum_size;
	void (*clearData)(DataAddress *);
	void (*creatData)(DataAddress *, const Type);
	void (*copyData)(DataAddress *, const DataAddress *, const Type);
	int (*equalData)(const DataAddress *, const DataAddress *, const Type);
} Strct4DataPointer;

// Mem fonksiyonları kullanılarak bazı veri formatları için genel fonk.
void clearMem(DataAddress *);
void creatMem(DataAddress *, const Type);
void copyMem(DataAddress *, const DataAddress *, const Type);
int equalMem(const DataAddress *, const DataAddress *, const Type);

// Adres tutacaksa
void clearAdr(DataAddress *);
void creatAdr(DataAddress *, const Type);
void copyAdr(DataAddress *, const DataAddress *, const Type);
int equalAdr(const DataAddress *, const DataAddress *, const Type);

// Item
typedef struct item{
	DataAddress data;
	struct item * next;
} * Item;

// LinkedList
typedef struct linked_list{
	Item head;
	Item tail;
	Strct4DataPointer func;
} LinkedList;

// int delete(LinkedList, Data *); // araya ekleme fonksiyonu
void initLinkedList(LinkedList *, Strct4DataPointer);
void clearLinkedList(LinkedList *);
int isEmptyLinkedList(const LinkedList *);
int getLL(LinkedList *, DataAddress *); // and delete
int insertLL(LinkedList *, const DataAddress *); //sorted
int peekLinkedList(const LinkedList *, DataAddress *);

// DynamicArray
typedef struct dynamic_array{
	DataAddress * array;
	Type boyut, kapasite;
	Strct4DataPointer func;
} DynamicArray;

// int getDA(DynamicArray, Data *); // and delete // istenen düğümü bulma ve silme fonksiyonu // araya ekleme fonksiyonu
void initDynamicArray(DynamicArray *, Strct4DataPointer);
void clearDynamicArray(DynamicArray *);
int isEmptyDynamicArray(const DynamicArray *);
int getFrDA(DynamicArray *, DataAddress *, const Type); // not delete
int insertDA(DynamicArray *, const DataAddress *); //sorted
int peekDynamicArray(const DynamicArray *, DataAddress *);
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

/*
 * eaDSLinkedList.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSLINKEDLIST_H_
#define EADSLINKEDLIST_H_

#include "eaDSData.h"

/*
 * LinkedList
 */

typedef struct _ItemLL{
	void * Data;
	struct _ItemLL * Next;
} ItemLL;

typedef struct _eaDSLinkedList{
	ItemLL * Head;
	ItemLL * Tail;
	StructDataInfo Funcs;
} eaDSLinkedList;

void eaDSLinkedListInit(eaDSLinkedList * linkedList, StructDataInfo Info);
void eaDSLinkedListReset(eaDSLinkedList * linkedList);
void eaDSLinkedListClear(eaDSLinkedList * linkedList);

void eaDSLinkedListSort(eaDSLinkedList * linkedList);

int eaDSLinkedListIsEmpty(const eaDSLinkedList * linkedList);

int eaDSLinkedListAdd(eaDSLinkedList * linkedList, const void * data);
int eaDSLinkedListRemove(eaDSLinkedList * linkedList, const void * data);
int eaDSLinkedListRemoveAt(eaDSLinkedList * linkedList, const size_t index);
int eaDSLinkedListInsert(eaDSLinkedList * linkedList, const void * data, const size_t index);
int eaDSLinkedListGetFrom(const eaDSLinkedList * linkedList, void * data, const size_t index);

#endif /* EADSLINKEDLIST_H_ */

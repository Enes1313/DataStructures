/*
 * eaDSLinkedList.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSLinkedList.h"

/*
 * LinkedList
 */

void eaDSLinkedListInit(eaDSLinkedList * linkedList, StructDataInfo funcs)
{
	linkedList->Head = NULL;
	linkedList->Tail = NULL;
	linkedList->Funcs = funcs;
}

void eaDSLinkedListReset(eaDSLinkedList * linkedList)
{
	while(!eaDSLinkedListIsEmpty(linkedList))
	{
		ItemLL * tmp = linkedList->Head;

		linkedList->Head = tmp->Next;
		linkedList->Funcs.dataClear(tmp->Data);

		free(tmp);
	}
	linkedList->Tail = NULL;
}

void eaDSLinkedListClear(eaDSLinkedList * linkedList)
{
	eaDSLinkedListReset(linkedList);
}

void eaDSLinkedListSort(eaDSLinkedList * linkedList)
{
	//TODO:
}

int eaDSLinkedListIsEmpty(const eaDSLinkedList * linkedList)
{
	if(linkedList->Head == NULL)
	{
		return 1;
	}
	return 0;
}

int eaDSLinkedListAdd(eaDSLinkedList * linkedList, const void * data)
{
	ItemLL * iter = linkedList->Head, * tmp;

	if((tmp = (ItemLL *) malloc(sizeof(ItemLL))) == NULL)
	{
		perror("Error: eaDSLinkedListInsert\n");
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = linkedList->Funcs.dataCreat(linkedList->Funcs.SumSize);
	linkedList->Funcs.dataCopy(tmp->Data, data, linkedList->Funcs.SumSize);

	if (iter == NULL)
	{
		linkedList->Head = tmp;
	}
	else
	{
		while (iter->Next != NULL)
		{
			iter = iter->Next;
		}

		iter->Next = tmp;
	}

	linkedList->Tail = tmp;

	return EXIT_SUCCESS;
}

int eaDSLinkedListRemove(eaDSLinkedList * linkedList, const void * data)
{
	int i;
	ItemLL * iter = linkedList->Head;

	for (i = 1; 0 != linkedList->Funcs.dataEqual(data, iter->Data, linkedList->Funcs.SumSize); i++)
	{
		if (iter->Next == NULL)
		{
			return EXIT_FAILURE;
		}
		iter = iter->Next;
	}

	linkedList->Funcs.dataClear(iter->Data);
	iter->Data = iter->Next->Data;
	void * p = iter->Next->Next;
	free(iter->Next);
	iter->Next = p;

	return EXIT_SUCCESS;
}

int eaDSLinkedListRemoveAt(eaDSLinkedList * linkedList, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head;

	if (0 != index)
	{
		for (i = 1; i < index; i++)
		{
			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		linkedList->Funcs.dataClear(iter->Data);
		iter->Data = iter->Next->Data;
		void * p = iter->Next->Next;
		free(iter->Next);
		iter->Next = p;
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int eaDSLinkedListInsert(eaDSLinkedList * linkedList, const void * data, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head, * tmp;

	if (0 != index)
	{
		if((tmp = (ItemLL *) malloc(sizeof(ItemLL))) == NULL)
		{
			perror("Error: eaDSLinkedListInsert\n");
			return EXIT_FAILURE;
		}

		for (i = 1; i < index; i++)
		{
			if ((iter->Next == NULL) && ((i + 1) != index))
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		tmp->Data = iter->Data;
		tmp->Next = iter->Next;
		iter->Next = tmp;

		iter->Data = linkedList->Funcs.dataCreat(linkedList->Funcs.SumSize);
		linkedList->Funcs.dataCopy(iter->Data, data, linkedList->Funcs.SumSize);

		if(tmp->Next == NULL)
		{
			linkedList->Tail = tmp;
		}
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int eaDSLinkedListGetFrom(const eaDSLinkedList * linkedList, void * data, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head;

	if (0 != index)
	{
		for (i = 1; i < index; i++)
		{
			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		linkedList->Funcs.dataCopy(data, iter->Data, linkedList->Funcs.SumSize);
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


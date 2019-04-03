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

void eaDSLinkedListInit(eaDSLinkedList * linkedList, StructDataInfo info)
{
	linkedList->Head = NULL;
	linkedList->Tail = NULL;
	linkedList->Info = info;
}

void eaDSLinkedListReset(eaDSLinkedList * linkedList)
{
	while(!eaDSLinkedListIsEmpty(linkedList))
	{
		ItemLL * tmp = linkedList->Head;

		linkedList->Head = tmp->Next;
		linkedList->Info.dataClear(tmp->Data);

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
		perror("Error: eaDSLinkedListAdd\n");
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = linkedList->Info.dataCreat(linkedList->Info.SumSize);
	linkedList->Info.dataCopy(tmp->Data, data, linkedList->Info.SumSize);

	if (iter == NULL)
	{
		linkedList->Head = tmp;
	}
	else
	{
		linkedList->Tail->Next = tmp;
	}

	linkedList->Tail = tmp;

	return EXIT_SUCCESS;
}

int eaDSLinkedListRemove(eaDSLinkedList * linkedList, const void * data)
{
	ItemLL * iter = linkedList->Head;

	while (0 != linkedList->Info.dataEqual(data, iter->Data, linkedList->Info.SumSize))
	{
		if (iter->Next == linkedList->Tail)
		{
			if (0 == linkedList->Info.dataEqual(data, iter->Next->Data, linkedList->Info.SumSize))
			{
				linkedList->Info.dataClear(iter->Next->Data);
				free(iter->Next);
				iter->Next = NULL;
				linkedList->Tail = iter;

				return EXIT_SUCCESS;
			}
			else
			{
				return EXIT_FAILURE;
			}
		}

		iter = iter->Next;
	}

	linkedList->Info.dataClear(iter->Data);

	void * p = iter->Next->Next;
	iter->Data = iter->Next->Data;
	free(iter->Next);
	iter->Next = p;

	return EXIT_SUCCESS;
}

int eaDSLinkedListRemoveAt(eaDSLinkedList * linkedList, const size_t index)
{
	size_t i;
	ItemLL * iter = linkedList->Head;

	if (0 != index)
	{
		for (i = 1; i < index; i++)
		{
			if ((iter->Next == linkedList->Tail) && ((i + 1) == index))
			{
				linkedList->Info.dataClear(iter->Next->Data);
				free(iter->Next);
				iter->Next = NULL;
				linkedList->Tail = iter;

				return EXIT_SUCCESS;
			}

			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}

			iter = iter->Next;
		}

		linkedList->Info.dataClear(iter->Data);
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
	size_t i;
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
			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		tmp->Data = iter->Data;
		tmp->Next = iter->Next;
		iter->Next = tmp;

		iter->Data = linkedList->Info.dataCreat(linkedList->Info.SumSize);
		linkedList->Info.dataCopy(iter->Data, data, linkedList->Info.SumSize);

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
	size_t i;
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

		linkedList->Info.dataCopy(data, iter->Data, linkedList->Info.SumSize);
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


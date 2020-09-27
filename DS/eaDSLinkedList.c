#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eaDSLinkedList.h"

typedef struct _ItemLL{
	void * Data;
	struct _ItemLL * Next;
} ItemLL;

struct _eaDSLinkedList{
	ItemLL * Head;
	ItemLL * Tail;
	void * (*dataCreateAndCopy)(const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

static void * copyAddress(const void * a)
{
	return (void *) a;
}

static int compareAddress(const void * a1, const void * a2)
{
	return !(a1 == a2);
}

eaDSLinkedList eaDSLinkedListInit(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
{
	eaDSLinkedList linkedList = (eaDSLinkedList) malloc(sizeof(struct _eaDSLinkedList));

	if (NULL == linkedList)
	{
		perror(NULL);
	}
	else
	{
		linkedList->Head = NULL;
		linkedList->Tail = NULL;
		linkedList->dataCreateAndCopy = (NULL == dataCreateAndCopy) ? copyAddress : dataCreateAndCopy;
		linkedList->dataCompare = (NULL == dataCompare) ? compareAddress : dataCompare;
		linkedList->dataClear = (NULL == dataClear) ? free : dataClear;
	}

	return linkedList;
}

void eaDSLinkedListReset(eaDSLinkedList linkedList)
{
	while(NULL != linkedList->Head)
	{
		ItemLL * tmp = linkedList->Head;
		linkedList->Head = tmp->Next;
		linkedList->dataClear(tmp->Data);

		free(tmp);
	}

	linkedList->Tail = NULL;
}

void eaDSLinkedListClear(eaDSLinkedList linkedList)
{
	eaDSLinkedListReset(linkedList);
	free(linkedList);
}

void eaDSLinkedListSort(eaDSLinkedList linkedList)
{
	/* 
		TODO:
		for warning unused-parameter
	*/
	linkedList->dataCompare(linkedList->Head, linkedList->Head);
}

int eaDSLinkedListIsEmpty(const eaDSLinkedList linkedList)
{
	return NULL == linkedList->Head;
}

int eaDSLinkedListAdd(eaDSLinkedList linkedList, const void * data)
{
	ItemLL * iter = linkedList->Head, * tmp;

	if(NULL == (tmp = (ItemLL *) malloc(sizeof(ItemLL))))
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	if (NULL == (tmp->Data = linkedList->dataCreateAndCopy(data)))
	{
		free(tmp);
		perror(NULL);

		return EXIT_FAILURE;
	}

	if (NULL == iter)
	{
		linkedList->Head = tmp;
	}
	else
	{
		linkedList->Tail->Next = tmp;
	}

	tmp->Next = NULL;
	linkedList->Tail = tmp;

	return EXIT_SUCCESS;
}
/*Look*/
void eaDSLinkedListRemove(eaDSLinkedList linkedList, const void * data)
{
	ItemLL * iter = linkedList->Head, * p;

	if (NULL == iter)
	{
		return;
	}

	if (iter == linkedList->Tail)
	{
		if (!linkedList->dataCompare(data, iter->Data))
		{
			linkedList->dataClear(iter->Data);
			free(iter);
			linkedList->Head = NULL;
			linkedList->Tail = NULL;
		}

		return;
	}

	while (0 != linkedList->dataCompare(data, iter->Data))
	{
		if (iter->Next == linkedList->Tail)
		{
			if (!linkedList->dataCompare(data, iter->Next->Data))
			{
				linkedList->dataClear(iter->Next->Data);
				free(iter->Next);
				iter->Next = NULL;
				linkedList->Tail = iter;
			}

			return;
		}

		iter = iter->Next;
	}

	linkedList->dataClear(iter->Data);

	if (iter->Next == linkedList->Tail)
	{
		linkedList->Tail = iter;
	}

	p = iter->Next->Next;
	iter->Data = iter->Next->Data;

	free(iter->Next);
	iter->Next = p;
}

void eaDSLinkedListRemoveAt(eaDSLinkedList linkedList, size_t index)
{
	void * p;
	size_t i;
	ItemLL * iter = linkedList->Head;

	if (NULL == iter)
	{
		return;
	}

	for (i = 0; i < index; i++)
	{
		if ((iter->Next == linkedList->Tail) && ((i + 1) == index))
		{
			linkedList->dataClear(iter->Next->Data);
			free(iter->Next);
			iter->Next = NULL;
			linkedList->Tail = iter;

			return;
		}

		if (NULL == iter->Next)
		{
			if (0 == index)
			{
				linkedList->dataClear(iter->Data);
				free(iter);
				linkedList->Head = NULL;
				linkedList->Tail = NULL;
			}

			return;
		}

		iter = iter->Next;
	}

	linkedList->dataClear(iter->Data);

	p = iter->Next->Next;
	iter->Data = iter->Next->Data;

	free(iter->Next);
	iter->Next = p;
}

int eaDSLinkedListInsert(eaDSLinkedList linkedList, const void * data, size_t index)
{
	size_t i;
	void * p;
	ItemLL * iter = linkedList->Head, * tmp = (ItemLL *) malloc(sizeof(ItemLL));

	if(NULL == tmp)
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	if (NULL == (p = linkedList->dataCreateAndCopy(data)))
	{
		free(tmp);
		perror(NULL);

		return EXIT_FAILURE;
	}

	for (i = 0; i < index; i++)
	{
		if (NULL == iter)
		{
			return EXIT_FAILURE;
		}
		iter = iter->Next;
	}

	if (0 == index || NULL == iter)
	{
		tmp->Next = iter;
		iter = tmp;

		if (0 == index)
		{
			linkedList->Head = tmp;
		}
	}
	else
	{
		tmp->Data = iter->Data;
		tmp->Next = iter->Next;
		iter->Next = tmp;
	}

	iter->Data = p;

	if (NULL == iter->Next)
	{
		linkedList->Tail = iter;
	}

	return EXIT_SUCCESS;
}

void * eaDSLinkedListGetFrom(const eaDSLinkedList linkedList, size_t index)
{
	size_t i = 0;
	void * data = NULL;
	ItemLL * iter = linkedList->Head;

	while (NULL != iter)
	{
		if (index == i++)
		{
			if (NULL == (data = linkedList->dataCreateAndCopy(iter->Data)))
			{
				perror(NULL);
			}

			break;
		}

		iter = iter->Next;
	}

	return data;
}

void * eaDSLinkedListGetAddressFrom(const eaDSLinkedList linkedList, size_t index)
{
	size_t i = 0;
	ItemLL * iter = linkedList->Head;

	while (NULL != iter)
	{
		if (index == i++)
		{
			return iter->Data;
		}

		iter = iter->Next;
	}

	return NULL;
}

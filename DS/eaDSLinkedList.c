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
	void * (*dataCreate)(size_t);
	void * (*dataCopy)(void *, const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

eaDSLinkedList eaDSLinkedListInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
{
	eaDSLinkedList linkedList;

	linkedList = (eaDSLinkedList) malloc(sizeof(struct _eaDSLinkedList));

	if (NULL == linkedList)
	{
		perror(NULL);
	}
	else
	{
		linkedList->Head = NULL;
		linkedList->Tail = NULL;
		linkedList->dataCreate = dataCreate;
		linkedList->dataCopy = dataCopy;
		linkedList->dataCompare = dataCompare;
		linkedList->dataClear = dataClear;
	}

	return linkedList;
}

void eaDSLinkedListReset(eaDSLinkedList linkedList)
{
	while(NULL != linkedList->Head)
	{
		ItemLL * tmp;

		tmp = linkedList->Head;
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
	/*TODO:*/
}

int eaDSLinkedListIsEmpty(const eaDSLinkedList linkedList)
{
	if(NULL == linkedList->Head)
	{
		return 1;
	}

	return 0;
}

int eaDSLinkedListAdd(eaDSLinkedList linkedList, const void * data)
{
	ItemLL * iter, * tmp;

	iter = linkedList->Head;

	if(NULL == (tmp = (ItemLL *) malloc(sizeof(ItemLL))))
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	tmp->Data = linkedList->dataCreate(1);

	if (NULL == tmp->Data)
	{
		free(tmp);
		perror(NULL);

		return EXIT_FAILURE;
	}

	linkedList->dataCopy(tmp->Data, data);

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

void eaDSLinkedListRemove(eaDSLinkedList linkedList, const void * data)
{
	ItemLL * iter, * p;

	if (NULL == linkedList->Head)
	{
		return;
	}

	iter = linkedList->Head;

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

	p = iter->Next->Next;
	iter->Data = iter->Next->Data;

	free(iter->Next);
	iter->Next = p;
}

void eaDSLinkedListRemoveAt(eaDSLinkedList linkedList, const size_t index)
{
	void * p;
	size_t i;
	ItemLL * iter;

	if (NULL == linkedList->Head)
	{
		return;
	}

	iter = linkedList->Head;

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

		if (iter->Next == NULL)
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

int eaDSLinkedListInsert(eaDSLinkedList linkedList, const void * data, const size_t index)
{
	size_t i;
	ItemLL * iter, * tmp, * p;

	if((tmp = (ItemLL *) malloc(sizeof(ItemLL))) == NULL)
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	if((p = linkedList->dataCreate(1)) == NULL)
	{
		free(tmp);
		perror(NULL);

		return EXIT_FAILURE;
	}

	iter = linkedList->Head;

	for (i = 0; i < index; i++)
	{
		if (iter == NULL)
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
	linkedList->dataCopy(iter->Data, data);

	if (iter->Next == NULL)
	{
		linkedList->Tail = iter;
	}

	return EXIT_SUCCESS;
}

int eaDSLinkedListGetFrom(const eaDSLinkedList linkedList, void * data, const size_t index)
{
	size_t i;
	ItemLL * iter;

	i = 0;
	iter = linkedList->Head;

	while (NULL != iter)
	{
		if (index == i++)
		{
			linkedList->dataCopy(data, iter->Data);

			return EXIT_SUCCESS;
		}

		iter = iter->Next;
	}

	return EXIT_FAILURE;
}

void * eaDSLinkedListGetAddressFrom(const eaDSLinkedList linkedList, const size_t index)
{
	size_t i;
	ItemLL * iter;

	i = 0;
	iter = linkedList->Head;

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

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
	eaDSDataInfo Info;
};

eaDSLinkedList eaDSLinkedListInit(eaDSDataInfo * info)
{
	eaDSLinkedList linkedList;

	linkedList = (eaDSLinkedList) malloc(sizeof(struct _eaDSLinkedList));

	if (NULL == linkedList)
	{
		EA_ERROR(__func__);
	}
	else
	{
		linkedList->Head = NULL;
		linkedList->Tail = NULL;

		if (NULL == info)
		{
			linkedList->Info = (eaDSDataInfo){sizeof(int), free, malloc, memcpy, memcmp};
		}
		else
		{
			linkedList->Info = *info;
		}
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
		linkedList->Info.dataClear(tmp->Data);

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
		EA_ERROR(__func__);

		return EXIT_FAILURE;
	}

	tmp->Data = linkedList->Info.dataCreat(linkedList->Info.SumSize);

	if (NULL == tmp->Data)
	{
		free(tmp);
		EA_ERROR(__func__);

		return EXIT_FAILURE;
	}

	linkedList->Info.dataCopy(tmp->Data, data, linkedList->Info.SumSize);

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
		if (!linkedList->Info.dataEqual(data, iter->Data, linkedList->Info.SumSize))
		{
			linkedList->Info.dataClear(iter->Data);
			free(iter);
			linkedList->Head = NULL;
			linkedList->Tail = NULL;
		}

		return;
	}

	while (0 != linkedList->Info.dataEqual(data, iter->Data, linkedList->Info.SumSize))
	{
		if (iter->Next == linkedList->Tail)
		{
			if (!linkedList->Info.dataEqual(data, iter->Next->Data, linkedList->Info.SumSize))
			{
				linkedList->Info.dataClear(iter->Next->Data);
				free(iter->Next);
				iter->Next = NULL;
				linkedList->Tail = iter;
			}

			return;
		}

		iter = iter->Next;
	}

	linkedList->Info.dataClear(iter->Data);

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
			linkedList->Info.dataClear(iter->Next->Data);
			free(iter->Next);
			iter->Next = NULL;
			linkedList->Tail = iter;

			return;
		}

		if (iter->Next == NULL)
		{
			if (0 == index)
			{
				linkedList->Info.dataClear(iter->Data);
				free(iter);
				linkedList->Head = NULL;
				linkedList->Tail = NULL;
			}

			return;
		}

		iter = iter->Next;
	}

	linkedList->Info.dataClear(iter->Data);

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
		EA_ERROR(__func__);

		return EXIT_FAILURE;
	}

	if((p = linkedList->Info.dataCreat(linkedList->Info.SumSize)) == NULL)
	{
		free(tmp);
		EA_ERROR(__func__);

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
	linkedList->Info.dataCopy(iter->Data, data, linkedList->Info.SumSize);

	if (iter->Next == NULL)
	{
		linkedList->Tail = iter;
	}

	return EXIT_SUCCESS;
}

int eaDSLinkedListGetFrom(const eaDSLinkedList linkedList, void * data, const size_t index)
{
	size_t i = 0;
	ItemLL * iter;

	iter = linkedList->Head;

	while (NULL != iter)
	{
		if (index == i++)
		{
			linkedList->Info.dataCopy(data, iter->Data, linkedList->Info.SumSize);

			return EXIT_SUCCESS;
		}

		iter = iter->Next;
	}

	return EXIT_FAILURE;
}

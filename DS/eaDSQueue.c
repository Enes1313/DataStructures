#include <stdlib.h>
#include <string.h>
#include "eaDSQueue.h"

typedef struct _ItemQue {
	void * Data;
	struct _ItemQue * Next;
} ItemQue;

struct _eaDSQueue {
	ItemQue * Front;
	ItemQue * Rear;
	eaDSDataInfo Info;
};

eaDSQueue eaDSQueueInit(eaDSDataInfo * info)
{
	eaDSQueue queue;

	queue = (eaDSQueue) malloc(sizeof(struct _eaDSQueue));

	if (NULL == queue)
	{
		EA_ERROR(__func__);
	}
	else
	{
		queue->Front = NULL;
		queue->Rear = NULL;

		if (NULL == info)
		{
			queue->Info = (eaDSDataInfo){sizeof(int), free, malloc, memcpy, memcmp};
		}
		else
		{
			queue->Info = *info;
		}
	}

	return queue;
}

void eaDSQueueReset(eaDSQueue queue)
{
	while (NULL != queue->Front)
	{
		ItemQue * tmp;

		tmp = queue->Front;
		queue->Front = tmp->Next;
		queue->Info.dataClear(tmp->Data);

		free(tmp);
	}

	queue->Rear = NULL;
}

void eaDSQueueClear(eaDSQueue queue)
{
	eaDSQueueReset(queue);
	free(queue);
}

int eaDSQueueIsEmpty(const eaDSQueue queue)
{
	if (NULL == queue->Front)
	{
		return 1;
	}

	return 0;
}

int eaDSQueueDequeue(eaDSQueue queue, void * data)
{
	void * p;

	if (NULL == queue->Front)
	{
		return EXIT_FAILURE;
	}

	queue->Info.dataCopy(data, queue->Front->Data, queue->Info.SumSize);
	queue->Info.dataClear(queue->Front->Data);

	p = queue->Front;
	queue->Front = queue->Front->Next;
	free(p);

	if (queue->Front == NULL)
	{
		queue->Rear = NULL;
	}

	return EXIT_SUCCESS;
}

int eaDSQueueEnqueue(eaDSQueue queue, const void * data)
{
	ItemQue * tmp;

	if ((tmp = (ItemQue *)malloc(sizeof(ItemQue))) == NULL)
	{
		EA_ERROR(__func__);
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = queue->Info.dataCreat(queue->Info.SumSize);
	queue->Info.dataCopy(tmp->Data, data, queue->Info.SumSize);

	if (queue->Front == NULL)
	{
		queue->Front = tmp;
	}
	else
	{
		queue->Rear->Next = tmp;
	}

	queue->Rear = tmp;
	
	return EXIT_SUCCESS;
}

int eaDSQueuePeekQueue(const eaDSQueue queue, void * data)
{
	if (queue->Front == NULL)
	{
		return EXIT_FAILURE;
	}

	queue->Info.dataCopy(data, queue->Front->Data, queue->Info.SumSize);

	return EXIT_SUCCESS;
}


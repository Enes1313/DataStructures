/*
 * eaDSQueue.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSQueue.h"

/*
 * Queue
 */

void eaDSQueueInit(eaDSQueue * queue, StructDataInfo info)
{
	queue->Front = NULL;
	queue->Rear = NULL;
	queue->Info = info;
}

void eaDSQueueReset(eaDSQueue * queue)
{
	while (!eaDSQueueIsEmpty(queue))
	{
		ItemQue * tmp = queue->Front;

		queue->Front = tmp->Next;
		queue->Info.dataClear(tmp->Data);

		free(tmp);
	}
	queue->Front = NULL;
}

void eaDSQueueClear(eaDSQueue * queue)
{
	eaDSQueueReset(queue);
}

int eaDSQueueIsEmpty(const eaDSQueue * queue)
{
	if (queue->Front == NULL)
	{
		return 1;
	}

	return 0;
}

int eaDSQueueDequeue(eaDSQueue * queue, void * data)
{
	if (queue->Front == NULL)
	{
		return EXIT_FAILURE;
	}

	queue->Info.dataCopy(data, queue->Front->Data, queue->Info.SumSize);
	queue->Info.dataClear(queue->Front->Data);

	void * p = queue->Front;
	queue->Front = queue->Front->Next;
	free(p);

	if (queue->Front == NULL)
	{
		queue->Rear = NULL;
	}

	return EXIT_SUCCESS;
}

int eaDSQueueEnqueue(eaDSQueue * queue, const void * data)
{
	ItemQue * iter = queue->Front, *tmp;

	if ((tmp = (ItemQue *)malloc(sizeof(ItemQue))) == NULL)
	{
		perror("Error: eaDSQueueEnqueue\n");
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = queue->Info.dataCreat(queue->Info.SumSize);
	queue->Info.dataCopy(tmp->Data, data, queue->Info.SumSize);

	if (iter == NULL)
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

int eaDSQueuePeekQueue(const eaDSQueue * queue, void * data)
{
	if (queue->Front == NULL)
	{
		return EXIT_FAILURE;
	}

	queue->Info.dataCopy(data, queue->Front->Data, queue->Info.SumSize);

	return EXIT_SUCCESS;
}


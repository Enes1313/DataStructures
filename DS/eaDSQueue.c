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
	void * (*dataCreateAndCopy)(const void *);
	void (*dataClear)(void *);
};

eaDSQueue eaDSQueueInit(void * (*dataCreateAndCopy)(const void *), void (*dataClear)(void *))
{
	eaDSQueue queue;

	queue = (eaDSQueue) malloc(sizeof(struct _eaDSQueue));

	if (NULL == queue)
	{
		perror(NULL);
	}
	else
	{
		queue->Front = NULL;
		queue->Rear = NULL;
		queue->dataCreateAndCopy = dataCreateAndCopy;
		queue->dataClear = dataClear;
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
		queue->dataClear(tmp->Data);

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

void * eaDSQueueDequeue(eaDSQueue queue)
{
	void * p, * data;

	if (NULL == queue->Front)
	{
		return NULL;
	}

	data = queue->dataCreateAndCopy(queue->Front->Data);

	if (NULL == data)
	{
		perror(NULL);
	}

	queue->dataClear(queue->Front->Data);

	p = queue->Front;
	queue->Front = queue->Front->Next;
	free(p);

	if (queue->Front == NULL)
	{
		queue->Rear = NULL;
	}

	return data;
}

int eaDSQueueEnqueue(eaDSQueue queue, const void * data)
{
	ItemQue * tmp;

	if ((tmp = (ItemQue *)malloc(sizeof(ItemQue))) == NULL)
	{
		perror(NULL);
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = queue->dataCreateAndCopy(data);

	if (NULL == tmp->Data)
	{
		free(tmp);
		perror(NULL);

		return EXIT_FAILURE;
	}

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

void * eaDSQueuePeekValue(const eaDSQueue queue)
{
	void * data;

	data = NULL;

	if (queue->Front == NULL)
	{
		return NULL;
	}

	data = queue->dataCreateAndCopy(queue->Front->Data);

	if (NULL == data)
	{
		perror(NULL);
	}

	return data;
}

void * eaDSQueuePeekAddress(const eaDSQueue queue)
{
	if (queue->Front == NULL)
	{
		return NULL;
	}

	return queue->Front->Data;
}

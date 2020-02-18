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
	void * (*dataCreate)(size_t);
	void * (*dataCopy)(void *, const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

eaDSQueue eaDSQueueInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
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
		queue->dataCreate = dataCreate;
		queue->dataCopy = dataCopy;
		queue->dataCompare = dataCompare;
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

int eaDSQueueDequeue(eaDSQueue queue, void * data)
{
	void * p;

	if (NULL == queue->Front)
	{
		return EXIT_FAILURE;
	}

	queue->dataCopy(data, queue->Front->Data);
	queue->dataClear(queue->Front->Data);

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
		perror(NULL);
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = queue->dataCreate(1);
	queue->dataCopy(tmp->Data, data);

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

	queue->dataCopy(data, queue->Front->Data);

	return EXIT_SUCCESS;
}


#include <stdlib.h>
#include <string.h>
#include "eaDSCircularBuffer.h"

#define DEFAULT_CAPACITY 1024

struct _eaDSCircularBuffer {
	void * Data;
	size_t Head, Tail, Capacity;
	void * (*dataCreate)(size_t);
	void * (*dataCopy)(void *, const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

eaDSCircularBuffer eaDSCircularBufferInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
{
	return eaDSCircularBufferInitWithDetails(dataCreate, dataCopy, dataCompare, dataClear, DEFAULT_CAPACITY);
}

eaDSCircularBuffer eaDSCircularBufferInitWithDetails(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *), size_t capacity)
{
	eaDSCircularBuffer circularBuffer;

	circularBuffer = (eaDSCircularBuffer) calloc(1, sizeof(struct _eaDSCircularBuffer));

	if (NULL == circularBuffer)
	{
		perror(NULL);
	}
	else
	{
		circularBuffer->Data = dataCreate(capacity);

		if (NULL == circularBuffer->Data)
		{
			perror(NULL);
			free(circularBuffer);
			circularBuffer = NULL;
		}
		else
		{
			circularBuffer->Capacity = capacity;
		}

		circularBuffer->dataCreate = dataCreate;
		circularBuffer->dataCopy = dataCopy;
		circularBuffer->dataCompare = dataCompare;
		circularBuffer->dataClear = dataClear;
	}

	return circularBuffer;
}

void eaDSCircularBufferReset(eaDSCircularBuffer circularBuffer)
{
	circularBuffer->Head = 0;
	circularBuffer->Tail = 0;
}

void eaDSCircularBufferClear(eaDSCircularBuffer circularBuffer)
{
	circularBuffer->dataClear(circularBuffer->Data);
	free(circularBuffer);
}

void eaDSCircularBufferAdd(eaDSCircularBuffer circularBuffer, const void * data)
{
	circularBuffer->dataCopy(circularBuffer->Data, data);
	circularBuffer->Tail++;
	if (circularBuffer->Tail == circularBuffer->Capacity)
	{
		circularBuffer->Tail = 0;
	}
}

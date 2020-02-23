#include <stdlib.h>
#include <string.h>
#include "eaDSCircularBuffer.h"

#define DEFAULT_CAPACITY 1024

struct _eaDSCircularBuffer {
	void * Data;
	size_t Head, Tail, Capacity;
	int Stop;
	size_t SizeOfData;
	void * (*dataCreate)(size_t);
	void * (*dataCopy)(void *, const void *, size_t);
	int (*dataCompare)(const void *, const void *, size_t);
	void (*dataClear)(void *);
};

eaDSCircularBuffer eaDSCircularBufferInit(size_t sizeOfData, void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *, size_t), int (*dataCompare)(const void *, const void *, size_t), void (*dataClear)(void *))
{
	return eaDSCircularBufferInitWithDetails(sizeOfData, dataCreate, dataCopy, dataCompare, dataClear, DEFAULT_CAPACITY);
}

eaDSCircularBuffer eaDSCircularBufferInitWithDetails(size_t sizeOfData, void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *, size_t), int (*dataCompare)(const void *, const void *, size_t), void (*dataClear)(void *), size_t capacity)
{
	eaDSCircularBuffer circularBuffer;

	circularBuffer = (eaDSCircularBuffer) calloc(1, sizeof(struct _eaDSCircularBuffer));

	if (NULL == circularBuffer)
	{
		perror(NULL);
	}
	else
	{
		circularBuffer->Data = dataCreate(sizeOfData * capacity);

		if (NULL == circularBuffer->Data)
		{
			perror(NULL);
			free(circularBuffer);
			circularBuffer = NULL;
		}
		else
		{
			circularBuffer->Capacity = capacity;
			circularBuffer->SizeOfData = sizeOfData;
			circularBuffer->dataCreate = dataCreate;
			circularBuffer->dataCopy = dataCopy;
			circularBuffer->dataCompare = dataCompare;
			circularBuffer->dataClear = dataClear;
		}
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

int eaDSCircularBufferAdd(eaDSCircularBuffer circularBuffer, const void * data, size_t len)
{
	if (circularBuffer->Stop)
	{
		return EXIT_FAILURE;
	}

	if (circularBuffer->Tail >= circularBuffer->Head)
	{
		if (len <= (circularBuffer->Capacity - circularBuffer->Tail))
		{
			circularBuffer->dataCopy((char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Tail, data, circularBuffer->SizeOfData * len);
			circularBuffer->Tail += len;

			if (circularBuffer->Tail == circularBuffer->Capacity)
			{
				circularBuffer->Tail = 0;
			}
		}
		else
		{
			if (len > (circularBuffer->Head + circularBuffer->Capacity - circularBuffer->Tail))
			{
				return EXIT_FAILURE;
			}
			else
			{
				circularBuffer->dataCopy((char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Tail, data, circularBuffer->SizeOfData * (circularBuffer->Capacity - circularBuffer->Tail));
				circularBuffer->dataCopy(circularBuffer->Data, (char *)data + circularBuffer->SizeOfData * (circularBuffer->Capacity - circularBuffer->Tail), circularBuffer->SizeOfData * (len - circularBuffer->Capacity + circularBuffer->Tail));
				circularBuffer->Tail = len - circularBuffer->Capacity + circularBuffer->Tail;
			}
		}
	}
	else
	{
		if (len > (circularBuffer->Head - circularBuffer->Tail))
		{
			return EXIT_FAILURE;
		}
		else
		{
			circularBuffer->dataCopy((char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Tail, data, circularBuffer->SizeOfData * len);
			circularBuffer->Tail += len;
		}
	}

	if (circularBuffer->Head == circularBuffer->Tail)
	{
		circularBuffer->Stop = 1;
	}

	return EXIT_SUCCESS;
}

int eaDSCircularBufferGet(eaDSCircularBuffer circularBuffer, void * data, size_t numberOfData)
{
	if (numberOfData > circularBuffer->Capacity)
	{
		return EXIT_FAILURE;
	}

	if (circularBuffer->Tail < circularBuffer->Head)
	{
		if (numberOfData <= (circularBuffer->Capacity - circularBuffer->Head))
		{
			circularBuffer->dataCopy(data, (char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Head, circularBuffer->SizeOfData * numberOfData);
			circularBuffer->Head += numberOfData;

			if (circularBuffer->Head == circularBuffer->Capacity)
			{
				circularBuffer->Head = 0;
			}
		}
		else
		{
			if (numberOfData > (circularBuffer->Tail + circularBuffer->Capacity - circularBuffer->Head))
			{
				return EXIT_FAILURE;
			}
			else
			{
				circularBuffer->dataCopy(data, (char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Head, circularBuffer->SizeOfData * (circularBuffer->Capacity - circularBuffer->Head));
				circularBuffer->dataCopy((char *)data + circularBuffer->SizeOfData * (circularBuffer->Capacity - circularBuffer->Head),circularBuffer->Data, circularBuffer->SizeOfData * (numberOfData - circularBuffer->Capacity + circularBuffer->Head));
				circularBuffer->Head = numberOfData - circularBuffer->Capacity + circularBuffer->Head;
			}
		}
	}
	else
	{
		if (numberOfData > (circularBuffer->Tail - circularBuffer->Head))
		{
			return EXIT_FAILURE;
		}
		else
		{
			circularBuffer->dataCopy(data, (char *)circularBuffer->Data + circularBuffer->SizeOfData * circularBuffer->Head, circularBuffer->SizeOfData * numberOfData);
			circularBuffer->Head += numberOfData;
		}
	}

	return EXIT_SUCCESS;
}

int eaDSCircularBufferGetIndex(eaDSCircularBuffer circularBuffer, const void * data, size_t numberOfData, size_t * len)
{
	size_t i;

	if (circularBuffer->Head <= circularBuffer->Tail)
	{
		for (i = circularBuffer->Head; i < circularBuffer->Tail; ++i)
		{
			if (circularBuffer->dataCompare((char *)circularBuffer->Data + i, data, circularBuffer->SizeOfData * numberOfData) == 0)
			{
				*len = i - circularBuffer->Head;

				return EXIT_SUCCESS;
			}
		}
	}
	else
	{
		for (i = circularBuffer->Head; i < circularBuffer->Capacity; ++i)
		{
			if (circularBuffer->dataCompare((char *)circularBuffer->Data + i, data, circularBuffer->SizeOfData * numberOfData) == 0)
			{
				*len = i - circularBuffer->Head;

				return EXIT_SUCCESS;
			}
		}

		for (i = 0; i < circularBuffer->Tail; ++i)
		{
			if (circularBuffer->dataCompare((char *)circularBuffer->Data + i, data, circularBuffer->SizeOfData * numberOfData) == 0)
			{
				*len = i + circularBuffer->Capacity - circularBuffer->Head;

				return EXIT_SUCCESS;
			}
		}
	}

	return EXIT_FAILURE;
}

int eaDSCircularBufferMoveHead(eaDSCircularBuffer circularBuffer, size_t len)
{
	if (circularBuffer->Head + len <= circularBuffer->Tail)
	{
		circularBuffer->Head += len;

		return EXIT_SUCCESS;
	}
	else if ((circularBuffer->Head + len) < circularBuffer->Capacity)
	{
		circularBuffer->Head += len;

		return EXIT_SUCCESS;
	}
	else if(((circularBuffer->Head + len) % circularBuffer->Capacity) < circularBuffer->Tail)
	{
		circularBuffer->Head = (circularBuffer->Head + len) % circularBuffer->Capacity;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

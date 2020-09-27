#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eaDSStack.h"

#define DEFAULT_EXP_FACTOR 2
#define DEFAULT_STARTING_CAPACITY 4

struct _eaDSStack {
	void ** Data;
	size_t Count, Capacity;
	unsigned short ExpFactor, StartingCapacity;
	void * (*dataCreateAndCopy)(const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

static void * copyAddress(const void * a)
{
	return (void *) a;
}

eaDSStack eaDSStackInit(void * (*dataCreateAndCopy)(const void *), void (*dataClear)(void *))
{
	return eaDSStackInitWithDetails(dataCreateAndCopy, dataClear, DEFAULT_EXP_FACTOR, DEFAULT_STARTING_CAPACITY);
}

eaDSStack eaDSStackInitWithDetails(void * (*dataCreateAndCopy)(const void *), void (*dataClear)(void *), unsigned short expFactor, unsigned short startingCapacity)
{
	eaDSStack stack;

	stack = (eaDSStack) malloc(sizeof(struct _eaDSStack));

	if (NULL == stack)
	{
		perror(NULL);
	}
	else
	{
		stack->StartingCapacity = startingCapacity ? startingCapacity : DEFAULT_STARTING_CAPACITY;
		stack->Data = (void **)malloc(stack->StartingCapacity * sizeof(void *));

		if (NULL == stack->Data)
		{
			perror(NULL);
			free(stack);
			stack = NULL;
		}
		else
		{
			stack->Count = 0;
			stack->Capacity = stack->StartingCapacity;
			stack->ExpFactor = (expFactor < 2) ? DEFAULT_EXP_FACTOR : expFactor;
			stack->dataCreateAndCopy = (dataCreateAndCopy == NULL) ? copyAddress : dataCreateAndCopy;
			stack->dataClear = (dataClear == NULL) ? free : dataClear;
		}
	}

	return stack;
}

int eaDSStackReset(eaDSStack stack)
{
	if (NULL == stack->Data)
	{
		stack->Data = (void **) malloc(stack->Capacity * sizeof(void *));

		if (NULL == stack->Data)
		{
			perror(NULL);

			return EXIT_FAILURE;
		}
	}
	else
	{
		while (stack->Count)
		{
			stack->dataClear(stack->Data[--stack->Count]);
		}

		if (stack->StartingCapacity < stack->Capacity)
		{
			free(stack->Data);
			stack->Data = (void **) malloc(stack->Capacity * sizeof(void *));

			if (NULL == stack->Data)
			{
				perror(NULL);

				return EXIT_FAILURE;
			}

			stack->Capacity = stack->StartingCapacity;
		}
	}

	return EXIT_SUCCESS;
}

void eaDSStackClear(eaDSStack stack)
{
	if (NULL != stack->Data)
	{
		while(stack->Count)
		{
			stack->dataClear(stack->Data[--stack->Count]);
		}

		free(stack->Data);
	}

	free(stack);
}

size_t eaDSStackGetCount(const eaDSStack stack)
{
	return stack->Count;
}

size_t eaDSStackGetCapacity(const eaDSStack stack)
{
	return stack->Capacity;
}

void * eaDSStackPop(eaDSStack stack)
{
	void * data;

	data = NULL;

	if (stack->Count)
	{
		data = stack->dataCreateAndCopy(stack->Data[stack->Count - 1]);

		if (data != NULL)
		{
			stack->dataClear(stack->Data[--stack->Count]);
		}
		else
		{
			perror(NULL);
		}
	}

	return data;
}

int eaDSStackPush(eaDSStack stack, const void * data)
{
	void * item;

	if (NULL == (item = stack->dataCreateAndCopy(data)))
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	if (stack->Count == stack->Capacity)
	{
		size_t i;
		void ** tmp;

		stack->Capacity *= stack->ExpFactor;
		tmp = (void **) malloc(stack->Capacity * sizeof(void *));

		if (NULL == tmp)
		{
			perror(NULL);
			stack->Capacity /= stack->ExpFactor;

			return EXIT_FAILURE;
		}

		for (i = 0; i < stack->Count; i++)
		{
			tmp[i] = stack->Data[i];
		}

		free(stack->Data);
		stack->Data = tmp;
	}

	stack->Data[stack->Count] = item;
	stack->Count++;

	return EXIT_SUCCESS;
}

void * eaDSStackPeekStack(const eaDSStack stack)
{
	void * data;

	data = NULL;

	if (stack->Count)
	{
		data = stack->dataCreateAndCopy(stack->Data[stack->Count - 1]);

		if (NULL == data)
		{
			perror(NULL);
		}
	}

	return data;
}

void * eaDSStackPeekStackGetAddress(const eaDSStack stack)
{
	if (stack->Count)
	{
		return stack->Data[stack->Count - 1];
	}

	return NULL;
}

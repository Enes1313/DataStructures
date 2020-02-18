#include <stdlib.h>
#include <string.h>
#include "eaDSStack.h"

#define DEFAULT_EXP_FACTOR 2
#define DEFAULT_STARTING_CAPACITY 4

struct _eaDSStack {
	void ** Data;
	size_t Count, Capacity;
	unsigned short ExpFactor, StartingCapacity;
	void * (*dataCreate)(size_t);
	void * (*dataCopy)(void *, const void *);
	int (*dataCompare)(const void *, const void *);
	void (*dataClear)(void *);
};

eaDSStack eaDSStackInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
{
	return eaDSStackInitWithDetails(dataCreate, dataCopy, dataCompare, dataClear, DEFAULT_EXP_FACTOR, DEFAULT_STARTING_CAPACITY);
}

eaDSStack eaDSStackInitWithDetails(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *), unsigned short expFactor, unsigned short startingCapacity)
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
			stack->dataCreate = dataCreate;
			stack->dataCopy = dataCopy;
			stack->dataCompare = dataCompare;
			stack->dataClear = dataClear;
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

int eaDSStackPop(eaDSStack stack, void * data)
{
	if (stack->Count)
	{
		stack->Count--;
		stack->dataCopy(data, stack->Data[stack->Count]);
		stack->dataClear(stack->Data[stack->Count]);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int eaDSStackPush(eaDSStack stack, const void * data)
{
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

	stack->Data[stack->Count] = stack->dataCreate(1);

	if (NULL == stack->Data[stack->Count])
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	stack->dataCopy(stack->Data[stack->Count], data);
	stack->Count++;

	return EXIT_SUCCESS;
}

int eaDSStackPeekStack(const eaDSStack stack, void * data)
{
	if (stack->Count)
	{
		stack->dataCopy(data, stack->Data[stack->Count - 1]);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

void * eaDSStackPeekStackGetAddress(const eaDSStack stack)
{
	if (stack->Count)
	{
		return stack->Data[stack->Count - 1];
	}

	return NULL;
}

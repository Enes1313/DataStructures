#include <stdlib.h>
#include <string.h>
#include "eaDSStack.h"

#define DEFAULT_EXP_FACTOR 2
#define DEFAULT_STARTING_CAPACITY 4

struct _eaDSStack {
	void ** Data;
	size_t Count, Capacity;
	unsigned short ExpFactor, StartingCapacity;
	eaDSInfosForData Infos;
};

eaDSStack eaDSStackInit(eaDSInfosForData * infos)
{
	return eaDSStackInitWithDetails(infos, DEFAULT_EXP_FACTOR, DEFAULT_STARTING_CAPACITY);
}

eaDSStack eaDSStackInitWithDetails(eaDSInfosForData * infos, unsigned short expFactor, unsigned short startingCapacity)
{
	eaDSStack stack;

	stack = (eaDSStack) malloc(sizeof(struct _eaDSStack));

	if (NULL == stack)
	{
		perror(__func__);
	}
	else
	{
		stack->StartingCapacity = startingCapacity ? startingCapacity : DEFAULT_STARTING_CAPACITY;
		stack->Data = (void **)malloc(stack->StartingCapacity * sizeof(void *));

		if (NULL == stack->Data)
		{
			perror(__func__);
			free(stack);
			stack = NULL;
		}
		else
		{
			stack->Count = 0;
			stack->Capacity = stack->StartingCapacity;
			stack->ExpFactor = (expFactor < 2) ? DEFAULT_EXP_FACTOR : expFactor;

			if (NULL == infos)
			{
				stack->Infos = (eaDSInfosForData){sizeof(int), free, malloc, memcpy, memcmp};
			}
			else
			{
				stack->Infos = *infos;
			}
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
			perror(__func__);

			return EXIT_FAILURE;
		}
	}
	else
	{
		while (stack->Count)
		{
			stack->Infos.dataClear(stack->Data[--stack->Count]);
		}

		if (stack->StartingCapacity < stack->Capacity)
		{
			free(stack->Data);
			stack->Data = (void **) malloc(stack->Capacity * sizeof(void *));

			if (NULL == stack->Data)
			{
				perror(__func__);

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
			stack->Infos.dataClear(stack->Data[--stack->Count]);
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
		stack->Infos.dataCopy(data, stack->Data[stack->Count], stack->Infos.SumSize);
		stack->Infos.dataClear(stack->Data[stack->Count]);

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
			perror(__func__);
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

	stack->Data[stack->Count] = stack->Infos.dataCreate(stack->Infos.SumSize);

	if (NULL == stack->Data[stack->Count])
	{
		perror(__func__);

		return EXIT_FAILURE;
	}

	stack->Infos.dataCopy(stack->Data[stack->Count], data, stack->Infos.SumSize);
	stack->Count++;

	return EXIT_SUCCESS;
}

int eaDSStackPeekStack(const eaDSStack stack, void * data)
{
	if (stack->Count)
	{
		stack->Infos.dataCopy(data, stack->Data[stack->Count - 1], stack->Infos.SumSize);

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eaDSStack.h"

struct _eaDSStack {
	void ** Data;
	size_t Count, Capacity;
	eaDSDataInfo Info;
};

eaDSStack eaDSStackInit(eaDSDataInfo * info)
{
	eaDSStack stack;

	stack = (eaDSStack) malloc(sizeof(struct _eaDSStack));

	if (NULL == stack)
	{
		EA_ERROR(__func__);
	}
	else
	{
		stack->Count = 0;
		stack->Capacity = 4;
		stack->Data = (void **)malloc(stack->Capacity * sizeof(void *));

		if (stack->Data == NULL)
		{
			EA_ERROR(__func__);
		}

		if (NULL == info)
		{
			stack->Info = (eaDSDataInfo){sizeof(int), free, malloc, memcpy, memcmp};
		}
		else
		{
			stack->Info = *info;
		}
	}

	return stack;
}

void eaDSStackReset(eaDSStack stack)
{
	if (NULL != stack->Data)
	{
		while (stack->Count)
		{
			stack->Info.dataClear(stack->Data[--stack->Count]);
		}

		if (4 < stack->Capacity)
		{
			free(stack->Data);

			stack->Capacity = 4;
			stack->Data = (void **) malloc(stack->Capacity * sizeof(void *));

			if (NULL == stack->Data)
			{
				EA_ERROR(__func__);
			}
		}
	}
	else
	{
		EA_INFO("In %s, context of S is NULL\n", __func__);
		stack->Data = (void **) malloc(stack->Capacity * sizeof(void *));

		if (NULL == stack->Data)
		{
			EA_ERROR(__func__);
		}
	}

	stack->Capacity = 4;
}

void eaDSStackClear(eaDSStack stack)
{
	if (NULL != stack->Data)
	{
		while(stack->Count)
		{
			stack->Info.dataClear(stack->Data[--stack->Count]);
		}
		free(stack->Data);
	}
	else
	{
		EA_INFO("In %s, context of S is NULL\n", __func__);
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
		stack->Info.dataCopy(data, stack->Data[stack->Count], stack->Info.SumSize);
		stack->Info.dataClear(stack->Data[stack->Count]);
		stack->Data[stack->Count] = NULL;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int eaDSStackPush(eaDSStack stack, const void * data)
{
	size_t i;

	if (NULL == stack->Data)
	{
		EA_INFO("In %s, context of S is NULL\n", __func__);

		return EXIT_FAILURE;
	}

	if (stack->Count == stack->Capacity)
	{
		void ** tmp;

		stack->Capacity += 4;
		tmp = (void **)malloc(stack->Capacity * sizeof(void *));

		if (NULL == tmp)
		{
			EA_ERROR(__func__);
			stack->Capacity -= 4;

			return EXIT_FAILURE;
		}

		for (i = 0; i < stack->Count; i++)
		{
			tmp[i] = stack->Data[i];
		}

		free(stack->Data);
		stack->Data = tmp;
	}

	stack->Data[stack->Count] = stack->Info.dataCreat(stack->Info.SumSize);

	if (NULL == stack->Data[stack->Count])
	{
		EA_ERROR(__func__);

		return EXIT_FAILURE;
	}

	stack->Info.dataCopy(stack->Data[stack->Count], data, stack->Info.SumSize);
	stack->Count++;

	return EXIT_SUCCESS;
}

int eaDSStackPeekStack(const eaDSStack stack, void * data)
{
	if (stack->Count)
	{
		stack->Info.dataCopy(data, stack->Data[stack->Count - 1], stack->Info.SumSize);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

/*
 * eaDSStack.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSStack.h"

/*
 * Stack
 */

void eaDSStackInit(eaDSStack * stack, StructDataInfo info)
{
	stack->Info = info;
	stack->Count = 0;
	stack->Capacity = 4;
	stack->Data = (void **)malloc(stack->Capacity * sizeof(void *));

	if (stack->Data == NULL)
	{
		perror("Error: eaDSStackInit\n");
	}
}

void eaDSStackReset(eaDSStack * stack)
{
	while (eaDSStackGetCount(stack))
	{
		stack->Info.dataClear(stack->Data[--stack->Count]);
	}

	stack->Capacity = 4;
}

void eaDSStackClear(eaDSStack * stack)
{
	eaDSStackReset(stack);

	if (stack->Data != NULL)
	{
		free(stack->Data);
	}
}

size_t eaDSStackGetCount(const eaDSStack * stack)
{
	return stack->Count;
}

size_t eaDSStackGetCapacity(const eaDSStack * stack)
{
	return stack->Capacity;
}

int eaDSStackPop(eaDSStack * stack, const void * data)
{
	size_t cnt = eaDSStackGetCount(stack);

	if (0 < cnt)
	{
		stack->Info.dataCopy(data, stack->Data[cnt - 1], stack->Info.SumSize);
		stack->Info.dataClear(stack->Data[cnt - 1]);
		stack->Data[cnt - 1] = NULL;
		stack->Count--;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int eaDSStackPush(eaDSStack * stack, const void * data)
{
	size_t i;

	if ((stack->Count + 1) == stack->Capacity)
	{
		stack->Capacity = stack->Count + 4;
		void ** tmp = (void **)malloc(stack->Capacity * sizeof(void *));

		if (NULL == tmp)
		{
			perror("Error: eaDSStackPush\n");
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
	stack->Info.dataCopy(stack->Data[stack->Count], data, stack->Info.SumSize);
	stack->Count++;

	return EXIT_SUCCESS;
}

int eaDSStackPeekStack(eaDSStack * stack, const void * data)
{
	if (eaDSStackGetCount(stack))
	{
		stack->Info.dataCopy(data, stack->Data[eaDSStackGetCount(stack) - 1], stack->Info.SumSize);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

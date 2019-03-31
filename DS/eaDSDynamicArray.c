/*
 * eaDSDynamicArray.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSDynamicArray.h"

/*
 * DynamicArray
 */

void eaDSDynamicArrayInit(eaDSDynamicArray * dynamicArray, StructDataInfo info)
{
	dynamicArray->Info = info;
	dynamicArray->Count = 0;
	dynamicArray->Capacity = 4;
	dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

	if (dynamicArray->Data == NULL)
	{
		perror("Error: eaDSDynamicArrayInit\n");
	}
}

void eaDSDynamicArrayReset(eaDSDynamicArray * dynamicArray)
{
	while(eaDSDynamicArrayGetCount(dynamicArray))
	{
		dynamicArray->Info.dataClear(dynamicArray->Data[--dynamicArray->Count]);
	}

	dynamicArray->Capacity = 4;
}

void eaDSDynamicArrayClear(eaDSDynamicArray * dynamicArray)
{
	eaDSDynamicArrayReset(dynamicArray);

	if (dynamicArray->Data != NULL)
	{
		free(dynamicArray->Data);
	}
}

void eaDSDynamicArraySort(eaDSDynamicArray * dynamicArray)
{
	void * buf;
	size_t i, j, N = eaDSDynamicArrayGetCount(dynamicArray);

	for(i = 1; i < N; i++)
	{
		for(j = i; (0 < j) && (dynamicArray->Info.dataEqual(dynamicArray->Data[j - 1], dynamicArray->Data[j], dynamicArray->Info.SumSize) > 0); j--)
		{
			buf = dynamicArray->Data[j];
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
			dynamicArray->Data[j - 1] = buf;
		}
	}
}

size_t eaDSDynamicArrayGetCount(const eaDSDynamicArray * dynamicArray)
{
	return dynamicArray->Count;
}

size_t eaDSDynamicArrayGetCapacity(const eaDSDynamicArray * dynamicArray)
{
	return dynamicArray->Capacity;
}

int eaDSDynamicArrayAdd(eaDSDynamicArray * dynamicArray, const void * data)
{
	size_t i;

	if((dynamicArray->Count + 1) == dynamicArray->Capacity)
	{
		dynamicArray->Capacity = dynamicArray->Count + 4;
		void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if(NULL == tmp)
		{
			perror("Error: eaDSDynamicArrayAdd\n");
			return EXIT_FAILURE;
		}

		for (i = 0; i < dynamicArray->Count; i++)
		{
			tmp[i] = dynamicArray->Data[i];
		}

		free(dynamicArray->Data);
		dynamicArray->Data = tmp;
	}

	dynamicArray->Data[dynamicArray->Count] = dynamicArray->Info.dataCreat(dynamicArray->Info.SumSize);
	dynamicArray->Info.dataCopy(dynamicArray->Data[dynamicArray->Count], data, dynamicArray->Info.SumSize);
	dynamicArray->Count++;

	return EXIT_SUCCESS;
}

int eaDSDynamicArrayRemove(eaDSDynamicArray * dynamicArray, const void * data)
{
	size_t i, cnt = eaDSDynamicArrayGetCount(dynamicArray);

	for (i = 0; i < cnt; i++)
	{
		if (!dynamicArray->Info.dataEqual(data, dynamicArray->Data[i], dynamicArray->Info.SumSize))
		{
			dynamicArray->Info.dataClear(dynamicArray->Data[i]);
			dynamicArray->Data[i] = NULL;
			dynamicArray->Count--;

			for (; i < cnt; i++)
			{
				dynamicArray->Data[i] = dynamicArray->Data[i + 1];
			}

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int eaDSDynamicArrayRemoveAt(eaDSDynamicArray * dynamicArray, const size_t index)
{
	size_t j, cnt = eaDSDynamicArrayGetCount(dynamicArray);

	if((cnt != 0) && (index <= cnt) && (0 != index))
	{
		dynamicArray->Info.dataClear(dynamicArray->Data[index - 1]);
		for (j = index; j < cnt; j++)
		{
			dynamicArray->Data[j - 1] = dynamicArray->Data[j];
		}
		dynamicArray->Count--;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int eaDSDynamicArrayInsert(eaDSDynamicArray * dynamicArray, const void * data, const size_t index)
{
	size_t j, cnt = eaDSDynamicArrayGetCount(dynamicArray);

	if((cnt != 0) && (index <= cnt) && (0 != index))
	{
		if((dynamicArray->Count + 1) == dynamicArray->Capacity)
		{
			dynamicArray->Capacity = dynamicArray->Count + 4;
			void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				perror("Error: eaDSDynamicArrayInsert\n");
				return EXIT_FAILURE;
			}

			for (j = 0; j < dynamicArray->Count; j++)
			{
				tmp[j] = dynamicArray->Data[j];
			}

			free(dynamicArray->Data);
			dynamicArray->Data = tmp;
		}

		for (j = cnt; j >= index - 1; j--)
		{
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
		}

		dynamicArray->Data[index - 1] = dynamicArray->Info.dataCreat(dynamicArray->Info.SumSize);
		dynamicArray->Info.dataCopy(dynamicArray->Data[index - 1], data, dynamicArray->Info.SumSize);
		dynamicArray->Count++;
	}
	return EXIT_SUCCESS;
}

int eaDSDynamicArrayGetFrom(const eaDSDynamicArray * dynamicArray, void * data, const size_t index)
{
	if((0 != index) && (index <= eaDSDynamicArrayGetCount(dynamicArray)))
	{
		dynamicArray->Info.dataCopy(data, dynamicArray->Data[index - 1], dynamicArray->Info.SumSize);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}


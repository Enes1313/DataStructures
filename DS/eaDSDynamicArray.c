#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eaDSDynamicArray.h"

#define DEFAULT_EXP_FACTOR 2
#define DEFAULT_STARTING_CAPACITY 4

struct _eaDSDynamicArray{
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

static int compareAddress(const void * a1, const void * a2)
{
	return !(a1 == a2);
}

eaDSDynamicArray eaDSDynamicArrayInit(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *))
{
	return eaDSDynamicArrayInitWithDetails(dataCreateAndCopy, dataCompare, dataClear, DEFAULT_EXP_FACTOR, DEFAULT_STARTING_CAPACITY);
}

eaDSDynamicArray eaDSDynamicArrayInitWithDetails(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *), unsigned short expFactor, unsigned short startingCapacity)
{
	eaDSDynamicArray dynamicArray = NULL;

	dynamicArray = (eaDSDynamicArray) malloc(sizeof(struct _eaDSDynamicArray));

	if (NULL == dynamicArray)
	{
		perror(NULL);
	}
	else
	{
		dynamicArray->StartingCapacity = startingCapacity ? startingCapacity : DEFAULT_STARTING_CAPACITY;
		dynamicArray->Data = (void **) malloc(dynamicArray->StartingCapacity * sizeof(void *));

		if (NULL == dynamicArray->Data)
		{
			perror(NULL);
			free(dynamicArray);
			dynamicArray = NULL;
		}
		else
		{
			dynamicArray->Count = 0;
			dynamicArray->Capacity = dynamicArray->StartingCapacity;
			dynamicArray->ExpFactor = (expFactor < 2) ? DEFAULT_EXP_FACTOR : expFactor;
			dynamicArray->dataCreateAndCopy = (dataCreateAndCopy == NULL) ? copyAddress : dataCreateAndCopy;
			dynamicArray->dataCompare = (dataCompare == NULL) ? compareAddress : dataCompare;
			dynamicArray->dataClear = (dataClear == NULL) ? free : dataClear;
		}
	}

	return dynamicArray;
}

int eaDSDynamicArrayReset(eaDSDynamicArray dynamicArray)
{
	if (NULL == dynamicArray->Data)
	{
		dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if (NULL == dynamicArray->Data)
		{
			perror(NULL);

			return EXIT_FAILURE;
		}
	}
	else
	{
		while(dynamicArray->Count)
		{
			dynamicArray->dataClear(dynamicArray->Data[--dynamicArray->Count]);
		}

		if (dynamicArray->StartingCapacity < dynamicArray->Capacity)
		{
			free(dynamicArray->Data);
			dynamicArray->Data = (void **) malloc(dynamicArray->StartingCapacity * sizeof(void *));

			if (NULL == dynamicArray->Data)
			{
				perror(NULL);

				return EXIT_FAILURE;
			}

			dynamicArray->Capacity = dynamicArray->StartingCapacity;
		}
	}

	return EXIT_SUCCESS;
}

void eaDSDynamicArrayClear(eaDSDynamicArray dynamicArray)
{
	if (NULL != dynamicArray->Data)
	{
		while(dynamicArray->Count)
		{
			dynamicArray->dataClear(dynamicArray->Data[--dynamicArray->Count]);
		}

		free(dynamicArray->Data);
	}

	free(dynamicArray);
}

void eaDSDynamicArraySort(eaDSDynamicArray dynamicArray)
{
	void * buf;
	size_t i, j, N;

	N = dynamicArray->Count;

	for(i = 1; i < N; i++)
	{
		for(j = i; (0 < j) && (dynamicArray->dataCompare(dynamicArray->Data[j - 1], dynamicArray->Data[j]) > 0); j--)
		{
			buf = dynamicArray->Data[j];
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
			dynamicArray->Data[j - 1] = buf;
		}
	}
}

size_t eaDSDynamicArrayGetCount(const eaDSDynamicArray dynamicArray)
{
	return dynamicArray->Count;
}

size_t eaDSDynamicArrayGetCapacity(const eaDSDynamicArray dynamicArray)
{
	return dynamicArray->Capacity;
}

int eaDSDynamicArrayAdd(eaDSDynamicArray dynamicArray, const void * data)
{
	void * item;

	if (NULL == (item = dynamicArray->dataCreateAndCopy(data)))
	{
		perror(NULL);

		return EXIT_FAILURE;
	}

	if (dynamicArray->Count == dynamicArray->Capacity)
	{
		size_t i;
		void ** tmp;

		dynamicArray->Capacity *= dynamicArray->ExpFactor;
		tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if (NULL == tmp)
		{
			perror(NULL);
			dynamicArray->Capacity /= dynamicArray->ExpFactor;

			return EXIT_FAILURE;
		}

		for (i = 0; i < dynamicArray->Count; i++)
		{
			tmp[i] = dynamicArray->Data[i];
		}

		free(dynamicArray->Data);
		dynamicArray->Data = tmp;
	}

	dynamicArray->Data[dynamicArray->Count] = item;
	dynamicArray->Count++;

	return EXIT_SUCCESS;
}

int eaDSDynamicArrayInsert(eaDSDynamicArray dynamicArray, const void * data, const size_t index)
{
	size_t j, cnt;

	cnt = dynamicArray->Count;

	if(index <= cnt)
	{
		void * item;

		if (NULL == (item = dynamicArray->dataCreateAndCopy(data)))
		{
			perror(NULL);

			return EXIT_FAILURE;
		}

		if(dynamicArray->Count == dynamicArray->Capacity)
		{
			void ** tmp;

			dynamicArray->Capacity *= dynamicArray->ExpFactor;
			tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				perror(NULL);
				dynamicArray->Capacity /= dynamicArray->ExpFactor;

				return EXIT_FAILURE;
			}

			for (j = 0; j < dynamicArray->Count; j++)
			{
				tmp[j] = dynamicArray->Data[j];
			}

			free(dynamicArray->Data);
			dynamicArray->Data = tmp;
		}

		if (cnt)
		{
			for (j = cnt - 1; j >= index; j--)
			{
				dynamicArray->Data[j + 1] = dynamicArray->Data[j];

				if (!j)
				{
					break;
				}
			}
		}

		dynamicArray->Data[index] = item;
		dynamicArray->Count++;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

void eaDSDynamicArrayRemove(eaDSDynamicArray dynamicArray, const void * data)
{
	size_t i, cnt;

	cnt = dynamicArray->Count;

	for (i = 0; i < cnt; i++)
	{
		if (!dynamicArray->dataCompare(data, dynamicArray->Data[i]))
		{
			dynamicArray->Count--;
			dynamicArray->dataClear(dynamicArray->Data[i]);

			for (; i < (cnt - 1); i++)
			{
				dynamicArray->Data[i] = dynamicArray->Data[i + 1];
			}

			break;
		}
	}
}

void eaDSDynamicArrayRemoveAll(eaDSDynamicArray dynamicArray, const void * data)
{
	size_t i, cnt;

	cnt = dynamicArray->Count;

	for (i = 0; i < cnt; i++)
	{
		if (!dynamicArray->dataCompare(data, dynamicArray->Data[i]))
		{
			dynamicArray->Count--;
			dynamicArray->dataClear(dynamicArray->Data[i]);

			if (i == (cnt - 1))
			{
				break;
			}

			dynamicArray->Data[i] = dynamicArray->Data[i + 1];
			i--;
		}
	}
}

void eaDSDynamicArrayRemoveAt(eaDSDynamicArray dynamicArray, const size_t index)
{
	size_t j, cnt;

	cnt = dynamicArray->Count;

	if(cnt && (index < cnt))
	{
		dynamicArray->dataClear(dynamicArray->Data[index]);

		for (j = index; j < cnt - 1; j++)
		{
			dynamicArray->Data[j] = dynamicArray->Data[j + 1];
		}

		dynamicArray->Count--;
	}
}

void eaDSDynamicArrayRemoveAtCopyLastItem(eaDSDynamicArray dynamicArray, const size_t index)
{
	size_t cnt;

	cnt = dynamicArray->Count;

	if(cnt && (index < cnt))
	{
		dynamicArray->dataClear(dynamicArray->Data[index]);

		if (cnt - 1)
		{
			dynamicArray->Data[index] = dynamicArray->Data[cnt - 1];
		}

		dynamicArray->Count--;
	}
}

void * eaDSDynamicArrayGetFrom(const eaDSDynamicArray dynamicArray, const size_t index)
{
	void * data;

	data = NULL;

	if(index < dynamicArray->Count)
	{
		if (NULL == (data = dynamicArray->dataCreateAndCopy(dynamicArray->Data[index])))
		{
			perror(NULL);
		}
	}

	return data;
}

void * eaDSDynamicArrayGetAddressFrom(const eaDSDynamicArray dynamicArray, const size_t index)
{
	if(index < dynamicArray->Count)
	{
		return dynamicArray->Data[index];
	}

	return NULL;
}

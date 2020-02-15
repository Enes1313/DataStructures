#include <stdlib.h>
#include <string.h>
#include "eaDSDynamicArray.h"

#define DEFAULT_EXP_FACTOR 2
#define DEFAULT_STARTING_CAPACITY 4

struct _eaDSDynamicArray{
	void ** Data;
	size_t Count, Capacity;
	unsigned short ExpFactor, StartingCapacity;
	eaDSInfosForData Infos;
};

eaDSDynamicArray eaDSDynamicArrayInit(eaDSInfosForData * infos)
{
	return eaDSDynamicArrayInitWithDetails(infos, DEFAULT_EXP_FACTOR, DEFAULT_STARTING_CAPACITY);
}

eaDSDynamicArray eaDSDynamicArrayInitWithDetails(eaDSInfosForData * infos, unsigned short expFactor, unsigned short startingCapacity)
{
	eaDSDynamicArray dynamicArray;

	dynamicArray = (eaDSDynamicArray) malloc(sizeof(struct _eaDSDynamicArray));

	if (NULL == dynamicArray)
	{
		perror(__func__);
	}
	else
	{
		dynamicArray->StartingCapacity = startingCapacity ? startingCapacity : DEFAULT_STARTING_CAPACITY;
		dynamicArray->Data = (void **) malloc(dynamicArray->StartingCapacity * sizeof(void *));

		if (NULL == dynamicArray->Data)
		{
			perror(__func__);
			free(dynamicArray);
			dynamicArray = NULL;
		}
		else
		{
			dynamicArray->Count = 0;
			dynamicArray->Capacity = dynamicArray->StartingCapacity;
			dynamicArray->ExpFactor = (expFactor < 2) ? DEFAULT_EXP_FACTOR : expFactor;

			if (NULL == infos)
			{
				dynamicArray->Infos = (eaDSInfosForData){sizeof(int), free, malloc, memcpy, memcmp};
			}
			else
			{
				dynamicArray->Infos = *infos;
			}
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
			perror(__func__);

			return EXIT_FAILURE;
		}
	}
	else
	{
		while(dynamicArray->Count)
		{
			dynamicArray->Infos.dataClear(dynamicArray->Data[--dynamicArray->Count]);
		}

		if (dynamicArray->StartingCapacity < dynamicArray->Capacity)
		{
			free(dynamicArray->Data);
			dynamicArray->Data = (void **) malloc(dynamicArray->StartingCapacity * sizeof(void *));

			if (NULL == dynamicArray->Data)
			{
				perror(__func__);

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
			dynamicArray->Infos.dataClear(dynamicArray->Data[--dynamicArray->Count]);
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
		for(j = i; (0 < j) && (dynamicArray->Infos.dataEqual(dynamicArray->Data[j - 1], dynamicArray->Data[j], dynamicArray->Infos.SumSize) > 0); j--)
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
	if (dynamicArray->Count == dynamicArray->Capacity)
	{
		size_t i;
		void ** tmp;

		dynamicArray->Capacity *= dynamicArray->ExpFactor;
		tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if (NULL == tmp)
		{
			perror(__func__);
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

	dynamicArray->Data[dynamicArray->Count] = dynamicArray->Infos.dataCreate(dynamicArray->Infos.SumSize);

	if (NULL == dynamicArray->Data[dynamicArray->Count])
	{
		perror(__func__);

		return EXIT_FAILURE;
	}

	dynamicArray->Infos.dataCopy(dynamicArray->Data[dynamicArray->Count], data, dynamicArray->Infos.SumSize);
	dynamicArray->Count++;

	return EXIT_SUCCESS;
}

int eaDSDynamicArrayInsert(eaDSDynamicArray dynamicArray, const void * data, const size_t index)
{
	size_t j, cnt;

	cnt = dynamicArray->Count;

	if(index <= cnt)
	{
		void * add;

		if(dynamicArray->Count == dynamicArray->Capacity)
		{
			void ** tmp;

			dynamicArray->Capacity *= dynamicArray->ExpFactor;
			tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				perror(__func__);
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

		if (NULL == (add = dynamicArray->Infos.dataCreate(dynamicArray->Infos.SumSize)))
		{
			perror(__func__);

			return EXIT_FAILURE;
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

		dynamicArray->Data[index] = add;
		dynamicArray->Infos.dataCopy(dynamicArray->Data[index], data, dynamicArray->Infos.SumSize);
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
		if (!dynamicArray->Infos.dataEqual(data, dynamicArray->Data[i], dynamicArray->Infos.SumSize))
		{
			dynamicArray->Count--;
			dynamicArray->Infos.dataClear(dynamicArray->Data[i]);

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
		if (!dynamicArray->Infos.dataEqual(data, dynamicArray->Data[i], dynamicArray->Infos.SumSize))
		{
			dynamicArray->Count--;
			dynamicArray->Infos.dataClear(dynamicArray->Data[i]);

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
		dynamicArray->Infos.dataClear(dynamicArray->Data[index]);

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
		dynamicArray->Infos.dataClear(dynamicArray->Data[index]);

		if (cnt - 1)
		{
			dynamicArray->Data[index] = dynamicArray->Data[cnt - 1];
		}

		dynamicArray->Count--;
	}
}

int eaDSDynamicArrayGetFrom(const eaDSDynamicArray dynamicArray, void * data, const size_t index)
{
	if(index < dynamicArray->Count)
	{
		dynamicArray->Infos.dataCopy(data, dynamicArray->Data[index], dynamicArray->Infos.SumSize);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

void * eaDSDynamicArrayGetAddressFrom(const eaDSDynamicArray dynamicArray, const size_t index)
{
	if(index < dynamicArray->Count)
	{
		return dynamicArray->Data[index];
	}

	return NULL;
}

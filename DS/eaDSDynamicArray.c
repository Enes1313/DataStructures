#include <stdlib.h>
#include <string.h>
#include "eaDSDynamicArray.h"

struct _eaDSDynamicArray{
	void ** Data;
	size_t Count, Capacity;
	eaDSDataInfo Info;
};

eaDSDynamicArray eaDSDynamicArrayInit(eaDSDataInfo * info)
{
	eaDSDynamicArray dynamicArray;

	dynamicArray = (eaDSDynamicArray) malloc(sizeof(struct _eaDSDynamicArray));

	if (NULL == dynamicArray)
	{
		EA_ERROR(__func__);
	}
	else
	{
		dynamicArray->Count = 0;
		dynamicArray->Capacity = 4;
		dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if (NULL == dynamicArray->Data)
		{
			EA_ERROR(__func__);
		}

		if (NULL == info)
		{
			dynamicArray->Info = (eaDSDataInfo){sizeof(int), free, malloc, memcpy, memcmp};
		}
		else
		{
			dynamicArray->Info = *info;
		}
	}

	return dynamicArray;
}

void eaDSDynamicArrayReset(eaDSDynamicArray dynamicArray)
{
	if (NULL != dynamicArray->Data)
	{
		while(dynamicArray->Count)
		{
			dynamicArray->Info.dataClear(dynamicArray->Data[--dynamicArray->Count]);
		}

		if (4 < dynamicArray->Capacity)
		{
			free(dynamicArray->Data);

			dynamicArray->Capacity = 4;
			dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if (NULL == dynamicArray->Data)
			{
				EA_ERROR(__func__);
			}
		}
	}
	else
	{
		EA_INFO("In %s, context of DA is NULL\n", __func__);
		dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if (NULL == dynamicArray->Data)
		{
			EA_ERROR(__func__);
		}
	}
}

void eaDSDynamicArrayClear(eaDSDynamicArray dynamicArray)
{
	if (NULL != dynamicArray->Data)
	{
		while(dynamicArray->Count)
		{
			dynamicArray->Info.dataClear(dynamicArray->Data[--dynamicArray->Count]);
		}
		free(dynamicArray->Data);
	}
	else
	{
		EA_INFO("In %s, context of DA is NULL\n", __func__);
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
		for(j = i; (0 < j) && (dynamicArray->Info.dataEqual(dynamicArray->Data[j - 1], dynamicArray->Data[j], dynamicArray->Info.SumSize) > 0); j--)
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
	size_t i;

	if (NULL == dynamicArray->Data)
	{
		EA_INFO("In %s, context of DA is NULL\n", __func__);

		return EXIT_FAILURE;
	}

	if(dynamicArray->Count == dynamicArray->Capacity)
	{
		void ** tmp;

		dynamicArray->Capacity += 4;
		tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if(NULL == tmp)
		{
			EA_ERROR(__func__);
			dynamicArray->Capacity -= 4;

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

	if (NULL == dynamicArray->Data[dynamicArray->Count])
	{
		EA_ERROR(__func__);

		return EXIT_FAILURE;
	}

	dynamicArray->Info.dataCopy(dynamicArray->Data[dynamicArray->Count], data, dynamicArray->Info.SumSize);
	dynamicArray->Count++;

	return EXIT_SUCCESS;
}

void eaDSDynamicArrayRemove(eaDSDynamicArray dynamicArray, const void * data)
{
	size_t i, cnt;

	cnt = dynamicArray->Count;

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
		}
	}
}

void eaDSDynamicArrayRemoveAt(eaDSDynamicArray dynamicArray, const size_t index)
{
	size_t j, cnt;

	cnt = dynamicArray->Count;

	if(cnt && (index < cnt))
	{
		dynamicArray->Info.dataClear(dynamicArray->Data[index]);

		for (j = index; j < cnt - 1; j++)
		{
			dynamicArray->Data[j] = dynamicArray->Data[j + 1];
		}

		dynamicArray->Count--;
	}
}

int eaDSDynamicArrayInsert(eaDSDynamicArray dynamicArray, const void * data, const size_t index)
{
	size_t j, cnt;

	if (NULL == dynamicArray->Data)
	{
		EA_INFO("In %s, context of DA is NULL\n", __func__);

		return EXIT_FAILURE;
	}

	cnt = dynamicArray->Count;

	if(index <= cnt)
	{
		void * add;

		if(dynamicArray->Count == dynamicArray->Capacity)
		{
			void ** tmp;

			dynamicArray->Capacity += 4;
			tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				EA_ERROR(__func__);
				dynamicArray->Capacity -= 4;

				return EXIT_FAILURE;
			}

			for (j = 0; j < dynamicArray->Count; j++)
			{
				tmp[j] = dynamicArray->Data[j];
			}

			free(dynamicArray->Data);
			dynamicArray->Data = tmp;
		}

		if (NULL == (add = dynamicArray->Info.dataCreat(dynamicArray->Info.SumSize)))
		{
			EA_ERROR(__func__);

			return EXIT_FAILURE;
		}

		if (cnt)
		{
			for (j = cnt - 1; j >= index; j--)
			{
				dynamicArray->Data[j + 1] = dynamicArray->Data[j];
				if (!j) break;
			}
		}

		dynamicArray->Data[index] = add;
		dynamicArray->Info.dataCopy(dynamicArray->Data[index], data, dynamicArray->Info.SumSize);
		dynamicArray->Count++;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int eaDSDynamicArrayGetFrom(const eaDSDynamicArray dynamicArray, void * data, const size_t index)
{
	if(index < dynamicArray->Count)
	{
		dynamicArray->Info.dataCopy(data, dynamicArray->Data[index], dynamicArray->Info.SumSize);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

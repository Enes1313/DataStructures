/********************************************************************************
* DESCRIPTION : It is test program for data structures.
* NOTES       : None
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eaDSCircularBuffer.h"
#include "eaDSDynamicArray.h"
#include "eaDSLinkedList.h"
#include "eaDSQueue.h"
#include "eaDSStack.h"

void testCircularBuffer();
void testDynamicArray();
void testLinkedList();
void testStack();
void testQueue();

int main(void)
{
	srand((unsigned int)time(NULL));

	testCircularBuffer();
	testDynamicArray();
	testLinkedList();
	testQueue();
	testStack();

	return EXIT_SUCCESS;
}

void testCircularBuffer()
{
	size_t len = 0;
	eaDSCircularBuffer circularBuffer;
	char data[] = {"{ \"Who\" : \"Enes\",{ \"Who\" : \"Enes\", \"Birth\" : 1994 }drgtfhyjg{ \"Who\" : \"Reis\", \"Birth\" : 8888 }"};

	puts("********************************************");
	puts("Circular Buffer");
	puts("********************************************");

	if (NULL == (circularBuffer = eaDSCircularBufferInit(sizeof(char), malloc, memcpy, memcmp, free)))
	{
		puts("circularBuffer olusmadi!");
		return;
	}

	while (EXIT_SUCCESS == eaDSCircularBufferAdd(circularBuffer, data, strlen(data)))
	{
		puts("circularBuffer'a veri eklendi!");
	}

	memset(data, 0, sizeof(data));

	if (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "{", 1, &len))
	{
		eaDSCircularBufferMoveHead(circularBuffer, len);

		if (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "}", 1, &len))
		{
			if (EXIT_SUCCESS == eaDSCircularBufferGet(circularBuffer, data, len + 1))
			{
				printf("circularBuffer'dan cekilen veri : %s\n", data);
			}
		}
		else
		{
			puts("Bo");
		}
	}

	if (EXIT_SUCCESS == eaDSCircularBufferAdd(circularBuffer, data, strlen(data)))
	{
		puts("circularBuffer'a veri eklendi!");
	}

	if (EXIT_SUCCESS == eaDSCircularBufferAdd(circularBuffer, data, strlen(data)))
	{
		puts("circularBuffer'a veri eklendi!");
	}

	if (EXIT_SUCCESS == eaDSCircularBufferAdd(circularBuffer, data, strlen(data)))
	{
		puts("circularBuffer'a veri eklendi!");
	}

	memset(data, 0, sizeof(data));

	if (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "{", 1, &len))
	{
		eaDSCircularBufferMoveHead(circularBuffer, len);

		if (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "}", 1, &len))
		{
			if (EXIT_SUCCESS == eaDSCircularBufferGet(circularBuffer, data, len + 1))
			{
				printf("circularBuffer'dan cekilen veri : %s\n", data);
			}
		}
		else
		{
			puts("Bo");
		}
	}

	if (EXIT_SUCCESS != eaDSCircularBufferAdd(circularBuffer, "dff", 3))
	{
		puts("circularBuffer'a veri eklenemedi!");
	}
	{
		memset(data, 0, sizeof(data));

		if (EXIT_SUCCESS == eaDSCircularBufferGet(circularBuffer, data, 1))
		{
			printf("circularBuffer'dan cekilen veri : %s\n", data);
			memset(data, 0, 1);
		}

		while (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "{", 1, &len))
		{
			eaDSCircularBufferMoveHead(circularBuffer, len);

			if (EXIT_SUCCESS == eaDSCircularBufferGetWhereIsIt(circularBuffer, "}", 1, &len))
			{
				if (EXIT_SUCCESS == eaDSCircularBufferGet(circularBuffer, data, len + 1))
				{
					printf("circularBuffer'dan cekilen veri : %s\n", data);
					memset(data, 0, sizeof(data));
				}
			}
			else
			{
				puts("Bo");
				break;
			}
		}
	}

	eaDSCircularBufferClear(circularBuffer);

	puts("********************************************");
	puts("Circular Buffer");
	puts("********************************************");
}

void * intCreateAndCopy(const void * data)
{
	void * a = malloc(sizeof(int));
	return memcpy(a, data, sizeof(int));
}

int intCompare(const void * a1, const void * a2)
{
	return memcmp(a1, a2, sizeof(int));
}

void testDynamicArray()
{
	size_t i, x;
	eaDSDynamicArray dynamicArray;

	puts("********************************************");
	puts("Dinamik Array");
	puts("********************************************");

	if (NULL == (dynamicArray = eaDSDynamicArrayInit(intCreateAndCopy, intCompare, free)))
	{
		puts("dynamicArray olusmadi!");
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = (unsigned int) rand() % 50;

		if(EXIT_SUCCESS == eaDSDynamicArrayAdd(dynamicArray, &x))
		{
			printf("DynamicArray'e eleman eklendi : %d \n", (int)x);
		}
		else
		{
			puts("DynamicArray'e eleman eklenemedi!");
		}
	}

	x = 50;

	if(EXIT_SUCCESS == eaDSDynamicArrayInsert(dynamicArray, &x, 2))
	{
		printf("DynamicArray'in 3. sirasina eleman eklendi : %d\n", (int)x);
	}
	else
	{
		puts("DynamicArray'in 3. sirasina eleman eklenemedi!");
	}
	
	x = 51;
/*
	if(EXIT_SUCCESS == eaDSDynamicArrayInsert(dynamicArray, &x, 6))
	{
		printf("DynamicArray'in 6. sirasina eleman eklendi : %d\n", (int)x);
	}
	else
	{
		puts("DynamicArray'in 6. sirasina eleman eklenemedi!");
	}*/

	x = 10;

	printf("DynamicArray'den siliniyor : %d\n", (int)x);
	eaDSDynamicArrayRemove(dynamicArray, &x);

	printf("DynamicArray'den 2. eleman atiliyor!\n");
	eaDSDynamicArrayRemoveAt(dynamicArray, 1);

	for(i = 0; i < eaDSDynamicArrayGetCount(dynamicArray); i++)
	{
		void * data = eaDSDynamicArrayGetFrom(dynamicArray, i);

		if(NULL != data)
		{
			printf("DynamicArray'den %d. eleman alindi : %d\n", (int)i + 1, *(int *)data);
			free(data);
		}
		else
		{
			printf("DynamicArray'den %d. eleman alma basarisiz\n", (int)i + 1);
		}
	}

	printf("DynamicArray siralaniyor...\n");
	eaDSDynamicArraySort(dynamicArray);

	for(i = 0; i < eaDSDynamicArrayGetCount(dynamicArray); i++)
	{
		void * data = eaDSDynamicArrayGetAddressFrom(dynamicArray, i);

		if(NULL != data)
		{
			printf("DynamicArray'den %d. eleman alindi : %d\n", (int)i + 1, *(int *)data);
		}
		else
		{
			printf("DynamicArray'den %d. eleman alma basarisiz\n", (int)i + 1);
		}
	}

	printf("DynamicArray eleman sayisi : %d.\n", (int)eaDSDynamicArrayGetCount(dynamicArray));

	printf("DynamicArray resetleniyor.\n");
	eaDSDynamicArrayReset(dynamicArray);

	printf("DynamicArray eleman sayisi : %d.\n", (int)eaDSDynamicArrayGetCount(dynamicArray));

	x = (unsigned int) rand() % 50;

	if(EXIT_SUCCESS == eaDSDynamicArrayAdd(dynamicArray, &x))
	{
		printf("DynamicArray'e eleman eklendi : %d\n", (int)x);
	}
	else
	{
		puts("DynamicArray'e eleman eklenemedi!");
	}

	printf("DynamicArray eleman sayisi : %d.\n", (int)eaDSDynamicArrayGetCount(dynamicArray));

	printf("DynamicArray siliniyor.\n");
	eaDSDynamicArrayClear(dynamicArray);

	puts("********************************************");
	puts("Dinamik Array");
	puts("********************************************");
}

void testLinkedList()
{
	size_t i, x;
	eaDSLinkedList linkedList;

	puts("********************************************");
	puts("Linked List");
	puts("********************************************");

	if (NULL == (linkedList = eaDSLinkedListInit(intCreateAndCopy, intCompare, free)))
	{
		puts("linkedList olusmadi!");
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = (unsigned int) rand() % 50;

		if(EXIT_SUCCESS == eaDSLinkedListAdd(linkedList, &x))
		{
			printf("LinkedList'e eleman eklendi : %d \n", (int)x);
		}
		else
		{
			puts("LinkedList'e eleman eklenemedi!");
		}
	}

	x = 10;

	printf("LinkedList'den siliniyor : %d\n", (int)x);
	eaDSLinkedListRemove(linkedList, &x);

	printf("LinkedList'den 12. eleman atiliyor!\n");
	eaDSLinkedListRemoveAt(linkedList, 11);

	for(i = 0; ; i++)
	{
		void * data = eaDSLinkedListGetFrom(linkedList, i);

		if (NULL != data)
		{
			printf("LinkedList'den %d. eleman alindi : %d\n", (int)i + 1, *(int *)data);
			free(data);
		}
		else
		{
			break;
		}
	}
	/*
	printf("LinkedList siralaniyor...\n");
	eaDSLinkedListSort(linkedList);

	for(i = 0; EXIT_SUCCESS == eaDSLinkedListGetFrom(linkedList, &x, i); i++)
	{
		printf("LinkedList'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
	}
	*/

	printf("LinkedList resetleniyor.\n");
	eaDSLinkedListReset(linkedList);

	x = (unsigned int) rand() % 50;

	if(EXIT_SUCCESS == eaDSLinkedListAdd(linkedList, &x))
	{
		printf("LinkedList'e eleman eklendi : %d\n", (int)x);
	}
	else
	{
		puts("LinkedList'e eleman eklenemedi!");
	}

	printf("LinkedList siliniyor.\n");
	eaDSLinkedListClear(linkedList);

	puts("********************************************");
	puts("Linked List");
	puts("********************************************");
}

void testStack()
{
	size_t i, x;
	eaDSStack stack;

	puts("********************************************");
	puts("Stack");
	puts("********************************************");

	if (NULL == (stack = eaDSStackInit(intCreateAndCopy, free)))
	{
		puts("stack olusmadi!");
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = (unsigned int) rand() % 50;

		if(EXIT_SUCCESS == eaDSStackPush(stack, &x))
		{
			printf("Stack'e eleman eklendi : %d \n", (int)x);
		}
		else
		{
			puts("Stack'e eleman eklenemedi!");
		}
	}

	printf("Stack eleman sayisi : %d.\n", (int)eaDSStackGetCount(stack));

	for(i = 0; eaDSStackGetCount(stack); i++)
	{
		void * data = eaDSStackPop(stack);
		if(NULL != data)
		{
			printf("Stack'den %d. eleman alindi : %d\n", (int)i + 1, *(int *)data);
			free(data);
		}
		else
		{
			printf("Stack'den %d. eleman alma basarisiz\n", (int)i + 1);
		}
	}

	printf("Stack eleman sayisi : %d.\n", (int)eaDSStackGetCount(stack));

	printf("Stack resetleniyor.\n");
	eaDSStackReset(stack);

	printf("Stack eleman sayisi : %d.\n", (int)eaDSStackGetCount(stack));

	x = (unsigned int) rand() % 50;

	if(EXIT_SUCCESS == eaDSStackPush(stack, &x))
	{
		printf("Stack'e eleman eklendi : %d\n", (int)x);
	}
	else
	{
		puts("Stack'e eleman eklenemedi!");
	}

	printf("Stack eleman sayisi : %d.\n", (int)eaDSStackGetCount(stack));

	printf("Stack siliniyor.\n");
	eaDSStackClear(stack);

	puts("********************************************");
	puts("Stack");
	puts("********************************************");
}

void testQueue()
{
	size_t i, x;
	eaDSQueue queue = NULL;

	if (NULL == (queue = eaDSQueueInit(intCreateAndCopy, free)))
	{
		puts("queue olusmadi!");
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = (unsigned int) rand() % 50;

		if(EXIT_SUCCESS == eaDSQueueEnqueue(queue, &x))
		{
			printf("Queue'e eleman eklendi : %d \n", (int)x);
		}
		else
		{
			puts("Queue'e eleman eklenemedi!");
		}
	}

	for(i = 0; !eaDSQueueIsEmpty(queue); i++)
	{
		void * data = eaDSQueueDequeue(queue);

		if(NULL != data)
		{
			printf("Queue'den %d. eleman alindi : %d\n", (int)i + 1, *(int *)data);
			free(data);
		}
		else
		{
			printf("Queue'den %d. eleman alma basarisiz\n", (int)i + 1);
		}
	}

	printf("Queue siliniyor.\n");
	eaDSQueueClear(queue);

	puts("********************************************");
	puts("Queue");
	puts("********************************************");
}

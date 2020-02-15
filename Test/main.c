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

#include "eaDSDynamicArray.h"
#include "eaDSLinkedList.h"
#include "eaDSStack.h"
#include "eaDSQueue.h"
#include "eaDSTree.h"

void testDynamicArray();
void testLinkedList();
void testStack();
void testQueue();
void testTree();

int main(void)
{
	srand((unsigned int)time(NULL));

	testDynamicArray();
	testLinkedList();
	testStack();
	testQueue();
	/*
	 * testTree();
	 */

	return EXIT_SUCCESS;
}

void testDynamicArray()
{
	size_t i, x;
	eaDSDynamicArray dynamicArray;
	/*
	 * eaDSInfosForData infos = {sizeof(int), free, malloc, memcpy, memcmp};
	 */

	puts("********************************************");
	puts("Dinamik Array");
	puts("********************************************");

	if (NULL == (dynamicArray = eaDSDynamicArrayInit(NULL))) /* &infos */
	{
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = rand() % 50;

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
		if(EXIT_SUCCESS == eaDSDynamicArrayGetFrom(dynamicArray, &x, i))
		{
			printf("DynamicArray'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
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
		if(EXIT_SUCCESS == eaDSDynamicArrayGetFrom(dynamicArray, &x, i))
		{
			printf("DynamicArray'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
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

	x = rand() % 50;

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
	/*
	 * eaDSInfosForData infos = {sizeof(int), free, malloc, memcpy, memcmp};
	 */

	puts("********************************************");
	puts("Linked List");
	puts("********************************************");

	if (NULL == (linkedList = eaDSLinkedListInit(NULL))) /* &infos */
	{
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = rand() % 50;

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

	for(i = 0; EXIT_SUCCESS == eaDSLinkedListGetFrom(linkedList, &x, i); i++)
	{
		printf("LinkedList'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
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

	x = rand() % 50;

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
	/*
	 * eaDSInfosForData infos = {sizeof(int), free, malloc, memcpy, memcmp};
	 */

	puts("********************************************");
	puts("Stack");
	puts("********************************************");

	if (NULL == (stack = eaDSStackInit(NULL))) /* &infos */
	{
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = rand() % 50;

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
		if(EXIT_SUCCESS == eaDSStackPop(stack, &x))
		{
			printf("Stack'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
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

	x = rand() % 50;

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
	/*
	 * eaDSInfosForData infos = {sizeof(int), free, malloc, memcpy, memcmp };
	 */

	if (NULL == (queue = eaDSQueueInit(NULL))) /* &infos */
	{
		return;
	}

	for(i = 0; i < 13; i++)
	{
		x = rand() % 50;

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
		if(EXIT_SUCCESS == eaDSQueueDequeue(queue, &x))
		{
			printf("Queue'den %d. eleman alindi : %d\n", (int)i + 1, (int)x);
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

void testTree()
{
	eaDSTree tree;
	eaDSInfosForData infos = {sizeof(int), free, malloc, memcpy, memcmp};

	eaDSTreeInit(&tree, infos);
	/*
	 *
	 */
	eaDSTreeClear(&tree);
}


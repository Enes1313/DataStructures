/*
 ============================================================================
 Name        : main.c
 Author      : Enes AYDIN
 Version     :
 Copyright   : Copyright dediğin nedir ki gülüm?
 Description : Data Structures with C
 ============================================================================
 */

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
	//testDynamicArray();
	//testLinkedList();
	//testStack();
	testQueue();
	//testTree();
	getchar();
	return EXIT_SUCCESS;
}

void testDynamicArray()
{
	size_t i, x;
	eaDSDynamicArray dynamicArray;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	eaDSDynamicArrayInit(&dynamicArray, info);

	srand((unsigned int)time(NULL));

	for(i = 1; i < 8; i++)
	{
		printf("DynamicArray'e ekleniyor : %d sayisi eklendi\n", (int)(x = rand() % 50));
		eaDSDynamicArrayAdd(&dynamicArray, &x);
	}

	x = 50;
	eaDSDynamicArrayInsert(&dynamicArray, &x, 3);
	x = 51;
	eaDSDynamicArrayInsert(&dynamicArray, &x, 6);
	x = 50;
	eaDSDynamicArrayRemove(&dynamicArray, &x);

	eaDSDynamicArrayRemoveAt(&dynamicArray, 2);

	for(i = 1; i <= eaDSDynamicArrayGetCount(&dynamicArray); i++)
	{
		eaDSDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alınıyor : %d. eleman %d\n", (int)i, (int)x);
	}

	printf("DynamicArray sıralanıyor...\n");
	eaDSDynamicArraySort(&dynamicArray);

	for(i = 1; i <= eaDSDynamicArrayGetCount(&dynamicArray); i++)
	{
		eaDSDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alınıyor : %d. eleman %d\n", (int)i, (int)x);
	}

	eaDSDynamicArrayClear(&dynamicArray);
}

void testLinkedList()
{
	size_t i, x;
	eaDSLinkedList linkedList;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	eaDSLinkedListInit(&linkedList, info);

	srand((unsigned int)time(NULL));

	for(i = 1; i < 8; i++)
	{
		printf("LinkedList'e ekleniyor : %d sayisi eklendi\n", (int)(x = rand() % 50));
		eaDSLinkedListAdd(&linkedList, &x);
	}

	x = 50;
	eaDSLinkedListInsert(&linkedList, &x, 3);
	x = 51;
	eaDSLinkedListInsert(&linkedList, &x, 6);
	x = 50;
	eaDSLinkedListRemove(&linkedList, &x);

	eaDSLinkedListRemoveAt(&linkedList, 2);

	for(i = 1; !eaDSLinkedListGetFrom(&linkedList, &x, i); i++)
	{
		printf("LinkedList'den alınıyor : %d. eleman %d\n", (int)i, (int)x);
	}

	printf("LinkedList sıralanıyor...\n");
	eaDSLinkedListSort(&linkedList);

	for(i = 1; !eaDSLinkedListGetFrom(&linkedList, &x, i); i++)
	{
		printf("LinkedList'den alınıyor : %d. eleman %d\n", (int)i, (int)x);
	}

	eaDSLinkedListClear(&linkedList);
}

void testStack()
{
	size_t i, x;
	eaDSStack stack;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	eaDSStackInit(&stack, info);

	srand((unsigned int)time(NULL));

	for (i = 1; i < 8; i++)
	{
		printf("Stack'e ekleniyor : %d sayisi eklendi\n", (int)(x = rand() % 50));
		eaDSStackPush(&stack, &x);
	}

	while (eaDSStackGetCount(&stack))
	{
		eaDSStackPop(&stack, &x);
		printf("Stack'den alınıyor : %d. eleman %d\n", (int)--i, (int)x);
	}

	eaDSStackClear(&stack);
}

void testQueue()
{
	size_t i, x;
	eaDSQueue stack;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp };

	eaDSQueueInit(&stack, info);

	srand((unsigned int)time(NULL));

	for (i = 1; i < 8; i++)
	{
		printf("Queue'ye ekleniyor : %d sayisi eklendi\n", (int)(x = rand() % 50));
		eaDSQueueEnqueue(&stack, &x);
	}

	for (i = 1; !eaDSQueueIsEmpty(&stack); i++)
	{
		eaDSQueueDequeue(&stack, &x);
		printf("Queue'den alınıyor : %d. eleman %d\n", (int)i, (int)x);
	}

	eaDSStackClear(&stack);
}

void testTree()
{
	eaDSTree tree;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	eaDSTreeInit(&tree, info);
	/*
	 *
	 */
	eaDSTreeClear(&tree);
}


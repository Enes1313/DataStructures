/*
 ============================================================================
 Name        : DataStructures.c
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
#include "dataStructure.h"

void testDynamicArray();
void testLinkedList();
void testTree();

int main(void)
{
	//testDynamicArray();
	//testLinkedList();
	testTree();
	return EXIT_SUCCESS;
}

void testDynamicArray()
{
	int i, x;
	DynamicArray dynamicArray;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	dtDynamicArrayInit(&dynamicArray, info);

	srand(time(NULL));

	for(i = 1; i < 8; i++)
	{
		printf("DynamicArray'e ekleniyor : %d sayisi eklendi\n", x = rand() % 50);
		dtDynamicArrayAdd(&dynamicArray, &x);
	}

	x = 50;
	dtDynamicArrayInsert(&dynamicArray, &x, 3);
	x = 51;
	dtDynamicArrayInsert(&dynamicArray, &x, 6);
	x = 50;
	dtDynamicArrayRemove(&dynamicArray, &x);

	dtDynamicArrayRemoveAt(&dynamicArray, 2);

	for(i = 1; i <= dtDynamicArrayGetCount(&dynamicArray); i++)
	{
		dtDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alınıyor : %d. eleman %d\n", i, x);
	}

	printf("DynamicArray sıralanıyor...\n");
	dtDynamicArraySort(&dynamicArray);

	for(i = 1; i <= dtDynamicArrayGetCount(&dynamicArray); i++)
	{
		dtDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alınıyor : %d. eleman %d\n", i, x);
	}

	dtDynamicArrayClear(&dynamicArray);
}

void testLinkedList()
{
	int i, x;
	LinkedList linkedList;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	dtLinkedListInit(&linkedList, info);

	srand(time(NULL));

	for(i = 1; i < 8; i++)
	{
		printf("LinkedList'e ekleniyor : %d sayisi eklendi\n", x = rand() % 50);
		dtLinkedListAdd(&linkedList, &x);
	}

	x = 50;
	dtLinkedListInsert(&linkedList, &x, 3);
	x = 51;
	dtLinkedListInsert(&linkedList, &x, 6);
	x = 50;
	dtLinkedListRemove(&linkedList, &x);

	dtLinkedListRemoveAt(&linkedList, 2);

	for(i = 1; !dtLinkedListGetFrom(&linkedList, &x, i); i++)
	{
		printf("LinkedList'den alınıyor : %d. eleman %d\n", i, x);
	}

	printf("LinkedList sıralanıyor...\n");
	dtLinkedListSort(&linkedList);

	for(i = 1; !dtLinkedListGetFrom(&linkedList, &x, i); i++)
	{
		printf("LinkedList'den alınıyor : %d. eleman %d\n", i, x);
	}

	dtLinkedListClear(&linkedList);
}

void testTree()
{
	Tree tree;
	StructDataInfo info = {sizeof(int), free, malloc, memcpy, memcmp};

	dtTreeInit(&tree, info);
	/*
	 *
	 */
	dtTreeClear(&tree);
}


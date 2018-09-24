/*
 ============================================================================
 Name        : DataStructure4C.c
 Author      : Enes
 Version     :
 Copyright   : -
 Description : Data Structure for C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"

int main(void)
{
	int x = 13;
	DynamicArray dynamicArray;
	DataFuncsPointers funcs = {sizeof(int), free, malloc, memcpy, memcmp};

	dtDynamicArrayInit(&dynamicArray, funcs);

	dtDynamicArrayInsert(&dynamicArray, &x); x = 15;
	dtDynamicArrayInsert(&dynamicArray, &x); x = 45;
	dtDynamicArrayInsert(&dynamicArray, &x); x = 3;
	dtDynamicArrayInsert(&dynamicArray, &x);

	for(int i = 1; i < 5; i++)
	{
		dtDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("%d. eleman %d\n", i, x);
	}

	return EXIT_SUCCESS;
}

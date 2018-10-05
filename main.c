/*
 ============================================================================
 Name        : DataStructure4C.c
 Author      : Enes
 Version     : -
 Copyright   : -
 Description : Data Structure for C (Standard : C99)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dataStructure.h"

int main(void)
{
	int i, x;
	DynamicArray dynamicArray;
	DataFuncsPointers funcs = {sizeof(int), free, malloc, memcpy, memcmp};

	dtDynamicArrayInit(&dynamicArray, funcs);

	srand(time(NULL));

	for(i = 1; i < 8; i++)
	{
		printf("DynamicArray'e ekleniyor : %d sayisi eklendi\n", x = rand() % 50);
		dtDynamicArrayAdd(&dynamicArray, &x);
	}

	for(i = 1; i < 8; i++)
	{
		dtDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alýnýyor : %d. eleman %d\n", i, x);
	}

	printf("DynamicArray'sýralanýyor...\n");
	dtDynamicArraySort(&dynamicArray);

	for(i = 1; i < 8; i++)
	{
		dtDynamicArrayGetFrom(&dynamicArray, &x, i);
		printf("DynamicArray'den alýnýyor : %d. eleman %d\n", i, x);
	}

	dtDynamicArrayClear(&dynamicArray);

	return EXIT_SUCCESS;
}

/*
 * eaDSDynamicArray.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSDYNAMICARRAY_H
#define EADSDYNAMICARRAY_H

#include "eaDSData.h"
/*
 * DynamicArray
 */

typedef struct _eaDSDynamicArray{
	void ** Data;
	size_t Count, Capacity;
	StructDataInfo Info;
} eaDSDynamicArray;

void eaDSDynamicArrayInit(eaDSDynamicArray * dynamicArray, StructDataInfo Info);
void eaDSDynamicArrayReset(eaDSDynamicArray * dynamicArray);
void eaDSDynamicArrayClear(eaDSDynamicArray * dynamicArray);

void eaDSDynamicArraySort(eaDSDynamicArray * dynamicArray);

size_t eaDSDynamicArrayGetCount(const eaDSDynamicArray * dynamicArray);
size_t eaDSDynamicArrayGetCapacity(const eaDSDynamicArray * dynamicArray);

int eaDSDynamicArrayAdd(eaDSDynamicArray * dynamicArray, const void * data);
int eaDSDynamicArrayRemove(eaDSDynamicArray * dynamicArray, const void * data);
int eaDSDynamicArrayRemoveAt(eaDSDynamicArray * dynamicArray, const size_t index);
int eaDSDynamicArrayInsert(eaDSDynamicArray * dynamicArray, const void * data, const size_t index);
int eaDSDynamicArrayGetFrom(const eaDSDynamicArray * dynamicArray, void * data, const size_t index);

#endif /* EADSDYNAMICARRAY_H */

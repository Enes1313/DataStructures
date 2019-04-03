/*
 * eaDSStack.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSSTACK_H_
#define EADSSTACK_H_

#include "eaDSData.h"

/*
 * Stack
 */

typedef struct _eaDSStack {
	void ** Data;
	size_t Count, Capacity;
	StructDataInfo Info;
} eaDSStack;

void eaDSStackInit(eaDSStack * stack, StructDataInfo info);
void eaDSStackReset(eaDSStack * stack);
void eaDSStackClear(eaDSStack * stack);

size_t eaDSStackGetCount(const eaDSStack * stack);
size_t eaDSStackGetCapacity(const eaDSStack * stack);

int eaDSStackPop(eaDSStack * stack, void * data);
int eaDSStackPush(eaDSStack * stack, const void * data);
int eaDSStackPeekStack(const eaDSStack * stack, void * data);

#endif /* EADSSTACK_H_ */

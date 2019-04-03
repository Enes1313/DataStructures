/*
 * eaDSQueue.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSQUEUE_H_
#define EADSQUEUE_H_

#include "eaDSData.h"

/*
 * Queue
 */

typedef struct _ItemQue {
	void * Data;
	struct _ItemQue * Next;
} ItemQue;

typedef struct _eaDSQueue {
	ItemQue * Front;
	ItemQue * Rear;
	StructDataInfo Info;
} eaDSQueue;

void eaDSQueueInit(eaDSQueue * queue, StructDataInfo info);
void eaDSQueueReset(eaDSQueue * queue);
void eaDSQueueClear(eaDSQueue * queue);

int eaDSQueueIsEmpty(const eaDSQueue * queue);

int eaDSQueueDequeue(eaDSQueue * queue, void * data);
int eaDSQueueEnqueue(eaDSQueue * queue, const void * data);
int eaDSQueuePeekQueue(const eaDSQueue * queue, void * data);

#endif /* EADSQUEUE_H_ */

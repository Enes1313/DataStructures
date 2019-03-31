/*
 * eaDSQueue.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSQueue.h"

//Queue
/*
Queue createQueue()
{
	Queue q = (Queue) calloc(1, sizeof(struct queue));
	if(q == NULL)
	{
		perror("Error: createQueue");
		return NULL;
	}
	return q;
}
void clearQueue(Queue q)
{
	while(q->front != NULL)
	{
		Item tmp = q->front;
		q->front = tmp->next;
		tmp->data.clearData(&(tmp->data));
		free(tmp);
	}
	free(q);
}
int isEmptyQueue(Queue q)
{
	if(q->front == NULL)
		return 1;
	return 0;
}
int dequeue(Queue q, Data * pd)
{
	if(!isEmptyQueue(q))
	{
		Item tmp = q->front;
		q->front = tmp->next;
		tmp->data.copyData(pd, &(tmp->data));
		tmp->data.clearData(&(tmp->data));
		free(tmp);
		return 1;
	}
	return 0;
}
int enqueue(Queue q, Data * pd)
{
	Item tmp = (Item) malloc(sizeof(struct item));
	if(tmp == NULL)
	{
		perror("Error: enqueue");
		return 0;
	}
	tmp->data.creatData(&(tmp->data));
	tmp->data.copyData(&(tmp->data), pd);
	tmp->next = NULL;
	if(isEmptyQueue(q))
		q->front = tmp;
	else
		q->rear->next = tmp;
	q->rear = tmp;
	return 1;
}
int peekQueue(Queue q, Data * pd)
{
	if(!isEmptyQueue(q))
	{
		pd->copyData(pd, &(q->front->data));
		return 1;
	}
	return 0;
}
*/

/*
 * eaDSStack.c
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#include <stdio.h>
#include <stdlib.h>
#include "eaDSStack.h"

// Stack
/*
Stack createStack()
{
	Stack s = (Stack) calloc(1, sizeof(struct stack));
	if(s == NULL)
	{
		perror("Error: createStack");
		return NULL;
	}
	return s;
}
void clearStack(Stack s)
{
	while(!isEmptyStack(s))
	{
		Item tmp = s->top;
		s->top = tmp->next;
		tmp->data.clearData(&(tmp->data));
		free(tmp);
	}
	free(s);
}
int isEmptyStack(Stack s)
{
	if(s->top == NULL)
		return 1;
	return 0;
}
int pop(Stack s, Data * pd)
{
	if(!isEmptyStack(s))
	{
		Item tmp = s->top;
		s->top = tmp->next;
		tmp->data.copyData(pd, &(tmp->data));
		tmp->data.clearData(&(tmp->data));
		free(tmp);
		return 1;
	}
	return 0;
}
int push(Stack s, Data * pd)
{
	Item tmp = (Item) malloc(sizeof(struct item));
	if(tmp == NULL)
	{
		perror("Error: push");
		return 0;
	}
	tmp->data.creatData(&(tmp->data));
	tmp->data.copyData(&(tmp->data), pd);
	if(isEmptyStack(s))
		tmp->next = NULL;
	else
		tmp->next = s->top;
	s->top = tmp;
	return 1;
}
int peekStack(Stack s, Data * pd)
{
	if(!isEmptyStack(s))
	{
		pd->copyData(pd, &(s->top->data));
		return 1;
	}
	return 0;
}
*/

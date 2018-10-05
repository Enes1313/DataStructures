/*
 * DataStructure.c
 *
 *  Created on: 13 Aðu 2018
 *      Author: enes.aydin
 */
#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"

/*
 * DynamicArray
 */

void dtDynamicArrayInit(DynamicArray * dynamicArray, DataFuncsPointers funcs)
{
	dynamicArray->Funcs = funcs;
	dynamicArray->Count = 0;
	dynamicArray->Capacity = 4;
	dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

	if (dynamicArray->Data == NULL)
	{
		perror("Error: dtDynamicArrayInit\n");
	}
}

void dtDynamicArrayClear(DynamicArray * dynamicArray)
{
	while(dtDynamicArrayGetCount(dynamicArray))
	{
		dynamicArray->Funcs.dataClear(dynamicArray->Data[--dynamicArray->Count]);
	}
}

void dtDynamicArraySort(DynamicArray * dynamicArray)
{
	void * buf;
	size_t i, j, N = dtDynamicArrayGetCount(dynamicArray);

	for(i = 1; i < N; i++)
	{
		for(j = i; 0 < j && dynamicArray->Funcs.dataEqual(dynamicArray->Data[j - 1], dynamicArray->Data[j], dynamicArray->Funcs.SumSize) > 0; j--)
		{
			buf = dynamicArray->Data[j];
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
			dynamicArray->Data[j - 1] = buf;
		}
	}
}

size_t dtDynamicArrayGetCount(const DynamicArray * dynamicArray)
{
	return dynamicArray->Count;
}

size_t dtDynamicArrayGetCapacity(const DynamicArray * dynamicArray)
{
	return dynamicArray->Capacity;
}

int dtDynamicArrayGetFrom(DynamicArray * dynamicArray, void * data, const size_t i)
{
	if(dtDynamicArrayGetCount(dynamicArray))
	{
		if(0 != i && i <= dynamicArray->Count)
		{
			dynamicArray->Funcs.dataCopy(data, dynamicArray->Data[i - 1], dynamicArray->Funcs.SumSize);
			return 1;
		}
	}
	return 0;
}

void dtDynamicArrayRemove(DynamicArray * dynamicArray, const void * data)
{
	size_t i, cnt = dtDynamicArrayGetCount(dynamicArray);

	for (i = 0; i < cnt; i++)
	{
		if (!dynamicArray->Funcs.dataEqual(data, dynamicArray->Data[i], dynamicArray->Funcs.SumSize))
		{
			dynamicArray->Funcs.dataClear(dynamicArray->Data[i]);
			dynamicArray->Data[i] = NULL;
			break;
		}
	}

	for (; i < cnt; i++)
	{
		dynamicArray->Data[i] = dynamicArray->Data[i + 1];
	}

	dynamicArray->Count--;
}

void dtDynamicArrayRemoveAt(DynamicArray * dynamicArray, const size_t i)
{
	size_t j, cnt = dtDynamicArrayGetCount(dynamicArray);

	if(!cnt && i <= cnt && 0 != i)
	{
		dynamicArray->Funcs.dataClear(dynamicArray->Data[i - 1]);
		for (j = i; j < cnt; j++)
		{
			dynamicArray->Data[j - 1] = dynamicArray->Data[j];
		}
		dynamicArray->Count--;
	}
}

int dtDynamicArrayAdd(DynamicArray * dynamicArray, const void * data)
{
	size_t i;

	if(dynamicArray->Count + 1 == dynamicArray->Capacity)
	{
		dynamicArray->Capacity = dynamicArray->Count + 4;
		void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if(NULL == tmp)
		{
			perror("Error: dtDynamicArrayAdd\n");
			return 0;
		}

		for (i = 0; i < dynamicArray->Count; i++)
		{
			tmp[i] = dynamicArray->Data[i];
		}

		free(dynamicArray->Data);
		dynamicArray->Data = tmp;
	}

	dynamicArray->Data[dynamicArray->Count] = dynamicArray->Funcs.dataCreat(dynamicArray->Funcs.SumSize);
	dynamicArray->Funcs.dataCopy(dynamicArray->Data[dynamicArray->Count], data, dynamicArray->Funcs.SumSize);
	dynamicArray->Count++;

	return 1;
}

int dtDynamicArrayInsert(DynamicArray * dynamicArray, const void * data, const size_t i)
{
	size_t j, cnt = dtDynamicArrayGetCount(dynamicArray);

	if(!cnt && i <= cnt && 0 != i)
	{
		if((dynamicArray->Count + 1) == dynamicArray->Capacity)
		{
			dynamicArray->Capacity = dynamicArray->Count + 4;
			void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				perror("Error: dtDynamicArrayInsert\n");
				return 0;
			}

			for (j = 0; j < dynamicArray->Count; j++)
			{
				tmp[j] = dynamicArray->Data[j];
			}

			free(dynamicArray->Data);
			dynamicArray->Data = tmp;
		}

		for (j = cnt - 1; j > i; j--)
		{
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
		}

		dynamicArray->Data[i] = dynamicArray->Funcs.dataCreat(dynamicArray->Funcs.SumSize);
		dynamicArray->Funcs.dataCopy(dynamicArray->Data[i], data, dynamicArray->Funcs.SumSize);
		dynamicArray->Count++;
	}
	return 1;
}

/*
 * LinkedList
 */

void dtLinkedListInit(LinkedList * linkedList, DataFuncsPointers funcs)
{
	linkedList->Head = NULL;
	linkedList->Tail = NULL;
	linkedList->Funcs = funcs;
}

void dtLinkedListClear(LinkedList * linkedList)
{
	while(!dtLinkedListIsEmpty(linkedList))
	{
		ItemLL * tmp = linkedList->Head;

		linkedList->Head = tmp->Next;
		linkedList->Funcs.dataClear(tmp->Data);

		free(tmp);
	}
	linkedList->Tail = NULL;
}

int dtLinkedListIsEmpty(const LinkedList * linkedList)
{
	if(linkedList->Head == NULL)
	{
		return 1;
	}
	return 0;
}

int dtLinkedListGet(LinkedList * linkedList, void * data)
{
	if(!dtLinkedListIsEmpty(linkedList))
	{
		ItemLL * tmp = linkedList->Head;

		linkedList->Head = tmp->Next;
		linkedList->Funcs.dataCopy(data, tmp->Data, linkedList->Funcs.SumSize);
		linkedList->Funcs.dataClear(tmp->Data);

		free(tmp);

		if(dtLinkedListIsEmpty(linkedList))
		{
			linkedList->Tail = NULL;
		}
		return 1;
	}
	return 0;
}

int insertLL(LinkedList * linkedList, const void * data)
{
	ItemLL * tmp = (ItemLL *) malloc(sizeof(ItemLL));

	if(tmp == NULL)
	{
		perror("Error: insertLL\n");
		return 0;
	}

	tmp->Next = NULL;
	tmp->Data = linkedList->Funcs.dataCreat(linkedList->Funcs.SumSize);
	linkedList->Funcs.dataCopy(tmp->Data, data, linkedList->Funcs.SumSize);

	if(dtLinkedListIsEmpty(linkedList))
		linkedList->Head = tmp;
	else
		linkedList->Tail->Next = tmp;

	linkedList->Tail = tmp;

	return 1;
}

int peekLinkedList(const LinkedList * linkedList, void * data)
{
	if(!dtLinkedListIsEmpty(linkedList))
	{
		linkedList->Funcs.dataCopy(data, &(linkedList->Head->Data), linkedList->Funcs.SumSize);
		return 1;
	}

	return 0;
}


/*
void initTree(Tree * t, Strct4DataPointer df)
{
	t->func = df;
	t->root = NULL;
}
void clearTree(Tree * t) // Doðru çalýþýyor mu bak.
{
	DataAddress d;
	LinkedList llist;
	Strct4DataPointer df1 = {sizeof(Node), clearAdr, creatAdr, copyAdr, equalAdr};
	if(isEmptyTree(t))								// Aðaç boþsa çýk
		return;
	initLinkedList(&llist, df1); 					// Adres tutan linked list
	Node iter = t->root;							// Aðacýn kök adresini iter e ata
	d.addres = iter;							// iteri linked liste atamak için datamýza ata
	insertLL(&llist, &d);							// kök adresini linked liste atadýk
	t->func.clearData(&((Node) d.addres)->element);
	while(getLL(&llist, &d))
	{
		for (size_t i = 0; i < ((Node) d.addres)->childs.ArraySize; i++)
		{
			insertLL(&llist, &(iter->childs.array[i]));
			t->func.clearData(&((Node) iter->childs.array[i].addres)->element);
		}
		free(d.addres);
	}
	t->root = NULL;
	clearLinkedList(&llist);
}
int isEmptyTree(const Tree * t)
{
	if(t->root == NULL)
		return 1;
	return 0;
}
*/
/*
MyTree initMyTree(int max_level)
{
	printf("************************** Agaç yapýmýz **************************\n");
	printf("* Level:  1, Kendisi %8s, Dgm: %8x, Data: %4d, Cost:    0 *\n", "Root", *((unsigned int *)&(my_tree->root)), (int) my_tree->root->data);
	setNodes(my_tree->root, max_level, 2); // Doldurma iþlemi soldan saða doðrudur.
	printf("******************************************************************\n");
}
void setNodes(Node node, int level, int step)
{
	if (level >= step)
	{
		for (int i = 0; i < MAX_NODES; i++)
		{
			if (rand() % 2 == 0)
			{
				node->subNodes[i] = (Node) malloc(sizeof(struct node));
				node->subNodes[i]->data = (Data) rand() % 100;
				node->subNodes[i]->cost = (Data) (rand() % 21) * 10 + 100; // 100 ile 300 arasý
				printf("* Level: %2d, UstDgm: %8x, Dgm: %8x, Data: %4d, Cost: %4d *\n", step, *((unsigned int *)&node),
				*((unsigned int *)&node->subNodes[i]), (int) node->subNodes[i]->data, (int) node->subNodes[i]->cost);
				setNodes(node->subNodes[i], level, step + 1);
			}
			else
				node->subNodes[i] = NULL;
		}
	}
	else
		for (int j = 0; j < MAX_NODES; j++)
			node->subNodes[j] = NULL;
}
*/


/*
// Stack
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
//Queue
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


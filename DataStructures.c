/*
 * DataStructure.c
 *
 *  Created on: 13 Ağu 2018
 *      Author: enes.aydin
 */
#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"

/*
 * DynamicArray
 */

void dtDynamicArrayInit(DynamicArray * dynamicArray, StructDataInfo info)
{
	dynamicArray->Info = info;
	dynamicArray->Count = 0;
	dynamicArray->Capacity = 4;
	dynamicArray->Data = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

	if (dynamicArray->Data == NULL)
	{
		perror("Error: dtDynamicArrayInit\n");
	}
}

void dtDynamicArrayReset(DynamicArray * dynamicArray)
{
	while(dtDynamicArrayGetCount(dynamicArray))
	{
		dynamicArray->Info.dataClear(dynamicArray->Data[--dynamicArray->Count]);
	}

	dynamicArray->Capacity = 4;
}

void dtDynamicArrayClear(DynamicArray * dynamicArray)
{
	dtDynamicArrayReset(dynamicArray);

	if (dynamicArray->Data != NULL)
	{
		free(dynamicArray->Data);
	}
}

void dtDynamicArraySort(DynamicArray * dynamicArray)
{
	void * buf;
	size_t i, j, N = dtDynamicArrayGetCount(dynamicArray);

	for(i = 1; i < N; i++)
	{
		for(j = i; (0 < j) && (dynamicArray->Info.dataEqual(dynamicArray->Data[j - 1], dynamicArray->Data[j], dynamicArray->Info.SumSize) > 0); j--)
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

int dtDynamicArrayAdd(DynamicArray * dynamicArray, const void * data)
{
	size_t i;

	if((dynamicArray->Count + 1) == dynamicArray->Capacity)
	{
		dynamicArray->Capacity = dynamicArray->Count + 4;
		void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

		if(NULL == tmp)
		{
			perror("Error: dtDynamicArrayAdd\n");
			return EXIT_FAILURE;
		}

		for (i = 0; i < dynamicArray->Count; i++)
		{
			tmp[i] = dynamicArray->Data[i];
		}

		free(dynamicArray->Data);
		dynamicArray->Data = tmp;
	}

	dynamicArray->Data[dynamicArray->Count] = dynamicArray->Info.dataCreat(dynamicArray->Info.SumSize);
	dynamicArray->Info.dataCopy(dynamicArray->Data[dynamicArray->Count], data, dynamicArray->Info.SumSize);
	dynamicArray->Count++;

	return EXIT_SUCCESS;
}

int dtDynamicArrayRemove(DynamicArray * dynamicArray, const void * data)
{
	size_t i, cnt = dtDynamicArrayGetCount(dynamicArray);

	for (i = 0; i < cnt; i++)
	{
		if (!dynamicArray->Info.dataEqual(data, dynamicArray->Data[i], dynamicArray->Info.SumSize))
		{
			dynamicArray->Info.dataClear(dynamicArray->Data[i]);
			dynamicArray->Data[i] = NULL;
			dynamicArray->Count--;

			for (; i < cnt; i++)
			{
				dynamicArray->Data[i] = dynamicArray->Data[i + 1];
			}

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int dtDynamicArrayRemoveAt(DynamicArray * dynamicArray, const size_t index)
{
	size_t j, cnt = dtDynamicArrayGetCount(dynamicArray);

	if((cnt != 0) && (index <= cnt) && (0 != index))
	{
		dynamicArray->Info.dataClear(dynamicArray->Data[index - 1]);
		for (j = index; j < cnt; j++)
		{
			dynamicArray->Data[j - 1] = dynamicArray->Data[j];
		}
		dynamicArray->Count--;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int dtDynamicArrayInsert(DynamicArray * dynamicArray, const void * data, const size_t index)
{
	size_t j, cnt = dtDynamicArrayGetCount(dynamicArray);

	if((cnt != 0) && (index <= cnt) && (0 != index))
	{
		if((dynamicArray->Count + 1) == dynamicArray->Capacity)
		{
			dynamicArray->Capacity = dynamicArray->Count + 4;
			void ** tmp = (void **) malloc(dynamicArray->Capacity * sizeof(void *));

			if(NULL == tmp)
			{
				perror("Error: dtDynamicArrayInsert\n");
				return EXIT_FAILURE;
			}

			for (j = 0; j < dynamicArray->Count; j++)
			{
				tmp[j] = dynamicArray->Data[j];
			}

			free(dynamicArray->Data);
			dynamicArray->Data = tmp;
		}

		for (j = cnt; j >= index - 1; j--)
		{
			dynamicArray->Data[j] = dynamicArray->Data[j - 1];
		}

		dynamicArray->Data[index - 1] = dynamicArray->Info.dataCreat(dynamicArray->Info.SumSize);
		dynamicArray->Info.dataCopy(dynamicArray->Data[index - 1], data, dynamicArray->Info.SumSize);
		dynamicArray->Count++;
	}
	return EXIT_SUCCESS;
}

int dtDynamicArrayGetFrom(const DynamicArray * dynamicArray, void * data, const size_t index)
{
	if((0 != index) && (index <= dtDynamicArrayGetCount(dynamicArray)))
	{
		dynamicArray->Info.dataCopy(data, dynamicArray->Data[index - 1], dynamicArray->Info.SumSize);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

/*
 * LinkedList
 */

void dtLinkedListInit(LinkedList * linkedList, StructDataInfo funcs)
{
	linkedList->Head = NULL;
	linkedList->Tail = NULL;
	linkedList->Funcs = funcs;
}

void dtLinkedListReset(LinkedList * linkedList)
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

void dtLinkedListClear(LinkedList * linkedList)
{
	dtLinkedListReset(linkedList);
}

void dtLinkedListSort(LinkedList * linkedList)
{
	//TODO:
}

int dtLinkedListIsEmpty(const LinkedList * linkedList)
{
	if(linkedList->Head == NULL)
	{
		return 1;
	}
	return 0;
}

int dtLinkedListAdd(LinkedList * linkedList, const void * data)
{
	ItemLL * iter = linkedList->Head, * tmp;

	if((tmp = (ItemLL *) malloc(sizeof(ItemLL))) == NULL)
	{
		perror("Error: dtLinkedListInsert\n");
		return EXIT_FAILURE;
	}

	tmp->Next = NULL;
	tmp->Data = linkedList->Funcs.dataCreat(linkedList->Funcs.SumSize);
	linkedList->Funcs.dataCopy(tmp->Data, data, linkedList->Funcs.SumSize);

	if (iter == NULL)
	{
		linkedList->Head = tmp;
	}
	else
	{
		while (iter->Next != NULL)
		{
			iter = iter->Next;
		}

		iter->Next = tmp;
	}

	linkedList->Tail = tmp;

	return EXIT_SUCCESS;
}

int dtLinkedListRemove(LinkedList * linkedList, const void * data)
{
	int i;
	ItemLL * iter = linkedList->Head;

	for (i = 1; 0 != linkedList->Funcs.dataEqual(data, iter->Data, linkedList->Funcs.SumSize); i++)
	{
		if (iter->Next == NULL)
		{
			return EXIT_FAILURE;
		}
		iter = iter->Next;
	}

	linkedList->Funcs.dataClear(iter->Data);
	iter->Data = iter->Next->Data;
	void * p = iter->Next->Next;
	free(iter->Next);
	iter->Next = p;

	return EXIT_SUCCESS;
}

int dtLinkedListRemoveAt(LinkedList * linkedList, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head;

	if (0 != index)
	{
		for (i = 1; i < index; i++)
		{
			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		linkedList->Funcs.dataClear(iter->Data);
		iter->Data = iter->Next->Data;
		void * p = iter->Next->Next;
		free(iter->Next);
		iter->Next = p;
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int dtLinkedListInsert(LinkedList * linkedList, const void * data, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head, * tmp;

	if (0 != index)
	{
		if((tmp = (ItemLL *) malloc(sizeof(ItemLL))) == NULL)
		{
			perror("Error: dtLinkedListInsert\n");
			return EXIT_FAILURE;
		}

		for (i = 1; i < index; i++)
		{
			if ((iter->Next == NULL) && ((i + 1) != index))
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		tmp->Data = iter->Data;
		tmp->Next = iter->Next;
		iter->Next = tmp;

		iter->Data = linkedList->Funcs.dataCreat(linkedList->Funcs.SumSize);
		linkedList->Funcs.dataCopy(iter->Data, data, linkedList->Funcs.SumSize);

		if(tmp->Next == NULL)
		{
			linkedList->Tail = tmp;
		}
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int dtLinkedListGetFrom(const LinkedList * linkedList, void * data, const size_t index)
{
	int i;
	ItemLL * iter = linkedList->Head;

	if (0 != index)
	{
		for (i = 1; i < index; i++)
		{
			if (iter->Next == NULL)
			{
				return EXIT_FAILURE;
			}
			iter = iter->Next;
		}

		linkedList->Funcs.dataCopy(data, iter->Data, linkedList->Funcs.SumSize);
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
 * Tree
 */

void dtTreeInit(Tree * tree, StructDataInfo Info)
{
	tree->Root = NULL;
	tree->Info = Info;
}

void dtTreeReset(Tree * tree)
{
	//TODO:
}

void dtTreeClear(Tree * tree)
{
	//TODO:
}


/*
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

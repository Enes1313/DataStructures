/*
 * DataStructure.c
 *
 *  Created on: 13 Aðu 2018
 *      Author: enes.aydin
 */

#include "dataStructure.h"

// DynamicArray

void dtDynamicArrayInit(DynamicArray * dynamicArray, DataFuncsPointers funcs)
{
	dynamicArray->Funcs = funcs;
	dynamicArray->Array.Count = 0;
	dynamicArray->Array.Capacity = 4;
	dynamicArray->Array.Data = (void **) calloc(dynamicArray->Array.Capacity, sizeof(void *));
}

void dtDynamicArrayClear(DynamicArray * dynamicArray)
{
	while(dtDynamicArrayGetCount(dynamicArray))
	{
		dynamicArray->Funcs.dataClear(dynamicArray->Array.Data[--dynamicArray->Array.Count]);
	}
}

void dtDynamicArraySort(DynamicArray * dynamicArray)
{
	int i, j;
	void * buf;
	Type N = dtDynamicArrayGetCount(dynamicArray);

	for(i = 1; i < N; i++)
	{
		for(j = i; j > 0 && dynamicArray->Funcs.dataEqual(dynamicArray->Array.Data[j - 1], dynamicArray->Array.Data[j], dynamicArray->Funcs.SumSize) > 0; j--)
		{
			buf = dynamicArray->Array.Data[j];
			dynamicArray->Array.Data[j] = dynamicArray->Array.Data[j - 1];
			dynamicArray->Array.Data[j - 1] = buf;
		}
	}
}

Type dtDynamicArrayGetCount(const DynamicArray * dynamicArray)
{
	return dynamicArray->Array.Count;
}

Type dtDynamicArrayGetCapacity(const DynamicArray * dynamicArray)
{
	return dynamicArray->Array.Capacity;
}

_Bool dtDynamicArrayGetFrom(DynamicArray * dynamicArray, void * data, const Type i)
{
	if(dtDynamicArrayGetCount(dynamicArray))
	{
		if(i != 0 && i <= dynamicArray->Array.Count)
		{
			dynamicArray->Funcs.dataCopy(data, dynamicArray->Array.Data[i - 1], dynamicArray->Funcs.SumSize);
			return 1;
		}
	}
	return 0;
}

void dtDynamicArrayRemove(DynamicArray * dynamicArray, const void * data)
{
	int i = 0;
	Type cnt = dtDynamicArrayGetCount(dynamicArray);

	for (; i < cnt; i++)
	{
		if (!dynamicArray->Funcs.dataEqual(data, dynamicArray->Array.Data[i], dynamicArray->Funcs.SumSize))
		{
			dynamicArray->Funcs.dataClear(dynamicArray->Array.Data[i]);
			dynamicArray->Array.Data[i] = NULL;
			break;
		}
	}

	for (; i < cnt; i++)
	{
		dynamicArray->Array.Data[i] = dynamicArray->Array.Data[i + 1];
	}

	dynamicArray->Array.Count--;
}

void dtDynamicArrayRemoveAt(DynamicArray * dynamicArray, const Type i)
{
	Type cnt = dtDynamicArrayGetCount(dynamicArray);
	if(!cnt && i <= cnt && i != 0)
	{
		dynamicArray->Funcs.dataClear(dynamicArray->Array.Data[i - 1]);
		for (int j = i; j < cnt; j++)
		{
			dynamicArray->Array.Data[j - 1] = dynamicArray->Array.Data[j];
		}
		dynamicArray->Array.Count--;
	}
}

_Bool dtDynamicArrayAdd(DynamicArray * dynamicArray, const void * data)
{
	if(dynamicArray->Array.Count + 1 == dynamicArray->Array.Capacity)	// Deðiþtirilebilir
	{
		dynamicArray->Array.Capacity = dynamicArray->Array.Count + 4;
		void ** tmp = (void **) calloc(dynamicArray->Array.Capacity, sizeof(void *));

		if(tmp == NULL)
		{
			perror("Error: dtDynamicArrayInsert\n");
			return 0;
		}

		for (Type i = 0; i < dynamicArray->Array.Count; i++)
		{
			tmp[i] = dynamicArray->Array.Data[i];
		}

		free(dynamicArray->Array.Data);
		dynamicArray->Array.Data = tmp;
	}

	dynamicArray->Array.Data[dynamicArray->Array.Count] = dynamicArray->Funcs.dataCreat(dynamicArray->Funcs.SumSize);
	dynamicArray->Funcs.dataCopy(dynamicArray->Array.Data[dynamicArray->Array.Count], data, dynamicArray->Funcs.SumSize);
	dynamicArray->Array.Count++;

	return 1;
}

_Bool dtDynamicArrayInsert(DynamicArray * dynamicArray, const void * data, const Type i)
{
	Type cnt = dtDynamicArrayGetCount(dynamicArray);

	if(!cnt && i <= cnt && i != 0)
	{
		if((dynamicArray->Array.Count + 1) == dynamicArray->Array.Capacity)	// Deðiþtirilebilir
		{
			dynamicArray->Array.Capacity = dynamicArray->Array.Count + 4;
			void ** tmp = (void **) calloc(dynamicArray->Array.Capacity, sizeof(void *));

			if(tmp == NULL)
			{
				perror("Error: dtDynamicArrayInsert\n");
				return 0;
			}

			for (Type i = 0; i < dynamicArray->Array.Count; i++)
				tmp[i] = dynamicArray->Array.Data[i];

			free(dynamicArray->Array.Data);
			dynamicArray->Array.Data = tmp;
		}

		for (int j = cnt - 1; j > i; j--)
		{
			dynamicArray->Array.Data[j] = dynamicArray->Array.Data[j - 1];
		}

		dynamicArray->Array.Data[i] = dynamicArray->Funcs.dataCreat(dynamicArray->Funcs.SumSize);
		dynamicArray->Funcs.dataCopy(dynamicArray->Array.Data[i], data, dynamicArray->Funcs.SumSize);
		dynamicArray->Array.Count++;
	}
	return 1;
}
// LinkedList

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
		for (Type i = 0; i < ((Node) d.addres)->childs.ArraySize; i++)
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

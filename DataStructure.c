/*
 * DataStructure.c
 *
 *  Created on: 13 Aðu 2018
 *      Author: enes.aydin
 */

#include "dataStructure.h"

// Mem.
/*
void dtMemClear(void * data)
{
	free(data);
}

void * dtMemCreat(Type dataSize)
{
	return malloc(dataSize);
}

void dtMemCopy(void * toData, const void * fromData, Type dataSize)
{
	memcpy(toData, fromData, dataSize);
}

int dtMemEqual(const void * data1, const void * data2, Type size) //eþitse 1
{
	return !memcmp(data1, data2, size);
}
*/
// DynamicArray

void dtDynamicArrayInit(DynamicArray * dynamicArray, DataFuncsPointers funcs)
{
	dynamicArray->Funcs = funcs;
	dynamicArray->ArraySize = 0;
	dynamicArray->ArrayCapacity = 4;
	dynamicArray->ArrayData = (ItemDA *) calloc(dynamicArray->ArrayCapacity, sizeof(ItemDA));
}

void dtDynamicArrayClear(DynamicArray * dynamicArray)
{
	while(!dtDynamicArrayIsEmpty(dynamicArray))
	{
		dynamicArray->Funcs.dataClear(dynamicArray->ArrayData[--(dynamicArray->ArraySize)].data);
	}
	free(dynamicArray->ArrayData);
}

int dtDynamicArrayIsEmpty(const DynamicArray * dynamicArray)
{
	if(dynamicArray->ArraySize == 0)
	{
		return 1;
	}
	return 0;
}

int dtDynamicArrayGetFrom(DynamicArray * dynamicArray, void * data, const Type i)
{
	if(!dtDynamicArrayIsEmpty(dynamicArray))
	{
		if((i != 0) && (i <= dynamicArray->ArraySize))
		{
			dynamicArray->Funcs.dataCopy(data, dynamicArray->ArrayData[i - 1].data, dynamicArray->Funcs.SumSize);
			return 1;
		}
	}
	return 0;
}

int dtDynamicArrayInsert(DynamicArray * dynamicArray, const void * data)
{
	if((dynamicArray->ArraySize + 1) == dynamicArray->ArrayCapacity)	// Deðiþtirilebilir
	{
		dynamicArray->ArrayCapacity = dynamicArray->ArraySize + 4;
		ItemDA * tmp = calloc(dynamicArray->ArrayCapacity, sizeof(ItemDA));

		if(tmp == NULL)
		{
			perror("Error: dtDynamicArrayInsert\n");
			return 0;
		}

		for (Type i = 0; i < dynamicArray->ArraySize; i++)
			tmp[i].data = dynamicArray->ArrayData[i].data;

		free(dynamicArray->ArrayData);
		dynamicArray->ArrayData = tmp;
	}

	dynamicArray->ArrayData[dynamicArray->ArraySize].data = dynamicArray->Funcs.dataCreat(dynamicArray->Funcs.SumSize);
	dynamicArray->Funcs.dataCopy(dynamicArray->ArrayData[dynamicArray->ArraySize].data, data, dynamicArray->Funcs.SumSize);
	dynamicArray->ArraySize++;

	return 1;
}
/*
// LinkedList

void initLinkedList(LinkedList * pll, Strct4DataPointer df)
{
	pll->func = df;
	pll->head = NULL;
	pll->tail = NULL;
}

void clearLinkedList(LinkedList * pll)
{
	while(!isEmptyLinkedList(pll))
	{
		Item tmp = pll->head;
		pll->head = tmp->next;
		pll->func.clearData(&(tmp->data));
		free(tmp);
	}
	pll->tail = NULL;
}

int isEmptyLinkedList(const LinkedList * pll)
{
	if(pll->head == NULL)
		return 1;
	return 0;
}

int getLL(LinkedList * pll, void * pd)
{
	if(!isEmptyLinkedList(pll))
	{
		Item tmp = pll->head;
		pll->head = tmp->next;
		pll->func.copyData(pd, &(tmp->data), pll->func.sum_size);
		pll->func.clearData(&(tmp->data));
		free(tmp);

		if(isEmptyLinkedList(pll))
			pll->tail = NULL;
		return 1;
	}
	return 0;
}

int insertLL(LinkedList * pll, const void * pd)
{
	Item tmp = (Item) malloc(sizeof(struct item));

	if(tmp == NULL)
	{
		perror("Error: insertLL\n");
		return 0;
	}

	tmp->next = NULL;
	pll->func.creatData(&(tmp->data), pll->func.sum_size);
	pll->func.copyData(&(tmp->data), pd, pll->func.sum_size);

	if(isEmptyLinkedList(pll))
		pll->head = tmp;
	else
		pll->tail->next = tmp;

	pll->tail = tmp;

	return 1;
}

int peekLinkedList(const LinkedList * pll, void * pd)
{
	if(!isEmptyLinkedList(pll))
	{
		pll->func.copyData(pd, &(pll->head->data), pll->func.sum_size);
		return 1;
	}

	return 0;
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

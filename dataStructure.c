/*
 * vy.c
 *
 *  Created on: 13 Ağu 2018
 *      Author: NS
 */

#include "dataStructure.h"

// Mem.

void clearMem(DataAddress * pd)
{
	free(pd->addres);
}

void creatMem(DataAddress * pd, Type size)
{
	pd->addres = malloc(size);
}

void copyMem(DataAddress * pd1, const DataAddress * pd2, Type size)
{
	memcpy(pd1->addres, pd2->addres, size);
}

int equalMem(const DataAddress * pd1, const DataAddress * pd2, Type size) //eşitse 1
{
	return !memcmp(pd1->addres, pd2->addres, size);
}

// Addres

void clearAdr(DataAddress * pd) // Uyumluluk
{
	if (pd == NULL){ // for warning
	}
}

void creatAdr(DataAddress * pd, Type size)
{
	if(pd->addres == NULL && size > 3){
	}
}

void copyAdr(DataAddress * pd1, const DataAddress * pd2, Type size)
{
	if (size >= 3){ // for warning
	}
	pd1->addres = pd2->addres;
}

int equalAdr(const DataAddress * pd1, const DataAddress * pd2, Type size)
{
	if (size >= 3){ // for warning
	}
	if(pd1->addres == pd2->addres)
		return 1;
	return 0;
}

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

int getLL(LinkedList * pll, DataAddress * pd)
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

int insertLL(LinkedList * pll, const DataAddress * pd)
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

int peekLinkedList(const LinkedList * pll, DataAddress * pd)
{
	if(!isEmptyLinkedList(pll))
	{
		pll->func.copyData(pd, &(pll->head->data), pll->func.sum_size);
		return 1;
	}

	return 0;
}

// DynamicArray

void initDynamicArray(DynamicArray * pda, Strct4DataPointer df)
{
	pda->func = df;
	pda->boyut = 0;
	pda->kapasite = 4;
	pda->array = (DataAddress *) calloc(pda->kapasite, sizeof(DataAddress));
}

void clearDynamicArray(DynamicArray * pda)
{
	while(!isEmptyDynamicArray(pda))
		pda->func.clearData(&(pda->array[--(pda->boyut)]));
	free(pda->array);
}

int isEmptyDynamicArray(const DynamicArray * pda)
{
	if(pda->boyut == 0)
		return 1;
	return 0;
}

int getFrDA(DynamicArray * pda, DataAddress *pd, const Type i)
{
	if(!isEmptyDynamicArray(pda))
	{
		if((i != 0) && (i <= pda->boyut))
		{
			pda->func.copyData(pd, &(pda->array[i - 1]), pda->func.sum_size);
			return 1;
		}
	}
	return 0;
}

int insertDA(DynamicArray * pda, const DataAddress * pd)
{
	if((pda->boyut + 1) == pda->kapasite)	// Değiştirilebilir
	{
		pda->kapasite = pda->boyut + 4;
		DataAddress * tmp = (DataAddress *) calloc(pda->kapasite, sizeof(DataAddress));

		if(tmp == NULL)
		{
			perror("Error: insertDA\n");
			return 0;
		}

		for (Type i = 0; i < pda->boyut; i++)
			tmp[i].addres = pda->array[i].addres;

		free(pda->array);
		pda->array = tmp;
	}

	pda->func.creatData(&(pda->array[pda->boyut]), pda->func.sum_size);
	pda->func.copyData(&(pda->array[pda->boyut]), pd, pda->func.sum_size);
	pda->boyut++;

	return 1;
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

void clearTree(Tree * t) // Doğru çalışıyor mu bak.
{
	DataAddress d;
	LinkedList llist;
	Strct4DataPointer df1 = {sizeof(Node), clearAdr, creatAdr, copyAdr, equalAdr};

	if(isEmptyTree(t))								// Ağaç boşsa çık
		return;

	initLinkedList(&llist, df1); 					// Adres tutan linked list

	Node iter = t->root;							// Ağacın kök adresini iter e ata
	d.addres = iter;							// iteri linked liste atamak için datamıza ata
	insertLL(&llist, &d);							// kök adresini linked liste atadık
	t->func.clearData(&((Node) d.addres)->element);

	while(getLL(&llist, &d))
	{
		for (Type i = 0; i < ((Node) d.addres)->childs.boyut; i++)
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
	printf("************************** Agaç yapımız **************************\n");
	printf("* Level:  1, Kendisi %8s, Dgm: %8x, Data: %4d, Cost:    0 *\n", "Root", *((unsigned int *)&(my_tree->root)), (int) my_tree->root->data);

	setNodes(my_tree->root, max_level, 2); // Doldurma işlemi soldan sağa doğrudur.

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
				node->subNodes[i]->cost = (Data) (rand() % 21) * 10 + 100; // 100 ile 300 arası

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

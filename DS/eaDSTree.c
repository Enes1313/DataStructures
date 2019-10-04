#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eaDSTree.h"

void eaDSTreeInit(eaDSTree * tree, eaDSDataInfo Info)
{
	tree->Root = NULL;
	tree->Info = Info;
}

void eaDSTreeReset(eaDSTree * tree)
{
	/*TODO:*/
}

void eaDSTreeClear(eaDSTree * tree)
{
	/*TODO:*/
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


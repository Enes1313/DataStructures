/*
 * eaDSTree.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSTREE_H_
#define EADSTREE_H_

#include "eaDSData.h"
#include "eaDSDynamicArray.h"
/*
 * Tree
 */

typedef struct _Node_Tree{
	void * Data;
	void * Parent;
	/*eaDSDynamicArray Children;*/
} Node_Tree;

typedef struct _eaDSTree{
	Node_Tree * Root;
	eaDSInfosForData Infos;
} eaDSTree;

void eaDSTreeInit(eaDSTree * tree, eaDSInfosForData infos);
void eaDSTreeReset(eaDSTree * tree);
void eaDSTreeClear(eaDSTree * tree);


/*

void clearTree(Tree *);
int isEmptyTree(const Tree *);
*/
/*
void setNodes(Node, int, int);
Tree initMyTree(int);
*/


#endif /* EADSTREE_H_ */

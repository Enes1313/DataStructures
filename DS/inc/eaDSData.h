/*
 * eaDSData.h
 *
 *  Created on: 31 03 2019
 *      Author: Enes AYDIN
 */

#ifndef EADSDATA_H
#define EADSDATA_H

/*
 * struct for data-specific operations
 */
#include <stddef.h>

typedef struct _StructDataInfo{
	size_t SumSize;
	void (*dataClear)(void *);
	void * (*dataCreat)(const size_t);
	void * (*dataCopy)(void *, const void *, const size_t);
	int (*dataEqual)(const void *, const void *, const size_t);	/* Eşitse 0 büyükse 1 küçükse -1*/
} StructDataInfo;

#endif /* EADSDATA_H */

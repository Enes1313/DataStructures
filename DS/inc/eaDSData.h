/********************************************************************************
* DESCRIPTION : It is an implementation of general Data.
* NOTES       : If you want, don't use for int type and pass NULL to init funcs.
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSDATA_H
#define EADSDATA_H

#include <stddef.h>

typedef struct _eaDSInfosForData{
	size_t	SumSize;
	void 	(*dataClear)(void *);
	void *	(*dataCreate)(const size_t);
	void *	(*dataCopy)(void *, const void *, const size_t);
	int 	(*dataEqual)(const void *, const void *, const size_t);  /* = 0, > 1, < -1 */
} eaDSInfosForData;

#endif /* EADSDATA_H */

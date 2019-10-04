/********************************************************************************
* DESCRIPTION : It is an implementation of general Data.
* NOTES       : If you want, don't use for int type and pass NULL to init funcs.
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSDATA_H
#define EADSDATA_H

#include <stddef.h>

#define DS_DEBUG	1

#if DS_DEBUG
#include <stdio.h>

#define EA_ERROR(x)	perror(x)
#define EA_INFO(...)	printf(__VA_ARGS__)
#else
#define EA_ERROR(x)
#define EA_INFO(...)
#endif

typedef struct _eaDSDataInfo{
	size_t	SumSize;
	void 	(*dataClear)(void *);
	void *	(*dataCreat)(const size_t);
	void *	(*dataCopy)(void *, const void *, const size_t);
	int 	(*dataEqual)(const void *, const void *, const size_t);  /* = 0, > 1, < -1 */
} eaDSDataInfo;

#endif /* EADSDATA_H */

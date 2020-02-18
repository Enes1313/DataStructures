/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of Dynamic Array.
* NOTES       : Increase or decrease in Capacity in eaDSDynamicArrayAdd and
*               eaDSDynamicArrayInsert functions can be changed.
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSDYNAMICARRAY_H
#define EADSDYNAMICARRAY_H

#include <stddef.h>

/********************************************************************************
* DESCRIPTION : The data type used for a dynamic array.
* NOTES       : Define "eaDSDynamicArray dA;" or "eaDSDynamicArray dA = NULL;".
********************************************************************************/
typedef struct _eaDSDynamicArray * eaDSDynamicArray;

/********************************************************************************
* DESCRIPTION : Initialize the dynamic array with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            dataCreate -> Data-specific memory alloc. function
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSDynamicArray type or NULL.
* NOTES       : All parameters are used in library.
********************************************************************************/
eaDSDynamicArray eaDSDynamicArrayInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *));

/********************************************************************************
* DESCRIPTION : Initialize the dynamic array with the given details for DA.
* INPUTS      :
*               PARAMETERS :
*                            info -> A struct which about infos for data.
*                                    (size, clear, creat, copy, equal)
*                            expFactor -> Increase value of memory area.
*                            startingCapacity -> Value of the starting capacity.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSDynamicArray type or NULL.
* NOTES       : If "info" will be NULL, It will use default settings.
*               {sizeof(int), free, malloc, memcpy, memcmp}
********************************************************************************/
eaDSDynamicArray eaDSDynamicArrayInitWithDetails(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataEqual)(const void *, const void *), void (*dataClear)(void *), unsigned short expFactor, unsigned short startingCapacity);

/********************************************************************************
* DESCRIPTION : Reset the dynamic array. Context of dynamic array is deleted.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses clear function given in info struct.
********************************************************************************/
int eaDSDynamicArrayReset(eaDSDynamicArray dynamicArray);

/********************************************************************************
* DESCRIPTION : Clear the dynamic array. The address must not be used later.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function given in info struct.
********************************************************************************/
void eaDSDynamicArrayClear(eaDSDynamicArray dynamicArray);

/********************************************************************************
* DESCRIPTION : Sorting operation of the dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses equal function given in info struct.
********************************************************************************/
void eaDSDynamicArraySort(eaDSDynamicArray dynamicArray);

/********************************************************************************
* DESCRIPTION : Count of data in dynamic array returns.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : A value from size_t type.
* NOTES       : None
********************************************************************************/
size_t eaDSDynamicArrayGetCount(const eaDSDynamicArray dynamicArray);

/********************************************************************************
* DESCRIPTION : Capacity of dynamic array returns.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : A value from size_t type.
* NOTES       : None
********************************************************************************/
size_t eaDSDynamicArrayGetCapacity(const eaDSDynamicArray dynamicArray);

/********************************************************************************
* DESCRIPTION : Data is added to dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            data -> Address to add to the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses creat and copy functions given in info struct.
********************************************************************************/
int eaDSDynamicArrayAdd(eaDSDynamicArray dynamicArray, const void * data);

/********************************************************************************
* DESCRIPTION : "data" param is inserted to index of dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            data -> Address of data for the dynamic array.
*                            index -> Index in the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses creat and copy functions given in info struct.
********************************************************************************/
int eaDSDynamicArrayInsert(eaDSDynamicArray dynamicArray, const void * data, const size_t index);

/********************************************************************************
* DESCRIPTION : "data" in DA is removed from dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            data -> Address to remove from the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses free function given in info struct.
********************************************************************************/
void eaDSDynamicArrayRemove(eaDSDynamicArray dynamicArray, const void * data);

/********************************************************************************
* DESCRIPTION : All "data" in DA is removed from dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            data -> Address to remove from the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses free function given in info struct.
********************************************************************************/
void eaDSDynamicArrayRemoveAll(eaDSDynamicArray dynamicArray, const void * data);

/********************************************************************************
* DESCRIPTION : Data is removed from index of dynamic array.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            index -> Index of any data in the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses free function given in info struct.
********************************************************************************/
void eaDSDynamicArrayRemoveAt(eaDSDynamicArray dynamicArray, const size_t index);

/********************************************************************************
* DESCRIPTION : Data is removed from index of dynamic array.
*
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            index -> Index of any data in the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : As eaDSDynamicArrayRemoveAt funciton and last item is copied.
********************************************************************************/
void eaDSDynamicArrayRemoveAtCopyLastItem(eaDSDynamicArray dynamicArray, const size_t index);

/********************************************************************************
* DESCRIPTION : Data in dynamic array is taken to "data" param.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            data -> Address to copy from the dynamic array.
*                            index -> Index in the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS :
*                            data -> It is Data in index of the dynamic array.
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses copy function given in info struct.
********************************************************************************/
int eaDSDynamicArrayGetFrom(const eaDSDynamicArray dynamicArray, void * data, const size_t index);

/********************************************************************************
* DESCRIPTION : Address of data in dynamic array is return.
* INPUTS      :
*               PARAMETERS :
*                            dynamicArray -> Address of a dynamic array.
*                            index -> Index in the dynamic array.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : None
********************************************************************************/
void * eaDSDynamicArrayGetAddressFrom(const eaDSDynamicArray dynamicArray, const size_t index);

#endif /* EADSDYNAMICARRAY_H */

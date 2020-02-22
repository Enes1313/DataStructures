/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of stack.
* NOTES       : Increase or decrease in Capacity in eaDSStackPush
*               functions can be changed.
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSSTACK_H_
#define EADSSTACK_H_

#include <stddef.h>

/********************************************************************************
* DESCRIPTION : The data type used for a stack.
* NOTES       : Define "eaDSStack s;" or "eaDSLinkedList s = NULL;".
********************************************************************************/
typedef struct _eaDSStack * eaDSStack;

/********************************************************************************
* DESCRIPTION : Initialize the stack with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSDynamicArray type or NULL.
* NOTES       : All parameters except "dataCompare" are used in library.
* 				"dataCompare" can be used in the future.
********************************************************************************/
eaDSStack eaDSStackInit(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *));

/********************************************************************************
* DESCRIPTION : Initialize the stack with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
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
eaDSStack eaDSStackInitWithDetails(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *), unsigned short expFactor, unsigned short startingCapacity);

/********************************************************************************
* DESCRIPTION : Reset the stack. Context of stack is deleted.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses clear function passed to init func.
********************************************************************************/
int eaDSStackReset(eaDSStack stack);

/********************************************************************************
* DESCRIPTION : Clear the stack. The address must not be used later.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function passed to init func.
********************************************************************************/
void eaDSStackClear(eaDSStack stack);

/********************************************************************************
* DESCRIPTION : Count of data in stack returns.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : A value from size_t type.
* NOTES       : None
********************************************************************************/
size_t eaDSStackGetCount(const eaDSStack stack);

/********************************************************************************
* DESCRIPTION : Capacity of stack returns.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : A value from size_t type.
* NOTES       : None
********************************************************************************/
size_t eaDSStackGetCapacity(const eaDSStack stack);

/********************************************************************************
* DESCRIPTION : Data is taken and deleted from end of stack.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : This function uses free and copy functions passed to init func.
* 				You have to free the value returned from the function.
********************************************************************************/
void * eaDSStackPop(eaDSStack stack);

/********************************************************************************
* DESCRIPTION : Data is pushed to end of stack.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*                            data -> Address of data to push to the stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses createandcopy functions passed to init func.
********************************************************************************/
int eaDSStackPush(eaDSStack stack, const void * data);

/********************************************************************************
* DESCRIPTION : Data is taken to peek of stack.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : This function uses copy function passed to init func.
* 				You have to free the value returned from the function.
********************************************************************************/
void * eaDSStackPeekValue(const eaDSStack stack, void * data);

/********************************************************************************
* DESCRIPTION : Address of data in peek of stack is return.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : None
********************************************************************************/
void * eaDSStackPeekAddress(const eaDSStack stack);

#endif /* EADSSTACK_H_ */

/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of stack.
* NOTES       : Increase or decrease in Capacity in eaDSStackPush
*               functions can be changed.
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSSTACK_H_
#define EADSSTACK_H_

#include "eaDSData.h"

/********************************************************************************
* DESCRIPTION : The data type used for a stack.
* NOTES       : Define "eaDSStack s;" or "eaDSLinkedList s = NULL;".
********************************************************************************/
typedef struct _eaDSStack * eaDSStack;

/********************************************************************************
* DESCRIPTION : Initialize the stack with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            info -> A struct which about infos for data.
*                                    (size, clear, creat, copy, equal)
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSDynamicArray type or NULL.
* NOTES       : If "info" will be NULL, It will use default settings.
*               {sizeof(int), free, malloc, memcpy, memcmp}
********************************************************************************/
eaDSStack eaDSStackInit(eaDSDataInfo * info);

/********************************************************************************
* DESCRIPTION : Reset the stack. Context of stack is deleted.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function given in info struct.
********************************************************************************/
void eaDSStackReset(eaDSStack stack);

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
* NOTES       : This function uses clear function given in info struct.
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
*                            data -> Address of data to copy from the stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses free and copy functions given in info struct.
********************************************************************************/
int eaDSStackPop(eaDSStack stack, void * data);

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
* NOTES       : This function uses creat and copy functions given in info struct.
********************************************************************************/
int eaDSStackPush(eaDSStack stack, const void * data);

/********************************************************************************
* DESCRIPTION : Data is taken to peek of stack.
* INPUTS      :
*               PARAMETERS :
*                            stack -> Address of a stack.
*                            data -> Address of data to copy from the stack.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses copy function given in info struct.
********************************************************************************/
int eaDSStackPeekStack(const eaDSStack stack, void * data);

#endif /* EADSSTACK_H_ */

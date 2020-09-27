/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of Queue.
* NOTES       : None
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSQUEUE_H_
#define EADSQUEUE_H_

#include <stddef.h>

/********************************************************************************
* DESCRIPTION : The data type used for a queue.
* NOTES       : Define "eaDSQueue q;" or "eaDSQueue q = NULL;".
********************************************************************************/
typedef struct _eaDSQueue * eaDSQueue;

/********************************************************************************
* DESCRIPTION : Initialize the queue with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSLinkedList type or NULL.
* NOTES       : All parameters are used in library.
********************************************************************************/
eaDSQueue eaDSQueueInit(void * (*dataCreateAndCopy)(const void *), void (*dataClear)(void *));

/********************************************************************************
* DESCRIPTION : Reset the queue. Context of queue is deleted.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function passed to init func.
********************************************************************************/
void eaDSQueueReset(eaDSQueue queue);

/********************************************************************************
* DESCRIPTION : Clear the queue. The address must not be used later.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function passed to init func.
********************************************************************************/
void eaDSQueueClear(eaDSQueue queue);

/********************************************************************************
* DESCRIPTION : If queue is empty, 1 returns
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : 0 or 1
* NOTES       : If "queue" is NULL, the function returns 1.
********************************************************************************/
int eaDSQueueIsEmpty(const eaDSQueue queue);

/********************************************************************************
* DESCRIPTION : Data is removed from queue.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : This function uses free function passed to init func.
********************************************************************************/
void * eaDSQueueDequeue(eaDSQueue queue);

/********************************************************************************
* DESCRIPTION : Data is added to queue.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*                            data -> Data address to add to the queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses createandcopy functions passed to init func.
********************************************************************************/
int eaDSQueueEnqueue(eaDSQueue queue, const void * data);

/********************************************************************************
* DESCRIPTION : Data in queue is taken to "data" param.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : This function uses createandcopy function passed to init func.
* 				You have to free the value returned from the function.
********************************************************************************/
void * eaDSQueuePeekValue(const eaDSQueue queue);

/********************************************************************************
* DESCRIPTION : Data in queue is taken to "data" param.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address of data or NULL
* NOTES       : None
********************************************************************************/
void * eaDSQueuePeekAddress(const eaDSQueue queue);

#endif /* EADSQUEUE_H_ */

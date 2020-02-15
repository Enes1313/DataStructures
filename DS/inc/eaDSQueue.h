/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of Queue.
* NOTES       : None
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSQUEUE_H_
#define EADSQUEUE_H_

#include "eaDSData.h"

/********************************************************************************
* DESCRIPTION : The data type used for a queue.
* NOTES       : Define "eaDSQueue q;" or "eaDSQueue q = NULL;".
********************************************************************************/
typedef struct _eaDSQueue * eaDSQueue;

/********************************************************************************
* DESCRIPTION : Initialize the queue with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            info -> A struct which about infos for data.
*                                    (size, clear, creat, copy, equal)
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSLinkedList type or NULL.
* NOTES       : If "info" will be NULL, It will use default settings.
*               {sizeof(int), free, malloc, memcpy, memcmp}
********************************************************************************/
eaDSQueue eaDSQueueInit(eaDSInfosForData * infos);

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
* NOTES       : This function uses clear function given in info struct.
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
* NOTES       : This function uses clear function given in info struct.
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
*                            data -> Data address to remove from the queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses free function given in info struct.
********************************************************************************/
int eaDSQueueDequeue(eaDSQueue queue, void * data);

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
* NOTES       : This function uses creat and copy functions given in info struct.
********************************************************************************/
int eaDSQueueEnqueue(eaDSQueue queue, const void * data);

/********************************************************************************
* DESCRIPTION : Data in queue is taken to "data" param.
* INPUTS      :
*               PARAMETERS :
*                            queue -> Address of a queue.
*                            data -> Address to copy from the queue.
*                            index -> Index in the queue.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS :
*                            data -> It is Data in index of the queue.
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses copy function given in info struct.
********************************************************************************/
int eaDSQueuePeekQueue(const eaDSQueue queue, void * data);

#endif /* EADSQUEUE_H_ */

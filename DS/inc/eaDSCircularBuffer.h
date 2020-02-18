/********************************************************************************
* DESCRIPTION : It is a handly/fastly/amazing implementation of Circular Buffer.
* NOTES       : None
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

#ifndef EADSCIRCULARBUFFER_H_
#define EADSCIRCULARBUFFER_H_

#include <stddef.h>

/********************************************************************************
* DESCRIPTION : The data type used for a circular buffer.
* NOTES       : Define "eaDSCircularBuffer cB;" or "eaDSCircularBuffer cB = NULL;".
********************************************************************************/
typedef struct _eaDSCircularBuffer * eaDSCircularBuffer;

/********************************************************************************
* DESCRIPTION : Initialize the circular buffer with the given structure.
* INPUTS      :
*               PARAMETERS :
*                            info -> A struct which about infos for data.
*                                    (size, clear, creat, copy, equal)
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSCircularBuffer type or NULL.
* NOTES       : If "info" will be NULL, It will use default settings.
*               {sizeof(int), free, malloc, memcpy, memcmp}
********************************************************************************/
eaDSCircularBuffer eaDSCircularBufferInit(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *));

/********************************************************************************
* DESCRIPTION : Initialize the circular buffer with the given details for CB.
* INPUTS      :
*               PARAMETERS :
*                            info -> A struct which about infos for data.
*                                    (size, clear, creat, copy, equal)
*                            capacity -> Length of circular buffer.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSCircularBuffer type or NULL.
* NOTES       : If "info" will be NULL, It will use default settings.
*               {sizeof(int), free, malloc, memcpy, memcmp}
*               This function uses clear function given in info struct.
********************************************************************************/
eaDSCircularBuffer eaDSCircularBufferInitWithDetails(void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *), size_t capacity);

/********************************************************************************
* DESCRIPTION : Reset the circular buffer. Context of circular buffer is deleted.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : None
********************************************************************************/
void eaDSCircularBufferReset(eaDSCircularBuffer circularBuffer);

/********************************************************************************
* DESCRIPTION : Clear the circular buffer. The address must not be used later.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : None
* NOTES       : This function uses clear function given in info struct.
********************************************************************************/
void eaDSCircularBufferClear(eaDSCircularBuffer circularBuffer);

/********************************************************************************
* DESCRIPTION : Data is added to circular buffer.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*                            data -> Data address to add to the circular buffer.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses creat and copy functions given in info struct.
********************************************************************************/
void eaDSCircularBufferAdd(eaDSCircularBuffer circularBuffer, const void * data);

#endif /* EADSCIRCULARBUFFER_H_ */

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
*                            dataCreate -> Data-specific memory alloc. function
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSCircularBuffer type or NULL.
* NOTES       : All parameters are used in library.
********************************************************************************/
eaDSCircularBuffer eaDSCircularBufferInit(size_t sizeOfData, void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *, size_t), int (*dataCompare)(const void *, const void *, size_t), void (*dataClear)(void *));

/********************************************************************************
* DESCRIPTION : Initialize the circular buffer with the given details for CB.
* INPUTS      :
*               PARAMETERS :
*                            dataCreate -> Data-specific memory alloc. function
*                            dataCopy -> Data-specific copy function
*                            dataCompare -> Data-specific compare function
*                            dataClear -> Data-specific clear function
*                            capacity -> Length of circular buffer.
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : Address from eaDSCircularBuffer type or NULL.
* NOTES       : All parameters are used in library.
********************************************************************************/
eaDSCircularBuffer eaDSCircularBufferInitWithDetails(size_t sizeOfData, void * (*dataCreate)(size_t), void * (*dataCopy)(void *, const void *, size_t), int (*dataCompare)(const void *, const void *, size_t), void (*dataClear)(void *), size_t capacity);

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
* NOTES       : This function uses clear function passed to init func.
********************************************************************************/
void eaDSCircularBufferClear(eaDSCircularBuffer circularBuffer);

/********************************************************************************
* DESCRIPTION : Data is added to circular buffer.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*                            data -> Data address to add to the circular buffer.
*                            len -> size of data (sizeof(...))
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses copy functions passed to init func.
********************************************************************************/
int eaDSCircularBufferAdd(eaDSCircularBuffer circularBuffer, const void * data, size_t len);

/********************************************************************************
* DESCRIPTION : Data is added to circular buffer.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*                            data -> Data address to add to the circular buffer.
*                            len -> size of data (sizeof(...))
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses copy functions passed to init func.
********************************************************************************/
int eaDSCircularBufferGet(eaDSCircularBuffer circularBuffer, void * data, size_t len);

/********************************************************************************
* DESCRIPTION : Data is added to circular buffer.
* INPUTS      :
*               PARAMETERS :
*                            circularBuffer -> Address of a circular buffer.
*                            data -> Data address to add to the circular buffer.
*                            numberOfData -> Data length
*                            len -> how many elements later
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : This function uses compare functions passed to init func.
********************************************************************************/
int eaDSCircularBufferGetWhereIsIt(const eaDSCircularBuffer circularBuffer, const void * data, size_t numberOfData, size_t * len);

/********************************************************************************
* DESCRIPTION : Data is added to circular buffer.
* INPUTS      :
*               PARAMETERS :
*                            len -> how much
*               GLOBALS    : None
* OUTPUTS     :
*               PARAMETERS : None
*               GLOBALS    : None
*               RETURN     : EXIT_SUCCESS or EXIT_FAILURE
* NOTES       : None
********************************************************************************/
int eaDSCircularBufferMoveHead(eaDSCircularBuffer circularBuffer, size_t len);

#endif /* EADSCIRCULARBUFFER_H_ */


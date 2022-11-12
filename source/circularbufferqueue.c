/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Chapter 8 from Alexander G Dean book
 *
 *
 * Description: Inlcudes Function definition of all the queue functions
 */

#include "circularbufferqueue.h"

/**************************************************************************************/
								/*FUNCTION DEFINITIONS*/
/**************************************************************************************/
/* Function: Q_Init()
 *
 * Param: *q(address of the structure)
 *
 * return: NULL
 *
 * Description: Intialising the queue
 */
void Q_Init(uart_queue* q)
{
	unsigned int i;
	//Initialize all the array size to zero
	for (i=0; i<Q_MAX_SIZE; i++)
	{
		q->data[i] = 0;
	}
	q->head = 0;
	q->tail = 0;
	q->size = 0;

}

/* Function: Q_Empty()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description: Check if the queue is empty
 */
int Q_Empty(uart_queue* q)
{
	if(q->size==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Function: Q_Full()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description: Check if the queue is full
 */
int Q_Full(uart_queue* q )
{
	//Check if size reached its maximum value
	if(q->size == Q_MAX_SIZE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Function: Q_Size()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description: return the size of the Queue
 */
int Q_Size(uart_queue* q)
{
	return q->size;
}

/* Function: Q_enqueue()
 *
 * Param: *q(address of the structure), buff(buffer data that is to be queued), size(the size required to be queued)
 *
 * return: uint8_t
 *
 * Description: Adds data to the queue and return 1 if successful
 */
uint8_t Q_enqueue(uart_queue* q,void *buff, unsigned int size)
{
	uint32_t masking_state;
	unsigned int index = 0;
	uint8_t* buf_ptr = (uint8_t*)buff;
	//Check if buffer has no data and size of buffer is less than or equal to 0
	if ((buff == NULL) || (size <= 0))
	{
	return 0;
	}
	//Checking if the size parameter passed will fit in the queue
	if ((size + q->size) > Q_MAX_SIZE)
	{
		size = Q_MAX_SIZE - q->size;//Store max data possible
	}
	//Fill the data into the queue
		while((size>0)&&(q->size<=Q_MAX_SIZE))
		{
			q->data[q->tail++] = buf_ptr[index++];
			q->tail %= Q_MAX_SIZE;
			//Disabling irq so that decrement of size is not affected by the interrupt
			masking_state = __get_PRIMASK();
			/*critical section*/
			__disable_irq();
			q->size++;
			size--;
			__set_PRIMASK(masking_state);

		}
		return 1;
}

/* Function: Q_dequeue()
 *
 * Param: *q(address of the structure), buff(buffer data that is to be queued), size(the size required to be queued)
 *
 * return: uint8_t
 *
 * Description: Removes data from  the queue and returns 1 if successful
 */
uint8_t Q_dequeue(uart_queue* q,void* buff, unsigned int size)
{
	uint32_t masking_state;
	int index = 0;
	uint8_t* buf_ptr = (uint8_t*)buff;
	if ((buff == NULL) || (size <= 0) ||(q->size==0))
	{
	return 0;
	}

	if (size > q->size)
	{
		size = q->size;
	}
	//Dequeue the data from the queue
		while((size>0)&&(q->size >=0))
		{
			buf_ptr[index++] = q->data[q->head++];
			q->head %= Q_MAX_SIZE;
			//Disabling irq so that decrement of size is not affected by the interrupt
			masking_state = __get_PRIMASK();
			/*critical section*/
			__disable_irq();
			q->size--;
			size--;
			__set_PRIMASK(masking_state);

		}
		return 1;
}

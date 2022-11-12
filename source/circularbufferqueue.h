/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Chapter 8 from Alexander G Dean book
 *
 *
 * Description: Includes Function definition of all the queue functions
 */
#include "stdint.h"
#include "string.h"
#include "MKL25Z4.h"
#define Q_MAX_SIZE 256

// uart_queue structure
typedef struct
{
	char data[Q_MAX_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int size;
}volatile uart_queue;

/**************************************************************************************/
								/*FUNCTION DECLARATIONS*/
/**************************************************************************************/
/* Function: Q_Init()
 *
 * Param: *q(address of the structure)
 *
 * return: NULL
 *
 * Description: Intialising the queue
 */
void Q_Init(uart_queue*);

/* Function: Q_Empty()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description:Empty the queue
 */
int Q_Empty(uart_queue*);

/* Function: Q_Full()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description: Check if the queue is full
 */
int Q_Full(uart_queue*);

/* Function: Q_Size()
 *
 * Param: *q(address of the structure)
 *
 * return: int
 *
 * Description: return the size of the Queue
 */
int Q_Size(uart_queue*);

/* Function: Q_enqueue()
 *
 * Param: *q(address of the structure), buff(buffer data that is to be queued), size(the size required to be queued)
 *
 * return: uint8_t
 *
 * Description: Adds data to the queue and return 1 if successful
 */
uint8_t Q_enqueue(uart_queue*,void*, unsigned int);

/* Function: Q_dequeue()
 *
 * Param: *q(address of the structure), buff(buffer data that is to be queued), size(the size required to be queued)
 *
 * return: uint8_t
 *
 * Description: Removes data from  the queue and returns 1 if successful
 */
uint8_t Q_dequeue(uart_queue*,void*,unsigned int);

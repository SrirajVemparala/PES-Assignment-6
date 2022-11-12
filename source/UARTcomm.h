/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Lecture given by Professor.Lalit Pandit
 *
 *
 * Description: Includes Function declarations of all the UART functions
 */
#include "MKL25Z4.h"


#define UART_OVERSAMPLE_RATE (16)

/**************************************************************************************/
								/*FUNCTION DECLARATIONS*/
/**************************************************************************************/
/* Function: uart0_init()
 *
 * Param: uint32_t baud_rate
 *
 * return: NULL
 *
 * Description: Intialising UART communication
 */
void  uart0_init(uint32_t baud_rate);


/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Lecture given by Professor.Lalit Pandit
 *
 *
 * Description: Entry point to functions
 */
#include "sysclock.h"
#include "UARTcomm.h"
#include "circularbufferqueue.h"
#include "MKL25Z4.h"
#include "string.h"
#include "stdio.h"
#include "commandprompt.h"

#define UART_BAUDRATE 38400
/* Function: main()
 *
 * Param: NILL
 *
 * return: int
 *
 * Description: Start of Program
 */
int main(void)
{
  sysclock_init();
  //UART initialization
  uart0_init(UART_BAUDRATE);
	__enable_irq();
	printf("Welcome to BreakfastSerial!\n\r");
  // enter infinite loop
 while (1) {
	 commandprompt();
	 __asm volatile ("nop");
  }

  return 0 ;
}

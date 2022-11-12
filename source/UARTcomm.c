/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Lecture given by Professor.Lalit Pandit
 *
 *
 * Description: Includes Function definition of all the UART functions
 */
#include "UARTcomm.h"
#include "stdio.h"
#include "sysclock.h"
#include "circularbufferqueue.h"

#define STOP_BIT 1
char ch;
//Tx Queue
uart_queue tx_queue;
//Rx Queue
uart_queue rx_queue;

/**************************************************************************************/
								/*FUNCTION DEFINITIONS*/
/**************************************************************************************/

/* Function: uart0_init()
 *
 * Param: uint32_t baud_rate
 *
 * return: NULL
 *
 * Description: Intialising UART communication
 */
void uart0_init(uint32_t baud_rate)
 {
	 uint16_t sbr;
	 // Enable clock gating for UARTO and Port A

	 SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;//Enable clock for UART0
	 SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;//Port A clock enable
	 UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK; //RE and TE Disable
	 SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//Clock source set to MCGFLLCLK or  MCGPLLCLK/2
	 SIM->SOPT2 |= 0x00U;//Clock MCGFLLCLK is set
	 PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	 PORTA->PCR[2]=  PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx
	 sbr = (uint16_t) ((SYSCLOCK_FREQUENCY)/(baud_rate * UART_OVERSAMPLE_RATE));
	 UART0->BDH &= ~UART0_BDH_SBR_MASK;
	 UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	 UART0->BDL = UART0_BDL_SBR(sbr);
	 //UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);
	 UART0->BDH |= UART0_BDH_RXEDGIE(0)|UART0_BDH_SBNS(STOP_BIT)|UART0_BDH_LBKDIE(0);
	 UART0->C1= UART0_C1_LOOPS(0) | UART0_C1_M(0) |UART0_C1_PE(0);// Loops= 0 means seperate Rx and Tx. M 0.Start, 8 data bits, stop/ Parity bit disabled
	 UART0->C3 = UART0_C3_TXINV (0) | UART0_C3_ORIE (1)| UART0_C3_NEIE (1) | UART0_C3_FEIE(1)| UART0_C3_PEIE (1);
	 UART0->S1=UART0_S1_OR(1) |UART0_S1_NF(1)|UART0_S1_FE(1)|UART0_S1_PF(1);
	 UART0->S2 = UART0_S2_MSBF(0)|UART0_S2_RXINV(0);
	 Q_Init(&tx_queue);//Initialize queue
	 Q_Init(&rx_queue);//Initialize queue
	  NVIC_SetPriority(UART0_IRQn,2);
	  NVIC_ClearPendingIRQ(UART0_IRQn);
	  NVIC_EnableIRQ(UART0_IRQn);
	  UART0->C2 |= UART_C2_RIE(1);//Enable Tansmit Enable interrupt
	 UART0->C2 |= UART0_C2_TE(1)|UART0_C2_RE(1);// Transmit and Receive Enable

 }

/* Function:UART0_IRQHandler()
 *
 * Param:NULL
 *
 * return:NULL
 *
 * Description: UART Interrupt Handler
 */
void UART0_IRQHandler()
{

	if(UART0->S1 & (UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK))
	{
		// clear the error flags

		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |	UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
	}

	if (UART0->S1 & UART0_S1_RDRF_MASK)
	{
	// received a character and tx queue is not full
		if(!Q_Full(&rx_queue))
		{
			ch=UART0->D;
			Q_enqueue(&rx_queue, &ch, 1);

		}
    }
	if((UART0->C2 & UART0_C2_TIE_MASK) &&(UART0->S1 & UART0_S1_TDRE_MASK))// If TIE mask is enabled
	{
		// can send another character

		if(Q_dequeue(&tx_queue, &ch, 1))
		{
			UART0->D = ch;
		}
		else
		{
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
	else
	{

	}
	//Used for the echo of characters
	if ((UART0->S1 & UART0_S1_TDRE_MASK))
	{

		UART0->D = ch;
	}

}

/* Function: __sys_write()
 *
 * Param: int handle, char* buf, int size
 *
 * return: int
 *
 * Description: REDLIB function to transfer the data when printf function is called.
 */
int __sys_write(int handle, char *buf,int size)
{
	int flag = 0;
	//Queues the data into tx_queue and returns 1 if sucessful
	flag = Q_enqueue(&tx_queue, buf, size);
	//Set TIE bit is not set then set it using the below function
	if(!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(1);
	}
	//Stay in the loop till all the data to be transmitted is dequeued
	while(Q_Size(&tx_queue) != 0);
	//If data is queued correctly then DISABLE TIE once transmission is complete
	if(flag == 1)
	{
		UART0->C2 &= ~UART0_C2_TIE(1);
		return 1;

	}
	else
	{
		return 0;
	}
}

/* Function: __sys_readc()
 *
 * Param: void
 *
 * return: int
 *
 * Description: REDLIB function to read the data when getchar or scanf function is called.
 */
int __sys_readc(void)
{
	char rx_char;
	// wait till you recieve the data
	while(Q_Size(&rx_queue) == 0);
	//Return the character received if dequeue is successful
	if(Q_dequeue(&rx_queue, &rx_char, 1) == 1)
	{
		return rx_char;
	}
	else
	{
		return -1;
	}
}

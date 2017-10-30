/*******************************************************************************
@file:uart.c
@brief:function declarations for uart operation functions

This file declares functions for implementing operations defined in uart.h
@author:Ravi Dubey
@date:10/22/2017
*******************************************************************************/

#include <stdlib.h>
#include "uart.h"
#include "MKL25Z4.h"

UART_enum UART_configure(){

uint32_t SBR;
uint32_t OSR;


//setting clock gating Registers
SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; //enable GPIOA
SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; //Enable clocks to UART0 Module


//Configure UART0 pins in Port Configuration Register.
PORTA->PCR[1] |= PORT_PCR_MUX(0X02); //set PTA1 to UART)_RX
PORTA->PCR[2] |= PORT_PCR_MUX(0X02); //set PTA2 to UART)_TX

//Configure Tx pin as Output. All pins are input by default
PTA_BASE_PTR->PDDR |= (uint32_t)(1<<2);

/*clear UART C1,C2,C3,S2 Registers to disable txr & rxr and load default settings
ie 8 data bits, no parity , 1 stop bit*/
UART0_C2 = 0;  /**< UART Control Register 2, offset: 0x3 */
UART0_C1 = 0;  /**< UART Control Register 1, offset: 0x2 */
UART0_C3 = 0;  /**< UART Control Register 3, offset: 0x6 */
//UART0_S2 = 0;  /**< UART Status Register 2, offset: 0x5 */

//calculate the baud rate as 57600 for 48MHz clock
uint16_t ubd = (uint16_t)( (48000*1000)/(5760*16) );

//set the oversampling rate to 16
UART0_C4 = UARTLP_C4_OSR(15);

//set baud Rate
UART0_BDH =  (ubd >> 8)&UARTLP_BDH_SBR_MASK; /**< UART Baud Rate Register High, offset: 0x0 */
UART0_BDL =  (ubd & UARTLP_BDL_SBR_MASK);  /**< UART Baud Rate Register Low, offset: 0x1 */

//Enable transmitter and rxr
 UART0_C2  |= (uint32_t)(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);      /**< UART Control Register 2, offset: 0x3 */



/*select 48 MHZ clock source in systems option register */
SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

}

UART_enum UART_send(unsigned_byte* data_ptr){

  //write data to data output register and it will be transmitted
  //wait for rxr data ready flag of status register s1 and read data from data output register

   while( !( UART0_S1 && (1<<8) ) ) ;       /**< UART Status Register 1, offset: 0x4 */
   UART0_D = *data_ptr;            /**< UART Data Register, for both rxr and txr. offset: 0x7 */
   return 0;
}

UART_enum UART_send_n(unsigned_byte* data_ptr,size_t num_bytes);

UART_enum UART_receive(unsigned_byte* data_ptr) ;

UART_enum UART_receive_n(unsigned_byte* data_ptr,size_t num_bytes);

void UART0_IRQHandler();

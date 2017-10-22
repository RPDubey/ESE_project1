/*******************************************************************************
@file:uart.h
@brief:An abstraction for uart operations implemented in uart.c

This file provides definitions for functions and external variables of file
uart.c
@author:Ravi Dubey
@date:10/22/2017
*******************************************************************************/

#include <stdint.h>
#include "circbuf.h"

#ifndef FILE_UART
#define FILE_UART

//enum for return type of UART functions.
typedef enum{
success
}UART_enum_t;


/*************************************************************************
@brief:Configures UART to given settings

This function configures UART to given settings, using predefined bitmasks
and macros
@param:none
@return:UART_enum_t
*************************************************************************/
UART_enum_t UART_configure()



/*************************************************************************
@brief: This​ ​ function​ ​ will​ ​ send​ ​ a ​ ​ single​ ​ byte​ ​ down​ ​ a ​ ​ specific​ ​ UART​ ​ device

This​ ​ function​ ​ will​ ​ send​ ​ a ​ ​ single​ ​ byte​ ​ down​ ​ a ​ ​ specific​ ​ UART​ ​ device.It takes
pointer to data item to send.It blocks on already transmitting data.

@param:pointer to data item to send
@return:UART_enum_t
*************************************************************************/
UART_enum_t​ UART_send(unsigned_byte* );



/*************************************************************************
@brief: This​ ​ function​ ​ will​ ​ send​s n​ bytes​ ​ down​ ​ a ​ ​ specific​ ​ UART​ ​ device

This​ ​function​ ​will​ send n bytes​ down​​ a specific​ UART​ device. It takes pointer to data
item to send & no. of items to send .It blocks on already transmitting data.
@param:pointer to data item to send, no. of bytes to send
@return: UART_enum_t
*************************************************************************/
UART_enum_t​ UART_send_n( ​unsigned_byte* , size_t​​ );



/*************************************************************************
@brief: This​ ​ function​ ​ returns a byte rxd from​ a​ specific​ ​ UART​ ​ device

This​ ​ function​ ​ should​ ​ return​ ​ a ​ ​ received​ ​ byte​ ​ on​ ​ the​ ​ UART​ ​ using​ ​ an​ ​ input​ ​
parameter​ ​ pointer.Blocks until the character has been rxd.
@param:pointer to data item to send
@return: UART_enum_t
*************************************************************************/
UART_enum_t​ UART_receive( unsigned_byte* );



/*************************************************************************
@brief: This​ ​ function​ ​ returns n bytes rxd from​ a​ specific​ ​ UART​ ​ device

This​ ​ function​ ​ should​ ​ return​ ​ received​ ​ byte​s ​ on​ ​ the​ ​ UART​ ​ using​ ​ an​ ​ input​ ​
parameter​ ​ pointer.Blocks until the characters have been rxd.
@param:pointer to data item to send, no. of bytes
@return: UART_enum_t
*************************************************************************/
UART_enum_t​ UART_receive_n( ​unsigned_byte* , size_t​ );



/*************************************************************************
@brief: This​ ​ function​ ​ is the IRQ handler for the UART

This​ ​ function​ ​ is​ ​ the​ ​ IRQ​ ​ handler​ ​ for​ ​ the​ ​ UART. We​​ handle​ ​ two​ ​ types​ ​ of
interrupts​ ​ in​ ​ this​ ​ function - Receive​ ​ Interrupts & Transmit​ ​ interrupt.
Each​ ​interrupt​ ​clears their​ associated flag​ when​ completed​ but​ only if​ ​ they​ ​ were​ ​ set
@param: none
@return: void
*************************************************************************/
void​ UART0_IRQHandler();


#endif

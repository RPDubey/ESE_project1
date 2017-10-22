/*******************************************************************************
@file:uart.c
@brief:function declarations for uart operation functions

This file declares functions for implementing operations defined in uart.h
@author:Ravi Dubey
@date:10/22/2017
*******************************************************************************/

#include <stdlib.h>
#include "uart.h"

UART_enum UART_configure();

UART_enum UART_send(unsigned_byte* data_ptr);

UART_enum UART_send_n(unsigned_byte* data_ptr,size_t num_bytes);

UART_enum UART_receive(unsigned_byte* data_ptr) ;

UART_enum UART_receive_n(unsigned_byte* data_ptr,size_t num_bytes);

void UART0_IRQHandler();

/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"

#include "uart.h"
#include "stdlib.h"

#include "fsl_common.h"
#include "fsl_port.h"

#include "circbuf.h"
#include "project2.h"
#include "conversion.h"

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define SOPT5_UART0RXSRC_UART_RX      0x00u   /*!< UART0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART0 transmit data source select: UART0_TX pin */


CB_t* Rx_CB_ptr;
CB_t* Tx_CB_ptr;

extern uint8_t g_Rx_Flag ;
extern unsigned_byte g_c ;
extern character_type_stats c_stats ;

unsigned_byte head[47] ="Total  Alphabet  Misc   Numeral   Punctuation";
unsigned_byte space[3] = "   " ;
unsigned_byte space_6[6] = "      " ;
unsigned_byte space_9[9] = "         " ;
unsigned_byte newline[2] = "\r\n" ;

void CB_Rx_function(void){

CB_buffer_add_item(Rx_CB_ptr,UART0->D);

}

void CB_Tx_function(void){



if (c_stats.total == 10  ) {

   uint8_t return_val;
   uint16_t* temp_char = (uint16_t*)malloc(sizeof(uint16_t));

   UART_send_n(head,45);

   UART_send_n(newline,2);

   return_val = my_itoa((c_stats.total),(uint8_t*)temp_char, (uint32_t)10);
   UART_send_n((uint8_t*)temp_char,return_val) ;
   UART_send_n(space_6,6);

   return_val = my_itoa((c_stats.alphabet),(uint8_t*)temp_char, (uint32_t)10) ;
   UART_send_n((uint8_t*)temp_char,return_val);
   UART_send_n(space_9,9);

   return_val = my_itoa((c_stats.miscellaneous),(uint8_t*)temp_char, (uint32_t)10) ;
   UART_send_n((uint8_t*)temp_char,return_val);
   UART_send_n(space_6,6);

   return_val = my_itoa((c_stats.numeral),(uint8_t*)temp_char, (uint32_t)10);
   UART_send_n((uint8_t*)temp_char,return_val);
   UART_send_n(space_9,9);

   return_val = my_itoa((c_stats.puctuation),(uint8_t*)temp_char, (uint32_t)10);
   UART_send_n((uint8_t*)temp_char,return_val);

   UART_send_n(newline,2);
   UART_send_n(newline,2);

   //reset stats
   c_stats.alphabet = 0; c_stats.miscellaneous = 0; c_stats.numeral = 0;
   c_stats.puctuation = 0; c_stats.total = 0;
free(temp_char);
}

}

int main(void)
{

//register call back functions
 Rx_function = &CB_Rx_function;
 Tx_function = &CB_Tx_function;

 Rx_CB_ptr = (CB_t*)malloc(sizeof(CB_t));

 c_stats.alphabet = 0; c_stats.miscellaneous = 0; c_stats.numeral = 0;
 c_stats.puctuation = 0; c_stats.total = 0;

 CB_init(Rx_CB_ptr , CB_SIZE);

   UART_configure();

   PRINTF("hello world.\r\n");

   while (1)

   {

   project2(Rx_CB_ptr);

   }

}

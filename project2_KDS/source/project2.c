
#include "MKL25Z4.h"

#include "project2.h"
#include "stdint.h"
#include "stdlib.h"
#include "circbuf.h"
#include "uart.h"
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

   UART_send_n(head,47);

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



void project2(void){

	//register call back functions
	 Rx_function = &CB_Rx_function;
	 Tx_function = &CB_Tx_function;
	 Rx_CB_ptr = (CB_t*)malloc(sizeof(CB_t));


	  c_stats.alphabet = 0; c_stats.miscellaneous = 0; c_stats.numeral = 0;
	  c_stats.puctuation = 0; c_stats.total = 0;

	  CB_init(Rx_CB_ptr , CB_SIZE);

	    UART_configure();



	    while (1)

	    {

	    process(Rx_CB_ptr);

	    }


}

void process(CB_t* R_CB_ptr){



    if( !CB_is_empty(R_CB_ptr)  ) {

       unsigned_byte temp1 = 0;
	   if( CB_buffer_remove_item(R_CB_ptr,&temp1) == (CB_enum)Success  ) {


	   c_stats.total++ ;//pop the data from RX buffer


	   if( ((temp1 >= 'A')&&(temp1 <= 'Z')) || ((temp1 >= 'a')&&(temp1 <= 'z')) ) c_stats.alphabet++ ;

	   else if( ((temp1 >= '0')&&(temp1 <= '9')) ) c_stats.numeral++ ;

	   else if( temp1 == ' ' || temp1 == '!' || temp1 == '"' ||  temp1 == ',' ||
			    temp1 == '.' || temp1 == ':' || temp1 == ';' ||  temp1 == '?' ||
				temp1 == 44 ) c_stats.puctuation++ ;

	   else c_stats.miscellaneous++ ;
	   }


	}


}

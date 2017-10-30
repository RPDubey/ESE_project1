#include "project2.h"
#include "stdint.h"
#include "stdlib.h"
#include "circbuf.h"

/*******************************************************************************
@file:project2.c
@brief:function declarations for project2 functions

This file declares functions for implementing operations defined in project.h
@author:Ravi Dubey
@date:10/22/2017
*******************************************************************************/



void project2(CB_t* R_CB_ptr){



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

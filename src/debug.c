/********************************************************************************
@file:conversion.c
@brief:function declarations for debug function

This file declares function for printing data to  debug as defined in debug.h
@author:Ravi Dubey
@date:09/23/2017
********************************************************************************/
# include <stdio.h>
# include <stdint.h>
# include "debug.h"

//#define VERBOSE
void print_memory(uint8_t* start, uint32_t length){

#ifdef VERBOSE
if(start == NULL) printf("Start pointer is NULL. print_memory failed\n");
else if(length <= 0 ) printf("Invalid Length\n" );

else{

uint32_t i;


for ( i = 0; i < length; i++) {
 printf("0x%x\n", *(start + i) );
}
}
#endif

}

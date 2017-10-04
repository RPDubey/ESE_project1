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
# include "platform.h"

void print_memory(uint8_t* start, uint32_t length){

#ifdef VERBOSE
if(start == NULL) {
    #ifdef ENABLE_LOWLEVEL_FUNCTION
  printf("Start pointer is NULL. print_memory failed\n");
  #endif
}
else if(length <= 0 ){
  #ifdef ENABLE_LOWLEVEL_FUNCTION
   printf("Invalid Length\n" );
   #endif
}
else{
uint32_t i;
#ifdef ENABLE_LOWLEVEL_FUNCTION
for ( i = 0; i < length; i++) {
 printf("0x%x\n", *(start + i) );
}
#endif
}
#endif

}

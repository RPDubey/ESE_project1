/********************************************************************************
@file:conversion.c
@brief:function declarations for conversion operation functions

This file declares functions for implementing conversion operations defined in 
conversion.h
@author:Ravi Dubey
@date:09/23/2017
********************************************************************************/
# include <stdio.h>
# include <stdint.h>

uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base){};

int32_t my_atoi( uint8_t* ptr, uint8_t digits , uint32_t base){};

int8_t big_to_little32( uint32_t* data, uint32_t length){};

int8_t little_to_big32( uint32_t* data, uint32_t length){};

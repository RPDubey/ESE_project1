/********************************************************************************
@file:debug.h
@brief:An abstraction for printing data to help in debugging

This file provides definitions for functions and external variables of file
debug.c
@author:Ravi Dubey
@date:09/23/2017
********************************************************************************/


#ifndef FILE_DEBUG
#define FILE_DEBUG

# include "../../src/debug.c"

/********************************************************************************
@brief:Implements Debug printing

This function takes a pointer to a memory and prints the hex output of bytes given
the length of bytes to print.
@param:Pointer to starting Memory, Length of data to be printed in bytes.
@return: void
********************************************************************************/
void print_memory(uint8_t*, uint32_t);

#endif

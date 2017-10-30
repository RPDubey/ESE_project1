/*******************************************************************************
@file:project.h
@brief:An abstraction for operations implemented in project.c

This file provides definitions for functions and external variables of file
project2.c
@author:Ravi Dubey
@date:10/29/2017
*******************************************************************************/
#include <stdint.h>
#include "circbuf.h"
#ifndef FILE_PROJECT2
#define FILE_PROJECT2

typedef struct{
int32_t total;
int32_t numeral;
int32_t alphabet;
int32_t puctuation;
int32_t miscellaneous;

}character_type_stats;

character_type_stats c_stats ;



/*******************************************************************************
@brief:implements creating stats for incoming char
This function reads data from a circular buffer, creates stats, which are then
stored on static variable
@param:Pointer to CB from which data has to be read
@return:void
*******************************************************************************/
void project2(CB_t*);

#endif

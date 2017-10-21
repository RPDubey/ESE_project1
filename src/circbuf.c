
/*******************************************************************************
@file:circbuf.c
@brief:function declarations for implementing circular buffer operations

This file provides definitions for CB related functions declared declared in
circbuf.h
@author:Ravi Dubey
@date:10/21/2017
*******************************************************************************/


CB_enum CB_init(CB_t* CB_ptr, size_t CB_size ){

};


CB_enum CB_destroy(CB_t* CB_ptr){};


CB_enum CB_buffer_add_item( CB_t* , char* ){};


CB_enum CB_buffer_remove_item(CB_t* , char*){};


CB_enum CB_is_full(CB_t*){};


CB_enum CB_is_empty(CB_t*){};


CB_enum CB_peek(CB_t* ,size_t, char* ){};

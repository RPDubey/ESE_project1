//#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "project1.h"
#include "conversion.h"
#include "debug.h"
#include "platform.h"
#include "circbuf.h"
#include "uart.h"


#define UART

#ifdef ENABLE_LOWLEVEL_FUNCTION
#undef ENABLE_LOWLEVEL_FUNCTION
#endif

int main(void){

#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Main Starts\n" );
#endif

#ifdef PROJECT1
project1();
#endif

#ifdef PROJECT3

CB_enum return_val;
CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
if(CB_ptr == NULL) {
printf("malloc for buffer structure failed\n" );
return 0;
}


return_val = CB_init(CB_ptr, 4);
if(return_val != 0) {
print_CB_enum(return_val);
return 0;}


return_val = CB_buffer_add_item(CB_ptr,0) ;
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}

return_val = CB_buffer_add_item(CB_ptr,1) ;
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}

return_val = CB_buffer_add_item(CB_ptr,2) ;
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}

return_val = CB_buffer_add_item(CB_ptr,3) ;
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}



return_val = CB_buffer_add_item(CB_ptr,4) ;
if(return_val != 0) {
  print_CB_enum(return_val);}


unsigned_byte* stored =(unsigned_byte* )malloc(1);

return_val = CB_buffer_remove_item(CB_ptr,stored) ;
if(return_val != 0) {
  print_CB_enum(return_val);}
printf("%d",*stored);


return_val = CB_buffer_remove_item(CB_ptr , stored);
if(return_val != 0) {
  print_CB_enum(return_val);}
printf("%d",*stored);


return_val = CB_buffer_remove_item(CB_ptr , stored);
if(return_val != 0) {
  print_CB_enum(return_val);}
printf("%d",*stored);


  return_val = CB_buffer_add_item(CB_ptr,4) ;
  if(return_val != 0) {
    print_CB_enum(return_val);}

  return_val = CB_buffer_add_item(CB_ptr,5) ;
    if(return_val != 0) {
      print_CB_enum(return_val);}


return_val = CB_buffer_remove_item(CB_ptr , stored);
if(return_val != 0) {
  print_CB_enum(return_val);}
printf("%d",*stored);


return_val = CB_buffer_remove_item(CB_ptr , stored);
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}
printf("%d",*stored);



return_val = CB_destroy(CB_ptr);
if(return_val != 0) {
  print_CB_enum(return_val);
  return 0;}

#endif
#ifdef UART

uint8_t send_var = 8;

UART_configure();
UART_send(&send_var);

#endif


#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Main ends\n" );
#endif

return 0;

}

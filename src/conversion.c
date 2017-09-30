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
# include "conversion.h"

#define BYTE_3 (0xFF000000)
#define BYTE_2 (0x00FF0000)
#define BYTE_1 (0x0000FF00)
#define BYTE_0 (0x000000FF)

#define SHIFT_1BYTE (8)
#define SHIFT_2BYTE (16)
#define SHIFT_3BYTE (24)

uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base){

  if(base < 2 | base >16 ){
    printf("Invalid Base. Aborting itoa\n" );
    return -1;
  }

  if (ptr == NULL) {
    printf("Destination poiner is Null\n");
    return -1;

  }
uint64_t i = 1;
uint8_t string_length = 0;
uint8_t digit;
int8_t sign;
uint32_t decimal_rep = 0;

if(data > 0) sign = 1;
else if(data < 0) sign = -1;
data = data*sign;

while(data >0){
digit = data%10;
if(digit >= base){
  printf("Incompatible Base and data. Aborting itoa\n");
  return 0;
}

data = (data - digit)/10;
decimal_rep += digit*(i);
i = i * base;
}

decimal_rep = decimal_rep * sign;

printf("Decimal Representation %d\n", decimal_rep);

uint8_t temp;

temp = (BYTE_3 & decimal_rep)>>SHIFT_3BYTE;
if( temp != 0){
*(ptr + string_length) = temp;
string_length++;
}

temp = (BYTE_2 & decimal_rep)>>SHIFT_2BYTE;
if( temp != 0){
*(ptr + string_length)= temp;
string_length++;
}


temp = (BYTE_1 & decimal_rep)>>SHIFT_1BYTE;
if( temp != 0){
*(ptr + string_length)= temp;
string_length++;
}

temp = (BYTE_0 & decimal_rep);
if( temp != 0){
*(ptr + string_length)= temp;
string_length++;
}

*(ptr+string_length) = 0;
string_length++;

return string_length;

}

int32_t my_atoi( uint8_t* ptr, uint8_t digits , uint32_t base){

  if(base < 2 | base >16 ){
    printf("Invalid Base. Aborting atoi\n");
    return -1;
  }

  if (ptr == NULL) {
    printf("Source poiner is Null.Aborting atoi\n" );
    return -1;

  }
if (digits <= 0) {
  printf("Invalid digits. Aborting atoi\n");
  return -1;
}

int32_t number_decimal = 0;
int32_t temp = 0;
uint8_t i ;

//check for null termination of character set
if (*(ptr + digits - 1) == 0) {
  digits = digits - 1;
}
//check for overflow , ie more than 4 bytes
if(digits > 4) {
digits = 4;
printf("Character set can't fit in 32 bit int.Converting first 4 bytes\n");}


for(i = 0; i < digits; i++ ){

number_decimal = number_decimal | ( (*(ptr+i) | temp )<<(8*(digits-1 -i)) ) ;

temp = 0;

}
printf("Equivalent Decimal %d\n",number_decimal );

uint32_t quotient = number_decimal;
uint8_t  remainder;
uint16_t power = 1;
int32_t number_base = 0;

//converting to given base
while(quotient){

remainder = quotient%base;
number_base += remainder * power;//printf("%d %d\n",remainder,number_base );
quotient = (quotient - remainder)/base;
power = power*10;

}
printf("Equivalent base %d\n",number_base );
return number_base;
}

int8_t big_to_little32( uint32_t* data, uint32_t length){

if(data == NULL | length <= 0){
  printf("Invalid Arguments\n");
  return -1;
}
uint32_t i, temp1, temp2, temp3, temp4 = 0;

for(i = 0;i < length;i++){
temp1 = *(data + i) & BYTE_3>>SHIFT_3BYTE  ;
temp2 = *(data + i) & BYTE_2>>SHIFT_1BYTE  ;
temp3 = *(data + i) & BYTE_1<<SHIFT_1BYTE  ;
temp4 = *(data + i) & BYTE_0<<SHIFT_3BYTE  ;
*(data + i) = temp4 | temp3 | temp2 | temp1 ;
}
return 1;
}

int8_t little_to_big32( uint32_t* data, uint32_t length){

  if(data == NULL | length <= 0){
    printf("Invalid Arguments\n");
    return -1;
  }
  uint32_t i, temp1, temp2, temp3, temp4 = 0;

  for(i = 0;i < length;i++){
  temp1 = *(data + i) & BYTE_3>>SHIFT_3BYTE  ;
  temp2 = *(data + i) & BYTE_2>>SHIFT_1BYTE  ;
  temp3 = *(data + i) & BYTE_1<<SHIFT_1BYTE  ;
  temp4 = *(data + i) & BYTE_0<<SHIFT_3BYTE  ;
  *(data + i) = temp4 | temp3 | temp2 | temp1 ;
  }
  return 1;

}

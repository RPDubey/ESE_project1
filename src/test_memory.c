#include <cmocka.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "../include/common/memory.h"
#include "../include/common/conversion.h"
#include "../include/common/circbuf.h"
/// Unit tests for memory

static void test_memmove_null_pointer(void **state) {
  assert_non_null(my_memmove(NULL,NULL,3));
}

static void test_memmove_no_overlap(void **state) {
 uint8_t test_arr[7]={0,0,0,0,0,0,0};
  assert_ptr_equal(my_memmove(test_arr,&test_arr[4],3),&test_arr[4]);
}

static void test_memmove_overlap_src_in_dst(void **state) {
 uint8_t test_arr[7]={0,0,0,0,0,0,0};
  assert_ptr_equal(my_memmove(&test_arr[2],test_arr,4),test_arr);
}

static void test_memmove_overlap_dst_in_src(void **state) {
 uint8_t test_arr[7]={0,0,0,0,0,0,0};
  assert_ptr_equal(my_memmove(test_arr,&test_arr[2],4),&test_arr[2]);
}

static void test_memset_null_pointer(void **state) {
  assert_non_null(my_memset(NULL,3,3));
}

static void test_memset_checkset(void **state) {
  uint8_t test_arr[6] = {0,0,0,6,6,6};
  assert_memory_equal(my_memset(test_arr,3,6) ,&test_arr[3], 3);
}

static void test_memzero_null_pointer(void **state) {
  assert_non_null(my_memzero(NULL,3));
}

static void test_memzero_checkset(void **state) {
  uint8_t test_arr[6] = {1,1,1,0,0,0};
  assert_memory_equal(my_memzero(test_arr,3) ,&test_arr[3], 3);
}

static void test_reverse_null_pointer(void **state) {
  assert_non_null(my_reverse(NULL,3));
}

static void test_reverse_odd_reverse(void **state) {
  uint8_t test_arr1[5] = {1,2,3,4,5};
  uint8_t test_arr2[5] = {5,4,3,2,1};
  assert_memory_equal(my_reverse(test_arr1,5) ,test_arr2, 5);
}

static void test_reverse_even_reverse(void **state) {
  uint8_t test_arr1[6] = {1,2,3,4,5,6};
  uint8_t test_arr2[6] = {6,5,4,3,2,1};
  assert_memory_equal(my_reverse(test_arr1,6) ,test_arr2, 6);
}

static void test_reverse_characters(void **state) {
  uint8_t test_arr1[5] = {1,'a','\n',5,' '};
  uint8_t test_arr2[5] = {' ',5,'\n','a',1};
  assert_memory_equal(my_reverse(test_arr1,5) ,test_arr2, 5);
}

/// unit tests for conversion

static void test_big_to_little_null_pointer(void **state) {
  assert_int_not_equal(big_to_little32(NULL,3),-1);
}

static void test_big_to_little_valid_conversion(void **state) {

  uint32_t test_arr1[3] = {0x00000001,0x00000002,0x00000004};//big endian
  uint32_t test_arr2[3] = {0x01000000,0x02000000,0x04000000};//little endian
  assert_memory_equal(big_to_little32(test_arr1,3) ,test_arr2, 3);
}

static void test_little_to_big_null_pointer(void **state) {
  assert_int_not_equal(little_to_big32(NULL,3),-1);
}

static void test_little_to_big_valid_conversion(void **state) {
  uint32_t test_arr1[3] = {0x00000001,0x00000002,0x00000004};//big endian
  uint32_t test_arr2[3] = {0x01000000,0x02000000,0x04000000};//little endian
  assert_memory_equal(little_to_big32(test_arr2,3) ,test_arr1, 3);
}


/// unit tests for circular Buffer
static void test_cir_buf_allocate_free(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,10);
  assert_non_null(CB_ptr->buf_ptr );
  free(CB_ptr);
}

static void test_cir_buf_null_pointer(void **state) {
  assert_int_equal(CB_init(NULL,3), (CB_enum)Argument_Error );
}

static void test_cir_buf_non_initalized(void **state) {
 CB_t* CB_ptr = NULL;
  CB_init(CB_ptr,10);
  assert_non_null(CB_ptr->buf_ptr );

}

static void test_cir_buf_add_remove(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,5);
  uint8_t test_arr1[5]={0,1,2,3,4} ;
  uint8_t test_arr2[5] ={0,0,0,0,0};

  for(int i=0;i<5;i++)
  CB_buffer_add_item(CB_ptr,test_arr1[i] );

  for(int i=0;i<5;i++)
  CB_buffer_remove_item(CB_ptr,&test_arr2[i] );

  assert_memory_equal(test_arr1,test_arr2,5 );
  free(CB_ptr);

}

static void test_cir_buf_full_buffer(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,5);
  uint8_t test_arr[5] ={0,0,0,0,0};

  for(int i=0;i<5;i++)
  CB_buffer_add_item(CB_ptr,test_arr[i] );

  assert_int_equal(CB_is_full(CB_ptr), (CB_enum)Buffer_Full );
  free(CB_ptr);
}

static void test_cir_buf_empty_buffer(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,5);
  assert_int_equal(CB_is_empty(CB_ptr), (CB_enum)Buffer_Empty );
  free(CB_ptr);
}

static void test_cir_buf_wrap_add(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,3);
  uint8_t test_arr[3] ={0,1,2};
  uint8_t data = 0;

  for(int i=0;i<3;i++)
  CB_buffer_add_item(CB_ptr,test_arr[i] );

  CB_buffer_remove_item(CB_ptr,&data);

  assert_ptr_equal(CB_ptr->buf_ptr, CB_ptr->head );
  free(CB_ptr);
}

static void test_cir_buf_wrap_remove(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,3);
  uint8_t test_arr[3] ={0,1,2};
  uint8_t data = 0;

  for(int i=0;i<3;i++)
  CB_buffer_add_item(CB_ptr,test_arr[i] );

  for(int i=0;i<3;i++)
  CB_buffer_remove_item(CB_ptr,&test_arr[i] );
  assert_ptr_equal(CB_ptr->tail, CB_ptr->head );
  free(CB_ptr);
}

static void test_cir_buf_overfill(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,3);
  uint8_t test_arr[3] ={0,1,2};
  uint8_t data = 0;

  for(int i=0;i<3;i++)
  CB_buffer_add_item(CB_ptr,test_arr[i] );



  assert_int_equal(CB_buffer_add_item(CB_ptr,(uint8_t)8 ), (CB_enum)Buffer_Full );
  free(CB_ptr);
}

static void test_cir_buf_overempty(void **state) {
  CB_t* CB_ptr = (CB_t*)malloc(sizeof(CB_t));
  CB_init(CB_ptr,3);
  uint8_t data = 0;
  assert_int_equal(CB_buffer_remove_item(CB_ptr,&data ), (CB_enum)Buffer_Empty );
  free(CB_ptr);
}



int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_memmove_null_pointer),
    cmocka_unit_test(test_memmove_no_overlap),
    cmocka_unit_test(test_memmove_overlap_src_in_dst),
    cmocka_unit_test(test_memmove_overlap_dst_in_src),
    cmocka_unit_test(test_memset_null_pointer),
    cmocka_unit_test(test_memset_checkset),
    cmocka_unit_test(test_memzero_null_pointer),
    cmocka_unit_test(test_memzero_checkset),
    cmocka_unit_test(test_reverse_null_pointer),
    cmocka_unit_test(test_reverse_odd_reverse),
    cmocka_unit_test(test_reverse_even_reverse),
    cmocka_unit_test(test_reverse_characters),
    cmocka_unit_test(test_big_to_little_null_pointer),
  //  cmocka_unit_test(test_big_to_little_valid_conversion),
    cmocka_unit_test(test_little_to_big_null_pointer),
  //  cmocka_unit_test(test_little_to_big_valid_conversion),
  cmocka_unit_test(test_cir_buf_allocate_free),
  cmocka_unit_test(test_cir_buf_null_pointer),
  cmocka_unit_test(test_cir_buf_non_initalized),
  cmocka_unit_test(test_cir_buf_add_remove),
  cmocka_unit_test(test_cir_buf_full_buffer),
  cmocka_unit_test(test_cir_buf_empty_buffer),
  cmocka_unit_test(test_cir_buf_wrap_add),
  cmocka_unit_test(test_cir_buf_wrap_remove),
  cmocka_unit_test(test_cir_buf_overempty),
  cmocka_unit_test(test_cir_buf_overfill)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}

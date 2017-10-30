#include <cmocka.h>
#include <setjmp.h>

void __wrap_my_memmove(int8_t* src, uint8_t* dst, size_t length) {
  check_expected(src);
}

#include <stdio.h>


#include "memory.h"
#include "project1.h"
#include "conversion.h"
#include "debug.h"
#include "platform.h"

int main(void){
#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Main Starts\n" );
#endif

#ifdef PROJECT1
project1();
#endif

#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Main ends\n" );
#endif

return 0;

}

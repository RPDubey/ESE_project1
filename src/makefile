CC = gcc
CPPFLAGS =  -DPROJECT2# -DVERBOSE #-DKL254Z
CFLAGS = -Wall -g -o0 -std=c99 -Werror
LDFLAGS = -Xlinker -MAP=>project1.map
SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c
INCLUDES = -I../include/common/

ifeq ($(PLATFORM), HOST)
	CC = gcc
	CPPFLAGS =  -DPROJECT2# -DVERBOSE #-DKL254Z
	CFLAGS = -Wall -g -o0 -std=c99 -Werror
	LDFLAGS = -Xlinker -MAP=>project1.map
	SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c \
	 					./circbuf.c
  INCLUDES = -I../include/common/
else ifeq ($(PLATFORM) , BBB)
	CC = arm-linux-gnueabihf-gcc
	CPPFLAGS =  -DPROJECT2 #-DVERBOSE
	CFLAGS = -Wall -g -o0 -std=c99 -Werror
	LDFLAGS = -Xlinker -MAP=>project1.map
	SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c \
						./circbuf.c
  INCLUDES = -I../include/common/
else ifeq ($(PLATFORM) , KL254Z)
	CC = arm-none-eabi-gcc
	CPPFLAGS = -DKL25Z4 -DPROJECT2 #-DVERBOSE
	CFLAGS = -Wall -g -o0 -std=c99 -Werror\
          	-mcpu='cortex-m0plus' -mthumb -march=armv6-m\
           	-mfloat-abi='soft' -mfpu=fpv4-sp-d16 --specs=nosys.specs
	LDFLAGS = -Xlinker -MAP=>project1.map\
	          -L../platform -T MKL25Z128xxx4_flash.ld

	SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c\
						./circbuf.c ./uart.c\
						./startup_MKL25Z4.S ./system_MKL25Z4.c
  INCLUDES = -I../include/common/ \
	           -I../include/CMSIS/ \
						 -I../include/kl25z/
endif

####### *.I Files ########
%.i: %.c
	$(CC) -E -o $@ $^ $(CPPFLAGS) $(INCLUDES)
####### *.asm Files ########
%.asm: %.c
	$(CC) -S -o $@ $^ $(CPPFLAGS) $(INCLUDES)
####### *.o Files #######
%.o: %.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
###### compile-all #############
.PHONY: compile-all
compile-all: memory.o
memory.o: memory.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:conversion.o
conversion.o: conversion.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:debug.o
debug.o: debug.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:project1.o
project1.o: project1.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:main.o
main.o:main.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
####### build ###############
.PHONY: build
##dependency files##
build: memory.dep
memory.dep: memory.c
	$(CC) -M -o $@ $^ $(CPPFLAGS) $(INCLUDES)
build:conversion.dep
conversion.dep: conversion.c
	$(CC) -M -o $@ $^ $(CPPFLAGS) $(INCLUDES)
build:debug.dep
debug.dep: debug.c
	$(CC) -M -o $@ $^ $(CPPFLAGS) $(INCLUDES)
build:project1.dep
project1.dep: project1.c
	$(CC) -M -o $@ $^ $(CPPFLAGS) $(INCLUDES)
build:main.dep
main.dep:main.c
	$(CC) -M -o $@ $^ $(CPPFLAGS) $(INCLUDES)
##executable##
build: project1.elf
project1.elf: $(subst .c,.o,$(SOURCES))
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@
build:size_report
size_report:
	size *.o project1.elf
########build -lib###########
.PHONY: build-lib
build-lib: libproject1.a
libproject1.a: conversion.o debug.o memory.o
	ar cr libproject1.a conversion.o debug.o memory.o
####### clean ###############
.PHONY: clean
clean:
	rm *.o *.i *.asm *.map project1.elf 0 *.dep

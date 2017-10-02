INCLUDES := -I../include/common/
CFLAGS := -Wall
CPPFLAGS :=  -DPROJECT1
LDFLAGS = -Xlinker -MAP=>project1.map

ifeq ($(PLATFORM), HOST)
	CC = gcc
	SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c
else ifeq ($(PLATFORM) , BBB)
	CC = arm-linux-gnueabi-gcc
	SOURCES = ./memory.c ./main.c ./conversion.c ./debug.c ./project1.c
else ifeq ($(PLATFORM) , KL25Z)
	CC = arm-none-eabi-gcc
	SOURCES =
endif

memory.o: memory.c
	$(CC) -c -o $@ $^

conversion.o: conversion.c
	$(CC) -c -o $@ $^ $(INCLUDES)

debug.o: debug.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)

project1.o: project1.c memory.o debug.o
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)

main.o:main.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)

.PHONY: all
all: project1.elf
project1.elf: $(subst .c,.o,$(SOURCES))
	$(CC) $(LDFLAGS) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm *.o project1.elf

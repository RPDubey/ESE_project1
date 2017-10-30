################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/board.c \
../source/circbuf.c \
../source/clock_config.c \
../source/conversion.c \
../source/main.c \
../source/memory.c \
../source/nvic.c \
../source/pin_mux.c \
../source/project2.c \
../source/uart.c 

OBJS += \
./source/board.o \
./source/circbuf.o \
./source/clock_config.o \
./source/conversion.o \
./source/main.o \
./source/memory.o \
./source/nvic.o \
./source/pin_mux.o \
./source/project2.o \
./source/uart.o 

C_DEPS += \
./source/board.d \
./source/circbuf.d \
./source/clock_config.d \
./source/conversion.d \
./source/main.d \
./source/memory.d \
./source/nvic.d \
./source/pin_mux.d \
./source/project2.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DCPU_MKL25Z128VFM4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MKL25Z128VFM4_cm0plus -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



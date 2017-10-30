################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sources/board.c \
../sources/circbuf.c \
../sources/clock_config.c \
../sources/conversion.c \
../sources/main.c \
../sources/memory.c \
../sources/nvic.c \
../sources/pin_mux.c \
../sources/project2.c \
../sources/uart.c 

OBJS += \
./sources/board.o \
./sources/circbuf.o \
./sources/clock_config.o \
./sources/conversion.o \
./sources/main.o \
./sources/memory.o \
./sources/nvic.o \
./sources/pin_mux.o \
./sources/project2.o \
./sources/uart.o 

C_DEPS += \
./sources/board.d \
./sources/circbuf.d \
./sources/clock_config.d \
./sources/conversion.d \
./sources/main.d \
./sources/memory.d \
./sources/nvic.d \
./sources/pin_mux.d \
./sources/project2.d \
./sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
sources/%.o: ../sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -flto -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -I../CMSIS/Include -I../devices -I../drivers -I../sources -I../utilities -std=gnu99 -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



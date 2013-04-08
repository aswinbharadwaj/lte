################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pdcp.c \
../src/rlc.c \
../src/tp.c \
../src/udpserver.c \
../src/uea2.c 

OBJS += \
./src/pdcp.o \
./src/rlc.o \
./src/tp.o \
./src/udpserver.o \
./src/uea2.o 

C_DEPS += \
./src/pdcp.d \
./src/rlc.d \
./src/tp.d \
./src/udpserver.d \
./src/uea2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -pthread -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



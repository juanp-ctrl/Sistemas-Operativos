################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EXEC.c \
../src/Ejercicio\ 7.c 

OBJS += \
./src/EXEC.o \
./src/Ejercicio\ 7.o 

C_DEPS += \
./src/EXEC.d \
./src/Ejercicio\ 7.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Ejercicio\ 7.o: ../src/Ejercicio\ 7.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Ejercicio 7.d" -MT"src/Ejercicio\ 7.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



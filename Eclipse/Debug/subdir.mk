################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Flame.c \
../Ldr.c \
../Led.c \
../MiddleWare.c \
../Motor.c \
../Project3.c \
../Timer0_PWM.c \
../adc.c \
../gpio.c \
../lcd.c \
../lm35_sensor.c 

OBJS += \
./Buzzer.o \
./Flame.o \
./Ldr.o \
./Led.o \
./MiddleWare.o \
./Motor.o \
./Project3.o \
./Timer0_PWM.o \
./adc.o \
./gpio.o \
./lcd.o \
./lm35_sensor.o 

C_DEPS += \
./Buzzer.d \
./Flame.d \
./Ldr.d \
./Led.d \
./MiddleWare.d \
./Motor.d \
./Project3.d \
./Timer0_PWM.d \
./adc.d \
./gpio.d \
./lcd.d \
./lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Accelerometermainproject.c \
../source/PWM.c \
../source/UARTcomm.c \
../source/accelerometer.c \
../source/circularbufferqueue.c \
../source/delay.c \
../source/i2c.c \
../source/inputtrigger.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/statemachine.c \
../source/sysclock.c \
../source/test_accel.c 

C_DEPS += \
./source/Accelerometermainproject.d \
./source/PWM.d \
./source/UARTcomm.d \
./source/accelerometer.d \
./source/circularbufferqueue.d \
./source/delay.d \
./source/i2c.d \
./source/inputtrigger.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/statemachine.d \
./source/sysclock.d \
./source/test_accel.d 

OBJS += \
./source/Accelerometermainproject.o \
./source/PWM.o \
./source/UARTcomm.o \
./source/accelerometer.o \
./source/circularbufferqueue.o \
./source/delay.o \
./source/i2c.o \
./source/inputtrigger.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/statemachine.o \
./source/sysclock.o \
./source/test_accel.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=0 -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\board" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\source" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\drivers" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\CMSIS" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\utilities" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Accelerometermainproject\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Accelerometermainproject.d ./source/Accelerometermainproject.o ./source/PWM.d ./source/PWM.o ./source/UARTcomm.d ./source/UARTcomm.o ./source/accelerometer.d ./source/accelerometer.o ./source/circularbufferqueue.d ./source/circularbufferqueue.o ./source/delay.d ./source/delay.o ./source/i2c.d ./source/i2c.o ./source/inputtrigger.d ./source/inputtrigger.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/statemachine.d ./source/statemachine.o ./source/sysclock.d ./source/sysclock.o ./source/test_accel.d ./source/test_accel.o

.PHONY: clean-source


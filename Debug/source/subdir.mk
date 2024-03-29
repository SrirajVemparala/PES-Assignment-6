################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/UARTcomm.c \
../source/circularbufferqueue.c \
../source/commandprompt.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c 

C_DEPS += \
./source/UARTcomm.d \
./source/circularbufferqueue.d \
./source/commandprompt.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d 

OBJS += \
./source/UARTcomm.o \
./source/circularbufferqueue.o \
./source/commandprompt.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\BreakfastSerial\source" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\BreakfastSerial" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\BreakfastSerial\startup" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.6.0_8187\workspace\BreakfastSerial\CMSIS" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/UARTcomm.d ./source/UARTcomm.o ./source/circularbufferqueue.d ./source/circularbufferqueue.o ./source/commandprompt.d ./source/commandprompt.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sysclock.d ./source/sysclock.o

.PHONY: clean-source


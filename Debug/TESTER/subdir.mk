################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TESTER/TESTER.c 

OBJS += \
./TESTER/TESTER.o 

C_DEPS += \
./TESTER/TESTER.d 


# Each subdirectory must supply rules for building sources it contributes
TESTER/%.o TESTER/%.su TESTER/%.cyclo: ../TESTER/%.c TESTER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../isotp-c -I../TESTER -I../ECU -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TESTER

clean-TESTER:
	-$(RM) ./TESTER/TESTER.cyclo ./TESTER/TESTER.d ./TESTER/TESTER.o ./TESTER/TESTER.su

.PHONY: clean-TESTER


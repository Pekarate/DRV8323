################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/DRV8323_RS/drv8323.c \
../Core/DRV8323_RS/drv8323_io.c \
../Core/DRV8323_RS/drv8323_pwm.c \
../Core/DRV8323_RS/drv8323_spi.c 

OBJS += \
./Core/DRV8323_RS/drv8323.o \
./Core/DRV8323_RS/drv8323_io.o \
./Core/DRV8323_RS/drv8323_pwm.o \
./Core/DRV8323_RS/drv8323_spi.o 

C_DEPS += \
./Core/DRV8323_RS/drv8323.d \
./Core/DRV8323_RS/drv8323_io.d \
./Core/DRV8323_RS/drv8323_pwm.d \
./Core/DRV8323_RS/drv8323_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Core/DRV8323_RS/%.o Core/DRV8323_RS/%.su Core/DRV8323_RS/%.cyclo: ../Core/DRV8323_RS/%.c Core/DRV8323_RS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F071xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-DRV8323_RS

clean-Core-2f-DRV8323_RS:
	-$(RM) ./Core/DRV8323_RS/drv8323.cyclo ./Core/DRV8323_RS/drv8323.d ./Core/DRV8323_RS/drv8323.o ./Core/DRV8323_RS/drv8323.su ./Core/DRV8323_RS/drv8323_io.cyclo ./Core/DRV8323_RS/drv8323_io.d ./Core/DRV8323_RS/drv8323_io.o ./Core/DRV8323_RS/drv8323_io.su ./Core/DRV8323_RS/drv8323_pwm.cyclo ./Core/DRV8323_RS/drv8323_pwm.d ./Core/DRV8323_RS/drv8323_pwm.o ./Core/DRV8323_RS/drv8323_pwm.su ./Core/DRV8323_RS/drv8323_spi.cyclo ./Core/DRV8323_RS/drv8323_spi.d ./Core/DRV8323_RS/drv8323_spi.o ./Core/DRV8323_RS/drv8323_spi.su

.PHONY: clean-Core-2f-DRV8323_RS


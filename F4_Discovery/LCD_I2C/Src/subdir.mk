################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_I2C/Src/LCD_I2C.c 

OBJS += \
./LCD_I2C/Src/LCD_I2C.o 

C_DEPS += \
./LCD_I2C/Src/LCD_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_I2C/Src/%.o LCD_I2C/Src/%.su LCD_I2C/Src/%.cyclo: ../LCD_I2C/Src/%.c LCD_I2C/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F4 DISCOVERY/LCD_I2C/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LCD_I2C-2f-Src

clean-LCD_I2C-2f-Src:
	-$(RM) ./LCD_I2C/Src/LCD_I2C.cyclo ./LCD_I2C/Src/LCD_I2C.d ./LCD_I2C/Src/LCD_I2C.o ./LCD_I2C/Src/LCD_I2C.su

.PHONY: clean-LCD_I2C-2f-Src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Parser/Src/parser.c 

OBJS += \
./Parser/Src/parser.o 

C_DEPS += \
./Parser/Src/parser.d 


# Each subdirectory must supply rules for building sources it contributes
Parser/Src/%.o Parser/Src/%.su Parser/Src/%.cyclo: ../Parser/Src/%.c Parser/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F030 Board/Parser/Inc" -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F030 Board/BNO055_SensorAPI" -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F030 Board/BNO055_SensorAPI/BNO055_Port" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Parser-2f-Src

clean-Parser-2f-Src:
	-$(RM) ./Parser/Src/parser.cyclo ./Parser/Src/parser.d ./Parser/Src/parser.o ./Parser/Src/parser.su

.PHONY: clean-Parser-2f-Src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BNO055_SensorAPI/BNO055_Port/bno055_port.c 

OBJS += \
./BNO055_SensorAPI/BNO055_Port/bno055_port.o 

C_DEPS += \
./BNO055_SensorAPI/BNO055_Port/bno055_port.d 


# Each subdirectory must supply rules for building sources it contributes
BNO055_SensorAPI/BNO055_Port/%.o BNO055_SensorAPI/BNO055_Port/%.su BNO055_SensorAPI/BNO055_Port/%.cyclo: ../BNO055_SensorAPI/BNO055_Port/%.c BNO055_SensorAPI/BNO055_Port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F4 DISCOVERY/BNO055_SensorAPI" -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F4 DISCOVERY/BNO055_SensorAPI/BNO055_Port" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BNO055_SensorAPI-2f-BNO055_Port

clean-BNO055_SensorAPI-2f-BNO055_Port:
	-$(RM) ./BNO055_SensorAPI/BNO055_Port/bno055_port.cyclo ./BNO055_SensorAPI/BNO055_Port/bno055_port.d ./BNO055_SensorAPI/BNO055_Port/bno055_port.o ./BNO055_SensorAPI/BNO055_Port/bno055_port.su

.PHONY: clean-BNO055_SensorAPI-2f-BNO055_Port


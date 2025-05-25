################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BNO055_SensorAPI/bno055.c \
../BNO055_SensorAPI/bno055_support.c 

OBJS += \
./BNO055_SensorAPI/bno055.o \
./BNO055_SensorAPI/bno055_support.o 

C_DEPS += \
./BNO055_SensorAPI/bno055.d \
./BNO055_SensorAPI/bno055_support.d 


# Each subdirectory must supply rules for building sources it contributes
BNO055_SensorAPI/%.o BNO055_SensorAPI/%.su BNO055_SensorAPI/%.cyclo: ../BNO055_SensorAPI/%.c BNO055_SensorAPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F4 DISCOVERY/BNO055_SensorAPI" -I"C:/Users/Mert/STM32CubeIDE/workspace_1.15.0/NEW_WORKSPACE/Wireless Data Acquisition F4 DISCOVERY/BNO055_SensorAPI/BNO055_Port" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BNO055_SensorAPI

clean-BNO055_SensorAPI:
	-$(RM) ./BNO055_SensorAPI/bno055.cyclo ./BNO055_SensorAPI/bno055.d ./BNO055_SensorAPI/bno055.o ./BNO055_SensorAPI/bno055.su ./BNO055_SensorAPI/bno055_support.cyclo ./BNO055_SensorAPI/bno055_support.d ./BNO055_SensorAPI/bno055_support.o ./BNO055_SensorAPI/bno055_support.su

.PHONY: clean-BNO055_SensorAPI


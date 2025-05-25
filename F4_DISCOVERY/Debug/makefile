################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD_I2C/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Wireless Data Acquisition F4 DISCOVERY
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Wireless\ Data\ Acquisition\ F4\ DISCOVERY.elf \

MAP_FILES += \
Wireless\ Data\ Acquisition\ F4\ DISCOVERY.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Wireless\ Data\ Acquisition\ F4\ DISCOVERY.list \


# All Target
all: main-build

# Main-build Target
main-build: Wireless\ Data\ Acquisition\ F4\ DISCOVERY.elf secondary-outputs

# Tool invocations
Wireless\ Data\ Acquisition\ F4\ DISCOVERY.elf Wireless\ Data\ Acquisition\ F4\ DISCOVERY.map: $(OBJS) $(USER_OBJS) C:\Users\Mert\STM32CubeIDE\workspace_1.15.0\NEW_WORKSPACE\Wireless\ Data\ Acquisition\ F4\ DISCOVERY\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Wireless Data Acquisition F4 DISCOVERY.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Mert\STM32CubeIDE\workspace_1.15.0\NEW_WORKSPACE\Wireless Data Acquisition F4 DISCOVERY\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Wireless Data Acquisition F4 DISCOVERY.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Wireless\ Data\ Acquisition\ F4\ DISCOVERY.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Wireless Data Acquisition F4 DISCOVERY.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Wireless\ Data\ Acquisition\ F4\ DISCOVERY.elf Wireless\ Data\ Acquisition\ F4\ DISCOVERY.list Wireless\ Data\ Acquisition\ F4\ DISCOVERY.map Wireless\\ Data\\ Acquisition\\ F4\\ DISCOVERY.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

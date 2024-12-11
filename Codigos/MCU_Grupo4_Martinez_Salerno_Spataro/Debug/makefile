################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Firmware/subdir.mk
-include src/Drivers/17-SCTimer/subdir.mk
-include src/Drivers/16-pin_interrupt/subdir.mk
-include src/Drivers/15-hc-sr04/subdir.mk
-include src/Drivers/14-Reloj/subdir.mk
-include src/Drivers/13-MultiRateTimer/subdir.mk
-include src/Drivers/12-Puente_H/subdir.mk
-include src/Drivers/11-Teclado/subdir.mk
-include src/Drivers/10-UART/subdir.mk
-include src/Drivers/09-display_LCD/subdir.mk
-include src/Drivers/06-timer/subdir.mk
-include src/Drivers/05-swhandler/subdir.mk
-include src/Drivers/04-inputs/subdir.mk
-include src/Drivers/03-outputs/subdir.mk
-include src/Drivers/02-gpio/subdir.mk
-include src/Aplicacion/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
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


BUILD_ARTIFACT_NAME := proyecto
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: proyecto.axf

# Tool invocations
proyecto.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -Xlinker -Map="proyecto.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "proyecto_Debug.ld" -o "proyecto.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) proyecto.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "proyecto.axf"; # arm-none-eabi-objcopy -v -O binary "proyecto.axf" "proyecto.bin" ; # checksum -p LPC845 -d "proyecto.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets

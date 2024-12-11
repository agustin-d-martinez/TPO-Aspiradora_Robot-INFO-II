################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Drivers/SCTimer/SCtimer.cpp 

CPP_DEPS += \
./src/Drivers/SCTimer/SCtimer.d 

OBJS += \
./src/Drivers/SCTimer/SCtimer.o 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/SCTimer/%.o: ../src/Drivers/SCTimer/%.cpp src/Drivers/SCTimer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Aplicacion" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\14-Reloj" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Firmware" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\01-pin" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\02-gpio" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\03-outputs" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\04-inputs" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\05-swhandler" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\06-timer" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\09-display_LCD" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\10-UART" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\11-Teclado" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\12-Puente_H" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\13-MultiRateTimer" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\hc-sr04" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\pin_interrupt" -I"D:\maste\Documents\Peque\Workspace\proyecto\src\Drivers\SCTimer" -I"D:\maste\Documents\Peque\Workspace\proyecto\src" -O1 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Drivers-2f-SCTimer

clean-src-2f-Drivers-2f-SCTimer:
	-$(RM) ./src/Drivers/SCTimer/SCtimer.d ./src/Drivers/SCTimer/SCtimer.o

.PHONY: clean-src-2f-Drivers-2f-SCTimer


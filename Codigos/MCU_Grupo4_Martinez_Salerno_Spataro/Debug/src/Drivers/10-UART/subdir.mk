################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Drivers/10-UART/Uart.cpp 

OBJS += \
./src/Drivers/10-UART/Uart.o 

CPP_DEPS += \
./src/Drivers/10-UART/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/10-UART/%.o: ../src/Drivers/10-UART/%.cpp src/Drivers/10-UART/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Aplicacion" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Firmware" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\01-pin" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\02-gpio" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\03-outputs" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\04-inputs" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\05-swhandler" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\06-timer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\09-display_LCD" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\10-UART" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\11-Teclado" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\12-Puente_H" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\13-MultiRateTimer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\14-Reloj" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\15-hc-sr04" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\16-pin_interrupt" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\17-SCTimer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src" -O1 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



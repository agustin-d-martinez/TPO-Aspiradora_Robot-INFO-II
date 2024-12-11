################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Drivers/08-Display7Segmentos/10A-barrido/I4017.cpp \
../src/Drivers/08-Display7Segmentos/10A-barrido/barrido.cpp 

CPP_DEPS += \
./src/Drivers/08-Display7Segmentos/10A-barrido/I4017.d \
./src/Drivers/08-Display7Segmentos/10A-barrido/barrido.d 

OBJS += \
./src/Drivers/08-Display7Segmentos/10A-barrido/I4017.o \
./src/Drivers/08-Display7Segmentos/10A-barrido/barrido.o 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/08-Display7Segmentos/10A-barrido/%.o: ../src/Drivers/08-Display7Segmentos/10A-barrido/%.cpp src/Drivers/08-Display7Segmentos/10A-barrido/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Aplicacion" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\14-Reloj" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Firmware" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\01-pin" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\02-gpio" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\03-outputs" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\04-inputs" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\05-swhandler" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\06-timer" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\07-timers" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\08-Display7Segmentos" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\09-display_LCD" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\10-UART" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\11-Teclado" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\12-Puente_H" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\13-MultiRateTimer" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\hc-sr04" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\pin_interrupt" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\SCTimer" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\08-Display7Segmentos\10A-barrido" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\08-Display7Segmentos\10B-segmentos" -I"C:\Users\mari-ser\Desktop\MCUexpresso\proyecto\src\Drivers\08-Display7Segmentos\10C-Display" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Drivers-2f-08-2d-Display7Segmentos-2f-10A-2d-barrido

clean-src-2f-Drivers-2f-08-2d-Display7Segmentos-2f-10A-2d-barrido:
	-$(RM) ./src/Drivers/08-Display7Segmentos/10A-barrido/I4017.d ./src/Drivers/08-Display7Segmentos/10A-barrido/I4017.o ./src/Drivers/08-Display7Segmentos/10A-barrido/barrido.d ./src/Drivers/08-Display7Segmentos/10A-barrido/barrido.o

.PHONY: clean-src-2f-Drivers-2f-08-2d-Display7Segmentos-2f-10A-2d-barrido


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/Firmware/aeabi_romdiv_patch.s 

CPP_SRCS += \
../src/Firmware/MRT_config.cpp \
../src/Firmware/cr_cpp_config.cpp \
../src/Firmware/cr_startup_lpc84x.cpp \
../src/Firmware/dr_pll.cpp \
../src/Firmware/systick.cpp 

C_SRCS += \
../src/Firmware/crp.c \
../src/Firmware/mtb.c 

OBJS += \
./src/Firmware/MRT_config.o \
./src/Firmware/aeabi_romdiv_patch.o \
./src/Firmware/cr_cpp_config.o \
./src/Firmware/cr_startup_lpc84x.o \
./src/Firmware/crp.o \
./src/Firmware/dr_pll.o \
./src/Firmware/mtb.o \
./src/Firmware/systick.o 

CPP_DEPS += \
./src/Firmware/MRT_config.d \
./src/Firmware/cr_cpp_config.d \
./src/Firmware/cr_startup_lpc84x.d \
./src/Firmware/dr_pll.d \
./src/Firmware/systick.d 

C_DEPS += \
./src/Firmware/crp.d \
./src/Firmware/mtb.d 


# Each subdirectory must supply rules for building sources it contributes
src/Firmware/%.o: ../src/Firmware/%.cpp src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Aplicacion" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Firmware" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\01-pin" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\02-gpio" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\03-outputs" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\04-inputs" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\05-swhandler" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\06-timer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\09-display_LCD" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\10-UART" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\11-Teclado" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\12-Puente_H" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\13-MultiRateTimer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\14-Reloj" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\15-hc-sr04" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\16-pin_interrupt" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src\Drivers\17-SCTimer" -I"C:\Users\santi\Desktop\workspaceXD\proyecto\src" -O1 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Firmware/%.o: ../src/Firmware/%.s src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -g3 -mcpu=cortex-m0 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Firmware/%.o: ../src/Firmware/%.c src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -D__NEWLIB__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



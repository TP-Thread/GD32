################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gd32c2x1_init.c \
../src/gd32c2x1_it.c \
../src/main.c 

C_DEPS += \
./src/gd32c2x1_init.d \
./src/gd32c2x1_it.d \
./src/main.d 

OBJS += \
./src/gd32c2x1_init.o \
./src/gd32c2x1_it.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD ARM MCU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -DGD32C231 -DHXTAL_STARTUP_TIMEOUT=65535 -DIRC48M_STARTUP_TIMEOUT=1280 -DHXTAL_VALUE=25000000 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -I"..\firmware\cmsis\inc" -I"..\firmware\GD32C2x1_standard_peripheral\Include" -I"..\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/gd32c2x1_init.d ./src/gd32c2x1_init.o ./src/gd32c2x1_it.d ./src/gd32c2x1_it.o ./src/main.d ./src/main.o

.PHONY: clean-src


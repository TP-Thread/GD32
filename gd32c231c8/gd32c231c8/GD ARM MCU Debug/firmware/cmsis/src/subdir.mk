################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/cmsis/src/gd32c2x1_err_report.c \
../firmware/cmsis/src/syscalls.c \
../firmware/cmsis/src/system_gd32c2x1.c 

C_DEPS += \
./firmware/cmsis/src/gd32c2x1_err_report.d \
./firmware/cmsis/src/syscalls.d \
./firmware/cmsis/src/system_gd32c2x1.d 

OBJS += \
./firmware/cmsis/src/gd32c2x1_err_report.o \
./firmware/cmsis/src/syscalls.o \
./firmware/cmsis/src/system_gd32c2x1.o 


# Each subdirectory must supply rules for building sources it contributes
firmware/cmsis/src/%.o: ../firmware/cmsis/src/%.c firmware/cmsis/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD ARM MCU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -DGD32C231 -DHXTAL_STARTUP_TIMEOUT=65535 -DIRC48M_STARTUP_TIMEOUT=1280 -DHXTAL_VALUE=25000000 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -I"..\firmware\cmsis\inc" -I"..\firmware\GD32C2x1_standard_peripheral\Include" -I"..\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-firmware-2f-cmsis-2f-src

clean-firmware-2f-cmsis-2f-src:
	-$(RM) ./firmware/cmsis/src/gd32c2x1_err_report.d ./firmware/cmsis/src/gd32c2x1_err_report.o ./firmware/cmsis/src/syscalls.d ./firmware/cmsis/src/syscalls.o ./firmware/cmsis/src/system_gd32c2x1.d ./firmware/cmsis/src/system_gd32c2x1.o

.PHONY: clean-firmware-2f-cmsis-2f-src


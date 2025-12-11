################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_adc.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_cmp.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_crc.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dbg.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dma.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_exti.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fmc.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fwdgt.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_gpio.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_i2c.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_misc.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_pmu.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rcu.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rtc.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_spi.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_syscfg.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_timer.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_usart.c \
../firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_wwdgt.c 

C_DEPS += \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_adc.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_cmp.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_crc.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dbg.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dma.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_exti.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fmc.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fwdgt.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_gpio.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_i2c.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_misc.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_pmu.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rcu.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rtc.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_spi.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_syscfg.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_timer.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_usart.d \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_wwdgt.d 

OBJS += \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_adc.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_cmp.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_crc.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dbg.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dma.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_exti.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fmc.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fwdgt.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_gpio.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_i2c.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_misc.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_pmu.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rcu.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rtc.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_spi.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_syscfg.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_timer.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_usart.o \
./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_wwdgt.o 


# Each subdirectory must supply rules for building sources it contributes
firmware/GD32C2x1_standard_peripheral/Source/%.o: ../firmware/GD32C2x1_standard_peripheral/Source/%.c firmware/GD32C2x1_standard_peripheral/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GD ARM MCU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -DGD32C231 -DHXTAL_STARTUP_TIMEOUT=65535 -DIRC48M_STARTUP_TIMEOUT=1280 -DHXTAL_VALUE=25000000 -DGD_ECLIPSE_GCC -DUSE_STDPERIPH_DRIVER -I"..\firmware\cmsis\inc" -I"..\firmware\GD32C2x1_standard_peripheral\Include" -I"..\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -Wa,-adhlns=$@.lst   -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-firmware-2f-GD32C2x1_standard_peripheral-2f-Source

clean-firmware-2f-GD32C2x1_standard_peripheral-2f-Source:
	-$(RM) ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_adc.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_adc.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_cmp.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_cmp.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_crc.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_crc.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dbg.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dbg.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dma.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_dma.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_exti.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_exti.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fmc.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fmc.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fwdgt.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_fwdgt.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_gpio.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_gpio.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_i2c.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_i2c.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_misc.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_misc.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_pmu.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_pmu.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rcu.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rcu.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rtc.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_rtc.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_spi.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_spi.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_syscfg.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_syscfg.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_timer.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_timer.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_usart.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_usart.o ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_wwdgt.d ./firmware/GD32C2x1_standard_peripheral/Source/gd32c2x1_wwdgt.o

.PHONY: clean-firmware-2f-GD32C2x1_standard_peripheral-2f-Source


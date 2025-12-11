/*!
    \file    gd32c2x1_syscfg.c
    \brief   SYSCFG driver

    \version 2025-07-04, V2.0.1, firmware for gd32c2x1
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32c2x1_syscfg.h"

#define SYSCFG_CFG0_FMPEN_MASK               (0x01DF0000U)
#define SYSCFG_CFG0_RMP_MASK                 (0x00000018U)
#define SYSCFG_CFG1_LOCK_MASK                (0x00000003U)
#define SYSCFG_CFG2_IE_MASK                  (0x0000001FU)
#define SYSCFG_STAT_FLAG_MASK                (0x00000003U)

/*!
    \brief      reset the SYSCFG registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

#if (defined(GD32C231) || defined(GD32C221))
/*!
    \brief      enable I2C Fm+ mode (API_ID(0x0002U))
    \param[in]  syscfg_gpio
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_PB6_FMPEN: PB6 pin I2C Fm+ mode
      \arg        SYSCFG_PB7_FMPEN: PB7 pin I2C Fm+ mode
      \arg        SYSCFG_PB8_FMPEN: PB8 pin I2C Fm+ mode
      \arg        SYSCFG_PB9_FMPEN: PB9 pin I2C Fm+ mode
      \arg        SYSCFG_I2C0_FMPEN: I2C0 Fm+ mode
      \arg        SYSCFG_PA9_FMPEN:  PA9 pin I2C Fm+ mode
      \arg        SYSCFG_PA10_FMPEN: PA10 pin I2C Fm+ mode
      \arg        SYSCFG_PC14_FMPEN: PC14 pin I2C Fm+ mode
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t syscfg_gpio)
{
    SYSCFG_CFG0 |= (syscfg_gpio & SYSCFG_CFG0_FMPEN_MASK);
}

/*!
    \brief      disable I2C Fm+ mode (API_ID(0x0003U))
    \param[in]  syscfg_gpio
                only one parameters can be selected which are shown as below:
      \arg        SYSCFG_PB6_FMPEN: PB6 pin I2C Fm+ mode
      \arg        SYSCFG_PB7_FMPEN: PB7 pin I2C Fm+ mode
      \arg        SYSCFG_PB8_FMPEN: PB8 pin I2C Fm+ mode
      \arg        SYSCFG_PB9_FMPEN: PB9 pin I2C Fm+ mode
      \arg        SYSCFG_I2C0_FMPEN: I2C0 Fm+ mode
      \arg        SYSCFG_PA9_FMPEN:  PA9 pin I2C Fm+ mode
      \arg        SYSCFG_PA10_FMPEN: PA10 pin I2C Fm+ mode
      \arg        SYSCFG_PC14_FMPEN: PC14 pin I2C Fm+ mode
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t syscfg_gpio)
{

  SYSCFG_CFG0 &= (uint32_t)(~(syscfg_gpio & SYSCFG_CFG0_FMPEN_MASK));

}
#endif

/*!
    \brief      enable remap pin function for small packages (API_ID(0x0004U))
    \param[in]  remap_pin
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_CFG0_PA11_RMP : PA11 remap to PA9
      \arg        SYSCFG_CFG0_PA12_RMP : PA12 remap to PA10
    \param[out] none
    \retval     none
*/
void syscfg_pin_remap_enable(uint32_t remap_pin)
{
    SYSCFG_CFG0 |= (remap_pin & SYSCFG_CFG0_RMP_MASK);
}

/*!
    \brief      disable remap pin function for small packages (API_ID(0x0005U))
    \param[in]  remap_pin
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_CFG0_PA11_RMP : PA11 remap to PA9
      \arg        SYSCFG_CFG0_PA12_RMP : PA12 remap to PA10
    \param[out] none
    \retval     none
*/
void syscfg_pin_remap_disable(uint32_t remap_pin)
{
    SYSCFG_CFG0 &= ~(remap_pin & SYSCFG_CFG0_RMP_MASK);
}

/*!
    \brief      get the current boot mode (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     the boot mode
      \arg        SYSCFG_BOOTMODE_FLASH: boot from the main flash
      \arg        SYSCFG_BOOTMODE_SYSTEM: boot from the system flash memory
      \arg        SYSCFG_BOOTMODE_SRAM: boot from the embedded SRAM
*/
uint8_t syscfg_bootmode_get(void)
{
    /* get the bootmode */
    uint8_t temp = (uint8_t)(SYSCFG_CFG0 & 0x00000003U);

    return temp;
}

/*!
    \brief      configure the GPIO pin as EXTI Line (API_ID(0x0007U))
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C,D,F): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(GPIOAx = 0..15, GPIOBx = 0..15, GPIOCx = 0..15, GPIODx = 0..6,8,9, GPIOFx = 0,1): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch(exti_pin / EXTI_SS_JSTEP) {
        case EXTISS0:
            /* clear EXTI source line(0..3) */
            SYSCFG_EXTISS0 &= clear_exti_mask;
            /* configure EXTI soure line(0..3) */
            SYSCFG_EXTISS0 |= config_exti_mask;
            break;
        case EXTISS1:
            /* clear EXTI soure line(4..7) */
            SYSCFG_EXTISS1 &= clear_exti_mask;
            /* configure EXTI soure line(4..7) */
            SYSCFG_EXTISS1 |= config_exti_mask;
            break;
        case EXTISS2:
            /* clear EXTI soure line(8..11) */
            SYSCFG_EXTISS2 &= clear_exti_mask;
            /* configure EXTI soure line(8..11) */
            SYSCFG_EXTISS2 |= config_exti_mask;
            break;
        case EXTISS3:
            /* clear EXTI soure line(12..15) */
            SYSCFG_EXTISS3 &= clear_exti_mask;
            /* configure EXTI soure line(12..15) */
            SYSCFG_EXTISS3 |= config_exti_mask;
            break;
        default:
            break;
        }
}

#if (defined(GD32C231) || defined(GD32C221))
/*!
    \brief      enable module lockup function (function can be disabled by system reset) (API_ID(0x0008U))
    \param[in]  lockup:
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_LOCKUP_LOCK: CPU lockup signal
      \arg        SYSCFG_SRAM_LOCKUP: SRAM ECC check error lock signal
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_CFG1 |= (lockup & SYSCFG_CFG1_LOCK_MASK);
}

#endif

#if defined(GD32C211)
/*!
    \brief      enable module lockup function (function can be disabled by system reset) (API_ID(0x0008U))
    \param[in]  lockup:
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_LOCKUP_LOCK: CPU lockup signal
      \arg        SYSCFG_SRAM_LOCKUP: SRAM parity check error lock signal
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_CFG1 |= (lockup & SYSCFG_CFG1_LOCK_MASK);
}

#endif

#if (defined(GD32C231) || defined(GD32C221))
/*!
    \brief      SRAM ECC single correctable bit get (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     single correctable bit
*/
uint32_t syscfg_sram_ecc_single_correctable_bit_get(void)
{
    uint32_t error_bits;
    error_bits = (uint32_t)((SYSCFG_CFG2 & SYSCFG_ECCSERRBITS) >> 10U);
    return error_bits;
}

/*!
    \brief      SRAM ECC error address get (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     SRAM ECC error address
*/
uint32_t syscfg_sram_ecc_error_address_get(void)
{
    uint32_t addr;
    addr = (uint32_t)((SYSCFG_CFG2 & SYSCFG_ECCEADDR)>> 20U);
    return addr;
}
#endif

/*!
    \brief      set the IRQ_LATENCY value (API_ID(0x000BU))
    \param[in]  irq_latency: IRQ_LATENCY value (0x00 - 0xFF)
    \param[out] none
    \retval     none
*/
void syscfg_irq_latency_set(uint32_t irq_latency)
{
    uint32_t reg;
    reg = SYSCFG_CPU_IRQ_LAT & (~(uint32_t)SYSCFG_CPU_IRQ_LAT_IRQ_LATENCY);
    reg |= (uint32_t)(IRQ_LATENCY(irq_latency & 0xFFU));
    SYSCFG_CPU_IRQ_LAT = (uint32_t)reg;
}

#if defined(GD32C211)
/*!
    \brief      configure the GPIO pinmux as specified (API_ID(0x000CU))
    \param[in]  syscfg_pinmux_pin: specify the pinmux configuration
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_PINMUX0_PB7: Pinmux configuration 0, PB7 mapped to pin1
      \arg        SYSCFG_PINMUX0_PC14: Pinmux configuration 0, PC14 mapped to pin1
      \arg        SYSCFG_PINMUX1_PC2: Pinmux configuration 1, PC2 mapped to pin4
      \arg        SYSCFG_PINMUX1_PA0: Pinmux configuration 1, PA0 mapped to pin4
      \arg        SYSCFG_PINMUX1_PA1: Pinmux configuration 1, PA1 mapped to pin4
      \arg        SYSCFG_PINMUX1_PA2: Pinmux configuration 1, PA2 mapped to pin4
      \arg        SYSCFG_PINMUX2_PA8: Pinmux configuration 2, PA8 mapped to pin5
      \arg        SYSCFG_PINMUX2_PA11: Pinmux configuration 2, PA11 mapped to pin5
      \arg        SYSCFG_PINMUX3_PA14: Pinmux configuration 3, PA14 mapped to pin8
      \arg        SYSCFG_PINMUX3_PB6: Pinmux configuration 3, PB6 mapped to pin8
      \arg        SYSCFG_PINMUX3_PC15: Pinmux configuration 3, PC15 mapped to pin8
      \arg        SYSCFG_PINMUX4_PC2: Pinmux configuration 4, PC2 mapped to pin5
      \arg        SYSCFG_PINMUX4_PA0: Pinmux configuration 4, PA0 mapped to pin5
      \arg        SYSCFG_PINMUX5_PA4: Pinmux configuration 5, PA4 mapped to pin9
      \arg        SYSCFG_PINMUX5_PA5: Pinmux configuration 5, PA5 mapped to pin9
      \arg        SYSCFG_PINMUX6_PA7: Pinmux configuration 6, PA7 mapped to pin11
      \arg        SYSCFG_PINMUX6_PA12:Pinmux configuration 6, PA12 mapped to pin11
      \arg        SYSCFG_PINMUX7_PA8: Pinmux configuration 7, PA8 mapped to pin12
      \arg        SYSCFG_PINMUX7_PA11: Pinmux configuration 7, PA11 mapped to pin12
    \param[in]  syscfg_pin: specify the SYSCFG pin to configure
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_PIN1_SOP8: SOP8 Pin1 configuration
      \arg        SYSCFG_PIN4_SOP8: SOP8 Pin4 configuration
      \arg        SYSCFG_PIN5_SOP8: SOP8 Pin5 configuration
      \arg        SYSCFG_PIN8_SOP8: SOP8 Pin8 configuration
      \arg        SYSCFG_PIN5_TSSOP16: TSSOP16 Pin5 configuration
      \arg        SYSCFG_PIN9_TSSOP16: TSSOP16 Pin9 configuration
      \arg        SYSCFG_PIN11_TSSOP16: TSSOP16 Pin11 configuration
      \arg        SYSCFG_PIN12_TSSOP16: TSSOP16 Pin12 configuration
    \param[out] none
    \retval     none
*/

void syscfg_pinmux_config(syscfg_pinmux_enum syscfg_pinmux_pin, syscfg_pin_enum syscfg_pin)
{
    uint32_t reg;
    uint32_t mask;

    switch (syscfg_pin) {
        case SYSCFG_PIN1_SOP8:
            mask = SYSCFG_CFG3_PINMUX0;
            break;
        case SYSCFG_PIN4_SOP8:
            mask = SYSCFG_CFG3_PINMUX1;
            break;
        case SYSCFG_PIN5_SOP8:
            mask = SYSCFG_CFG3_PINMUX2;
            break;
        case SYSCFG_PIN8_SOP8:
            mask = SYSCFG_CFG3_PINMUX3;
            break;
        case SYSCFG_PIN5_TSSOP16:
            mask = SYSCFG_CFG3_PINMUX4;
            break;
        case SYSCFG_PIN9_TSSOP16:
            mask = SYSCFG_CFG3_PINMUX5;
            break;
        case SYSCFG_PIN11_TSSOP16:
            mask = SYSCFG_CFG3_PINMUX6;
            break;
        case SYSCFG_PIN12_TSSOP16:
            mask = SYSCFG_CFG3_PINMUX7;
            break;
        default:
            return;
    }
    reg = SYSCFG_CFG3 & (~mask);
    reg |= (uint32_t)(syscfg_pinmux_pin);
    SYSCFG_CFG3 = reg;
}
#endif

/*!
    \brief      interrupt enable (API_ID(0x000DU))
    \param[in]  interrupt: 
                one or more parameter can be selected which is shown as below:
      \arg        SYSCFG_CFG2_SRAM_PARITY_IE : SRAM parity check error interrup enable (for GD32C211)
      \arg        SYSCFG_CFG2_LXTALCSS_IE: LXTAL clock stuck interrupt enable
      \arg        SYSCFG_CFG2_HXTALCSS_IE: HXTAL clock stuck interrupt enable (for GD32C231 / GD32C221)
      \arg        SYSCFG_CFG2_ECCMEIE: Multi-bits (two bits) non-correction error NMI interrupt enable (for GD32C231 / GD32C221)
      \arg        SYSCFG_CFG2_ECCSEIE: Single bit correction error interrupt enable (for GD32C231 / GD32C221)
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_enable(uint32_t interrupt)
{
    SYSCFG_CFG2 |= (interrupt & SYSCFG_CFG2_IE_MASK);
}

/*!
    \brief      interrupt disable (API_ID(0x000EU))
    \param[in]  interrupt: 
                one or more parameter can be selected which is shown as below:
      \arg        SYSCFG_CFG2_LXTALCSS_IE: LXTAL clock stuck interrupt enable
      \arg        SYSCFG_CFG2_HXTALCSS_IE: HXTAL clock stuck interrupt enable
      \arg        SYSCFG_CFG2_ECCMEIE: Multi-bits (two bits) non-correction error NMI interrupt disable (for GD32C231 / GD32C221)
      \arg        SYSCFG_CFG2_ECCSEIE: Single bit correction error interrupt disable (for GD32C231 / GD32C221)
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_disable(uint32_t interrupt)
{
    SYSCFG_CFG2 &= ~(interrupt & SYSCFG_CFG2_IE_MASK);
}

#if (defined(GD32C231) || defined(GD32C221))
/*!
    \brief      get SYSCFG flag state (API_ID(0x000F))
    \param[in]  flag: SYSCFG flags
                one or more parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_ECCME: SRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE: SRAM single bit correction event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_interrupt_flag_get(uint32_t flag)
{
    FlagStatus interrupt_flag;

    /* get flag and interrupt enable state */
    if( 0U != (SYSCFG_STAT & (flag & SYSCFG_STAT_FLAG_MASK))) {
        interrupt_flag = SET;
    } else {
        interrupt_flag = RESET;
    }

    return interrupt_flag;
}

/*!
    \brief      clear SYSCFG flag state (API_ID(0x0010))
    \param[in]  flag: SYSCFG flags
                one or more parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_ECCME: SRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE: SRAM single bit correction event flag
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_flag_clear(uint32_t flag)
{
    SYSCFG_STAT = (flag & SYSCFG_STAT_FLAG_MASK);
}
#endif

#if defined(GD32C211)
/*!
    \brief      get SYSCFG flag state (API_ID(0x000F))
    \param[in]  flag: SYSCFG flags
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_PARITY_ERR: SRAM parity check error flag

    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_flag_get(uint32_t flag)
{
    FlagStatus interrupt_flag = RESET;

    /* get flag and interrupt enable state */
    if( 0U != (SYSCFG_CFG1 & (flag & SYSCFG_FLAG_PARITY_ERR))) {
        interrupt_flag = SET;
    } else {
        interrupt_flag = RESET;
    }

    return interrupt_flag;
}

/*!
    \brief      clear SYSCFG flag state (API_ID(0x0010))
    \param[in]  flag: SYSCFG flags
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_PARITY_ERR: SRAM parity check error flag
    \param[out] none
    \retval     none
*/
void syscfg_flag_clear(uint32_t flag)
{
    SYSCFG_CFG1 = (flag & SYSCFG_FLAG_PARITY_ERR);
}
#endif
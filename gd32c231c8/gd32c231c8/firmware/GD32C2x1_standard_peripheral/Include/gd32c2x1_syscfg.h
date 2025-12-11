/*!
    \file    gd32c2x1_syscfg.h
    \brief   definitions for the SYSCFG

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

#ifndef GD32C2X1_SYSCFG_H
#define GD32C2X1_SYSCFG_H

#include "gd32c2x1.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE

/* registers definitions */
#define SYSCFG_CFG0                         REG32(SYSCFG + 0x00U)                       /*!< system configuration register 0 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x08U)                       /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0CU)                       /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x10U)                       /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x14U)                       /*!< EXTI sources selection register 3 */
#define SYSCFG_CFG1                         REG32(SYSCFG + 0x18U)                       /*!< System configuration register 1 */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_STAT                         REG32(SYSCFG + 0x1CU)                       /*!< SYSCFG STAT register */
#endif
#define SYSCFG_CFG2                         REG32(SYSCFG + 0x28U)                       /*!< System configuration register 2 */
#if (defined(GD32C211))
#define SYSCFG_CFG3                         REG32(SYSCFG + 0x3CU)                       /*!< System configuration register 2 */
#endif
#define SYSCFG_CPU_IRQ_LAT                  REG32(SYSCFG + 0x100U)                      /*!< IRQ latency register */
#define SYSCFG_TIMERCFG0(syscfg_timerx)     REG32(SYSCFG + 0x110U + (syscfg_timerx)*8U)  /*!< TIMERx configuration register0 */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     REG32(SYSCFG + 0x114U + (syscfg_timerx)*8U)  /*!< TIMERx configuration register1 */
#define SYSCFG_TIMER0CFG0                   REG32(SYSCFG + 0x110U)                      /*!< TIMER0 configuration register 0 */
#define SYSCFG_TIMER0CFG1                   REG32(SYSCFG + 0x114U)                      /*!< TIMER0 configuration register 1 */
#define SYSCFG_TIMER2CFG0                   REG32(SYSCFG + 0x118U)                      /*!< TIMER2 configuration register 0 */
#define SYSCFG_TIMER2CFG1                   REG32(SYSCFG + 0x11CU)                      /*!< TIMER2 configuration register 1 */

/* SYSCFG_CFG0 bits definitions */
#define SYSCFG_CFG0_BOOT_MODE               BITS(0,1)                                   /*!< SYSCFG memory remap config */
#define SYSCFG_CFG0_PA11_RMP                BIT(3)                                      /*!< PA11 remapping */
#define SYSCFG_CFG0_PA12_RMP                BIT(4)                                      /*!< PA12 remapping */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_CFG0_PB6_FMPEN               BIT(16)                                     /*!< I2C Fm+ mode on PB6 pin enable */
#define SYSCFG_CFG0_PB7_FMPEN               BIT(17)                                     /*!< I2C Fm+ mode on PB7 pin enable */
#define SYSCFG_CFG0_PB8_FMPEN               BIT(18)                                     /*!< I2C Fm+ mode on PB8 pin enable */
#define SYSCFG_CFG0_PB9_FMPEN               BIT(19)                                     /*!< I2C Fm+ mode on PB9 pin enable */
#define SYSCFG_CFG0_I2C0_FMPEN              BIT(20)                                     /*!< Fast Mode Plus (FM+) enable for I2C0  */
#define SYSCFG_CFG0_PA9_FMPEN               BIT(22)                                     /*!< I2C Fm+ mode on PA9 pin enable */
#define SYSCFG_CFG0_PA10_FMPEN              BIT(23)                                     /*!< I2C Fm+ mode on PA10 pin enable */
#define SYSCFG_CFG0_PC14_FMPEN              BIT(24)                                     /*!< I2C Fm+ mode on PC14 pin enable */
#endif

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,1)                                   /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,5)                                   /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,9)                                   /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,13)                                 /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BIT(0)                                      /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BIT(4)                                      /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,9)                                   /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,13)                                 /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BIT(0)                                      /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BIT(4)                                      /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BIT(8)                                      /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BIT(12)                                     /*!< EXTI 11 configuration */
                                                                                  
/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BIT(0)                                      /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,5)                                   /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,9)                                   /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,13)                                 /*!< EXTI 15 configuration */

/* SYSCFG_CFG1 bits definitions */
#define SYSCFG_CFG1_LOCKUP_LOCK             BIT(0)                                      /*!< Cortex-M23 LOCKUP output lock */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_CFG1_SRAM_ECC_LOCK           BIT(1)                                      /*!< SRAM ecc check error lock */
#endif
#if defined(GD32C211)
#define SYSCFG_CFG1_SRAM_LOCK               BIT(1)                                      /*!< SRAM check error lock */
#define SYSCFG_CFG1_SRAM_PARITY_ERR         BIT(8)                                      /*!< SRAM parity check error flag */
#endif

#if (defined(GD32C231) || defined(GD32C221))
/* SYSCFG_STAT bits definitions */
#define SYSCFG_STAT_ECCMEIF                 BIT(0)                                      /*!< SRAM two bits non-correction event flag */ 
#define SYSCFG_STAT_ECCSEIF                 BIT(1)                                      /*!< SRAM single bit correction event flag */
#endif

/* SYSCFG_CFG2 bits definitions */
#if (defined(GD32C211))
#define SYSCFG_CFG2_SRAM_PARITY_IE          BIT(0)                                      /*!< SRAM parity check error interrup enable */
#endif
#define SYSCFG_CFG2_LXTALCSS_IE             BIT(1)                                      /*!< LXTAL clock stuck interrupt enable */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_CFG2_HXTALCSS_IE             BIT(2)                                      /*!< HXTAL clock stuck interrupt enable */
#define SYSCFG_CFG2_ECCMEIE                 BIT(3)                                      /*!< Multi-bits (two bits) non-correction error NMI interrupt enable */
#define SYSCFG_CFG2_ECCSEIE                 BIT(4)                                      /*!< Single bit correction error interrupt enable */
#define SYSCFG_ECCSERRBITS                  BITS(10,15)                                 /*!< Indicates the error bit */
#define SYSCFG_ECCEADDR                     BITS(20,31)                                 /*!< Indicates the last ECC event on SRAM occurred */
#endif

#if (defined(GD32C211))
/* SYSCFG_CFG3 bits definitions */
#define SYSCFG_CFG3_PINMUX0                 BITS(1,0)                                   /*!< Pinmux0 is used for SOP8 pin1 */ 
#define SYSCFG_CFG3_PINMUX1                 BITS(3,2)                                   /*!< Pinmux1 is used for SOP8 pin4 */ 
#define SYSCFG_CFG3_PINMUX2                 BITS(5,4)                                   /*!< Pinmux2 is used for SOP8 pin5 */
#define SYSCFG_CFG3_PINMUX3                 BITS(7,6)                                   /*!< Pinmux3 is used for SOP8 pin8 */
#define SYSCFG_CFG3_PINMUX4                 BITS(8,9)                                   /*!< Pinmux4 is used for TSSOP16 pin5 */ 
#define SYSCFG_CFG3_PINMUX5                 BITS(10,11)                                 /*!< Pinmux5 is used for TSSOP16 pin9 */ 
#define SYSCFG_CFG3_PINMUX6                 BITS(12,13)                                 /*!< Pinmux6 is used for TSSOP16 pin11 */
#define SYSCFG_CFG3_PINMUX7                 BITS(14,15)                                 /*!< Pinmux7 is used for TSSOP16 pin12 */
#endif

/* SYSCFG_CPU_IRQ_LAT bits definitions */
#define SYSCFG_CPU_IRQ_LAT_IRQ_LATENCY      BITS(0,7)                                   /*!< IRQ_LATENCY specifies the minimum number of cycles between an interrupt */

/* SYSCFG_TIMERxCFG bits definitions */
#define SYSCFG_TSCFG0                       BITS(0,2)                                   /*!< Quadrature decoder mode 0 configuration */
#define SYSCFG_TSCFG1                       BITS(4,6)                                   /*!< Quadrature decoder mode 1 configuration */
#define SYSCFG_TSCFG2                       BITS(8,10)                                  /*!< Quadrature decoder mode 2 configuration */
#define SYSCFG_TSCFG3                       BITS(12,14)                                 /*!< Restart mode configuration */
#define SYSCFG_TSCFG4                       BITS(16,18)                                 /*!< Pause mode configuration */
#define SYSCFG_TSCFG5                       BITS(20,22)                                 /*!< Event mode configuration */
#define SYSCFG_TSCFG6                       BITS(24,26)                                 /*!< External clock mode 0 configuration */
#define SYSCFG_TSCFG7                       BITS(28,30)                                 /*!< Restart event configuration */
#define SYSCFG_TSCFG8                       BITS(0,2)                                   /*!< Internal trigger input source configuration */

/* constants definitions */
/* boot mode definitions */
#define SYSCFG_BOOTMODE_FLASH               ((uint8_t)0x00U)                            /*!< boot from main flash */
#define SYSCFG_BOOTMODE_SYSTEM              ((uint8_t)0x01U)                            /*!< boot from system flash memory */
#define SYSCFG_BOOTMODE_SRAM                ((uint8_t)0x03U)                            /*!< boot from embedded SRAM */

/* EXTI source select definition */
#define EXTISS0                             ((uint8_t)0x00U)                            /*!< EXTI source select register 0 */
#define EXTISS1                             ((uint8_t)0x01U)                            /*!< EXTI source select register 1 */
#define EXTISS2                             ((uint8_t)0x02U)                            /*!< EXTI source select register 2 */
#define EXTISS3                             ((uint8_t)0x03U)                            /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                                   /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))                          /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)                            /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)                            /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)                            /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                   ((uint8_t)0x03U)                            /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)                            /*!< EXTI GPIOF configuration */

/* EXTI pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)                            /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)                            /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)                            /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)                            /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)                            /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)                            /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)                            /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)                            /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)                            /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)                            /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)                            /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)                            /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)                            /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)                            /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)                            /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)                            /*!< EXTI GPIO pin15 configuration */

/* SYSCFG_CPU_IRQ_LAT register IRQ_LATENCY value */
#define IRQ_LATENCY(regval)                (BITS(0,7) & ((uint32_t)(regval) << 0U))     /*!< write value to IRQ_LATENCY bits field */

/* SYSCFG_CFG3 register pinmux bits definitions*/
#define SYSCFG_CFG3_PIN1_SOP8(regval)        (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define SYSCFG_CFG3_PIN4_SOP8(regval)        (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define SYSCFG_CFG3_PIN5_SOP8(regval)        (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define SYSCFG_CFG3_PIN8_SOP8(regval)        (BITS(6,7) & ((uint32_t)(regval) << 6U))
#define SYSCFG_CFG3_PIN5_TSSOP16(regval)     (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define SYSCFG_CFG3_PIN9_TSSOP16(regval)     (BITS(10,11) & ((uint32_t)(regval) << 10U))
#define SYSCFG_CFG3_PIN11_TSSOP16(regval)    (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define SYSCFG_CFG3_PIN12_TSSOP16(regval)    (BITS(14,15) & ((uint32_t)(regval) << 13U))

#if defined(GD32C211)
/* Pinmux definitions */
typedef enum {
    SYSCFG_PINMUX0_PB7 = SYSCFG_CFG3_PIN1_SOP8(0),   /*!< Pinmux configuration 0: PB7 mapped to pin1*/
    SYSCFG_PINMUX0_PC14 = SYSCFG_CFG3_PIN1_SOP8(1),  /*!< Pinmux configuration 0: PC14 mapped to pin1*/

    SYSCFG_PINMUX1_PC2 = SYSCFG_CFG3_PIN4_SOP8(0),   /*!< Pinmux configuration 1: PC2 mapped to pin4*/
    SYSCFG_PINMUX1_PA0 = SYSCFG_CFG3_PIN4_SOP8(1),   /*!< Pinmux configuration 1: PA0 mapped to pin4*/
    SYSCFG_PINMUX1_PA1 = SYSCFG_CFG3_PIN4_SOP8(2),   /*!< Pinmux configuration 1: PA1 mapped to pin4*/
    SYSCFG_PINMUX1_PA2 = SYSCFG_CFG3_PIN4_SOP8(3),   /*!< Pinmux configuration 1: PA2 mapped to pin4*/

    SYSCFG_PINMUX2_PA8 = SYSCFG_CFG3_PIN5_SOP8(0),   /*!< Pinmux configuration 2: PA8 mapped to pin5*/
    SYSCFG_PINMUX2_PA11 = SYSCFG_CFG3_PIN5_SOP8(1),  /*!< Pinmux configuration 2: PA11 mapped to pin5*/

    SYSCFG_PINMUX3_PA14 = SYSCFG_CFG3_PIN8_SOP8(0),  /*!< Pinmux configuration 3: PA14 mapped to pin8*/
    SYSCFG_PINMUX3_PB6 = SYSCFG_CFG3_PIN8_SOP8(1),   /*!< Pinmux configuration 3: PB6 mapped to pin8*/
    SYSCFG_PINMUX3_PC15 = SYSCFG_CFG3_PIN8_SOP8(2),  /*!< Pinmux configuration 3: PC15 mapped to pin8*/
    
    SYSCFG_PINMUX4_PC2 = SYSCFG_CFG3_PIN5_TSSOP16(0),   /*!< Pinmux configuration 4: PC2 mapped to pin5*/
    SYSCFG_PINMUX4_PA0 = SYSCFG_CFG3_PIN5_TSSOP16(1),   /*!< Pinmux configuration 4: PA0 mapped to pin5*/
    
    SYSCFG_PINMUX5_PA4 = SYSCFG_CFG3_PIN9_TSSOP16(0),   /*!< Pinmux configuration 5: PA4 mapped to pin9*/
    SYSCFG_PINMUX5_PA5 = SYSCFG_CFG3_PIN9_TSSOP16(1),   /*!< Pinmux configuration 5: PA5 mapped to pin9*/
    
    SYSCFG_PINMUX6_PA7 = SYSCFG_CFG3_PIN11_TSSOP16(0),  /*!< Pinmux configuration 6: PA7 mapped to pin11*/
    SYSCFG_PINMUX6_PA12 = SYSCFG_CFG3_PIN11_TSSOP16(1), /*!< Pinmux configuration 6: PA12 mapped to pin11*/
    
    SYSCFG_PINMUX7_PA8 = SYSCFG_CFG3_PIN12_TSSOP16(0),  /*!< Pinmux configuration 7: PA8 mapped to pin12*/
    SYSCFG_PINMUX7_PA11 = SYSCFG_CFG3_PIN12_TSSOP16(1)  /*!< Pinmux configuration 7: PA11 mapped to pin12*/
} syscfg_pinmux_enum;

typedef enum {
    SYSCFG_PIN1_SOP8 = 0U,   /*!< SOP8_Pin1 */
    SYSCFG_PIN4_SOP8,        /*!< SOP8_Pin4 */
    SYSCFG_PIN5_SOP8,        /*!< SOP8_Pin5 */
    SYSCFG_PIN8_SOP8,        /*!< SOP8_Pin8 */
    SYSCFG_PIN5_TSSOP16,     /*!< TSSOP16_Pin5 */
    SYSCFG_PIN9_TSSOP16,     /*!< TSSOP16_Pin9 */
    SYSCFG_PIN11_TSSOP16,    /*!< TSSOP16_Pin11 */
    SYSCFG_PIN12_TSSOP16     /*!< TSSOP16_Pin12 */
} syscfg_pin_enum;
#endif

#define SYSCFG_TIMER0                       ((uint8_t)0x00U)
#define SYSCFG_TIMER2                       ((uint8_t)0x01U)

/* Quadrature decoder mode configuration bits definitions */
#define TIMER_DECODER_MODE_DISABLE          ((uint8_t)0x00U)                            /*!< Quadrature decoder mode disable */
#define TIMER_COUNT_CI0FE0_EDGE             (SYSCFG_TSCFG0 << 0U)                       /*!< The counter counts on CI0FE0 edge, while the direction depends on CI1FE1 level */
#define TIMER_COUNT_CI1FE1_EDGE             (SYSCFG_TSCFG1 << 4U)                       /*!< The counter counts on CI1FE1 edge, while the direction depends on CI0FE0 level */
#define TIMER_COUNT_CI0FE0_CI1FE1_EDGE      (SYSCFG_TSCFG2 << 8U)                       /*!< The counter counts on both CI0FE0 and CI1FE1 edge, while the direction depends on each other */

/* Restart mode configuration bits definitions */
#define SYSCFG_TIMER_RESTART_MODE_CONFIG(regval)   (SYSCFG_TSCFG3 & ((uint32_t)(regval) << 12U))
#define TIMER_RESTART_MODE_DISABLE          SYSCFG_TIMER_RESTART_MODE_CONFIG(0)                            /*!< Restart mode disable */
#define TIMER_RESTART_MODE_TRIGGER_ITI0     SYSCFG_TIMER_RESTART_MODE_CONFIG(1)                            /*!< Internal trigger input 0 */
#define TIMER_RESTART_MODE_TRIGGER_ITI2     SYSCFG_TIMER_RESTART_MODE_CONFIG(2)                            /*!< Internal trigger input 2 */
#define TIMER_RESTART_MODE_TRIGGER_ITI3     SYSCFG_TIMER_RESTART_MODE_CONFIG(3)                            /*!< Internal trigger input 3 */
#define TIMER_RESTART_MODE_TRIGGER_CI0F_ED  SYSCFG_TIMER_RESTART_MODE_CONFIG(4)                            /*!< CI0 edge flag */
#define TIMER_RESTART_MODE_TRIGGER_CI0FE0   SYSCFG_TIMER_RESTART_MODE_CONFIG(5)                            /*!< The filtered output of channel 0 input */
#define TIMER_RESTART_MODE_TRIGGER_CI1FE1   SYSCFG_TIMER_RESTART_MODE_CONFIG(6)                            /*!< The filtered output of channel 1 input */
#define TIMER_RESTART_MODE_TRIGGER_ETIFP    SYSCFG_TIMER_RESTART_MODE_CONFIG(7)                            /*!< The filtered output of external trigger input */

/* Pause mode configuration bits definitions */
#define SYSCFG_TIMER_PAUSE_MODE_CONFIG(regval)     (SYSCFG_TSCFG4 & ((uint32_t)(regval) << 16))
#define TIMER_PAUSE_MODE_DISABLE            SYSCFG_TIMER_PAUSE_MODE_CONFIG(0)                              /*!< Pause mode disable */
#define TIMER_PAUSE_MODE_TRIGGER_ITI0       SYSCFG_TIMER_PAUSE_MODE_CONFIG(1)                              /*!< Internal trigger input 0 */
#define TIMER_PAUSE_MODE_TRIGGER_ITI2       SYSCFG_TIMER_PAUSE_MODE_CONFIG(2)                              /*!< Internal trigger input 2 */
#define TIMER_PAUSE_MODE_TRIGGER_ITI3       SYSCFG_TIMER_PAUSE_MODE_CONFIG(3)                              /*!< Internal trigger input 3 */
#define TIMER_PAUSE_MODE_TRIGGER_CI0F_ED    SYSCFG_TIMER_PAUSE_MODE_CONFIG(4)                              /*!< CI0 edge flag */
#define TIMER_PAUSE_MODE_TRIGGER_CI0FE0     SYSCFG_TIMER_PAUSE_MODE_CONFIG(5)                              /*!< The filtered output of channel 0 input */
#define TIMER_PAUSE_MODE_TRIGGER_CI1FE1     SYSCFG_TIMER_PAUSE_MODE_CONFIG(6)                              /*!< The filtered output of channel 1 input */
#define TIMER_PAUSE_MODE_TRIGGER_ETIFP      SYSCFG_TIMER_PAUSE_MODE_CONFIG(7)                              /*!< The filtered output of external trigger input */

/* Event mode configuration bits definitions */
#define SYSCFG_TIMER_EVENT_MODE_CONFIG(regval)     (SYSCFG_TSCFG5 & ((uint32_t)(regval) << 20))
#define TIMER_EVENT_MODE_DISABLE            SYSCFG_TIMER_EVENT_MODE_CONFIG(0)                              /*!< Event mode disable */
#define TIMER_EVENT_MODE_TRIGGER_ITI0       SYSCFG_TIMER_EVENT_MODE_CONFIG(1)                              /*!< Internal trigger input 0 */
#define TIMER_EVENT_MODE_TRIGGER_ITI2       SYSCFG_TIMER_EVENT_MODE_CONFIG(2)                              /*!< Internal trigger input 2 */
#define TIMER_EVENT_MODE_TRIGGER_ITI3       SYSCFG_TIMER_EVENT_MODE_CONFIG(3)                              /*!< Internal trigger input 3 */
#define TIMER_EVENT_MODE_TRIGGER_CI0F_ED    SYSCFG_TIMER_EVENT_MODE_CONFIG(4)                              /*!< CI0 edge flag */
#define TIMER_EVENT_MODE_TRIGGER_CI0FE0     SYSCFG_TIMER_EVENT_MODE_CONFIG(5)                              /*!< The filtered output of channel 0 input */
#define TIMER_EVENT_MODE_TRIGGER_CI1FE1     SYSCFG_TIMER_EVENT_MODE_CONFIG(6)                              /*!< The filtered output of channel 1 input */
#define TIMER_EVENT_MODE_TRIGGER_ETIFP      SYSCFG_TIMER_EVENT_MODE_CONFIG(7)                              /*!< The filtered output of external trigger input */

/* External clock mode 0 configuration bits definitions */
#define SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(regval)     (SYSCFG_TSCFG6 & ((uint32_t)(regval) << 24))
#define TIMER_EXT_CLOCK_MODE0_DISABLE           SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(0)                     /*!< External clock mode 0 disable */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_ITI0       SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(1)                     /*!< Internal trigger input 0 */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_ITI2       SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(2)                     /*!< Internal trigger input 2 */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_ITI3       SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(3)                     /*!< Internal trigger input 3 */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_CI0F_ED    SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(4)                     /*!< CI0 edge flag */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_CI0FE0     SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(5)                     /*!< The filtered output of channel 0 input */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_CI1FE1     SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(6)                     /*!< The filtered output of channel 1 input */
#define TIMER_EXT_CLOCK_MODE0_SOURCE_ETIFP      SYSCFG_TIMER_EXT_CLOCK_MODE0_CONFIG(7)                     /*!< The filtered output of external trigger input */

/* Channel restart event configuration bits definitions */
#define SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(regval)     (SYSCFG_TSCFG7 & ((uint32_t)(regval) << 28))
#define TIMER_CHANNEL_INPUT_SOURCE_DIS          SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(0)                /*!< Restart + event mode disable */
#define TIMER_CHANNEL_INPUT_SOURCE_ITI0         SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(1)                /*!< Internal trigger input 0 */
#define TIMER_CHANNEL_INPUT_SOURCE_ITI2         SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(2)                /*!< Internal trigger input 2 */
#define TIMER_CHANNEL_INPUT_SOURCE_ITI3         SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(3)                /*!< Internal trigger input 3 */
#define TIMER_CHANNEL_INPUT_SOURCE_CI0F_ED      SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(4)                /*!< CI0 edge flag */
#define TIMER_CHANNEL_INPUT_SOURCE_CI0FE0       SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(5)                /*!< The filtered output of channel 0 input */
#define TIMER_CHANNEL_INPUT_SOURCE_CI1FE1       SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(6)                /*!< The filtered output of channel 1 input  */
#define TIMER_CHANNEL_INPUT_SOURCE_ETIFP        SYSCFG_TIMER_CHANNEL_INPUT_SOURCE_CONFIG(7)                /*!< The filtered output of external trigger input */

/* Internal trigger input source configuration bits definitions */
#define SYSCFG_TIMER_TRIG_INPUT_SOURCE_CONFIG(regval)       (SYSCFG_TSCFG8 & ((uint32_t)(regval) << 0))
#define TIMER_TRIG_INPUT_SOURCE_ITI0            SYSCFG_TIMER_TRIG_INPUT_SOURCE_CONFIG(1)                   /*!< Internal trigger input 0 */
#define TIMER_TRIG_INPUT_SOURCE_ITI2            SYSCFG_TIMER_TRIG_INPUT_SOURCE_CONFIG(3)                   /*!< Internal trigger input 2 */
#define TIMER_TRIG_INPUT_SOURCE_ITI3            SYSCFG_TIMER_TRIG_INPUT_SOURCE_CONFIG(4)                   /*!< Internal trigger input 3 */
#define TIMER_TRIG_INPUT_SOURCE_CI0F_ED         SYSCFG_TIMER_TRIG_INPUT_SOURCE_CONFIG(5)                   /*!< CI0 edge flag */

#if (defined(GD32C231) || defined(GD32C221))
/* SYSCFG pin I2C Fm+ mode */
#define SYSCFG_PB6_FMPEN                        SYSCFG_CFG0_PB6_FMPEN                                      /*!< I2C Fm+ mode on PB6 pin enable */
#define SYSCFG_PB7_FMPEN                        SYSCFG_CFG0_PB7_FMPEN                                      /*!< I2C Fm+ mode on PB7 pin enable */
#define SYSCFG_PB8_FMPEN                        SYSCFG_CFG0_PB8_FMPEN                                      /*!< I2C Fm+ mode on PB8 pin enable */
#define SYSCFG_PB9_FMPEN                        SYSCFG_CFG0_PB9_FMPEN                                      /*!< I2C Fm+ mode on PB9 pin enable */
#define SYSCFG_I2C0_FMPEN                       SYSCFG_CFG0_I2C0_FMPEN                                     /*!< Fast Mode Plus (FM+) enable for I2C0  */
#define SYSCFG_PA9_FMPEN                        SYSCFG_CFG0_PA9_FMPEN                                      /*!< I2C Fm+ mode on PA9 pin enable */
#define SYSCFG_PA10_FMPEN                       SYSCFG_CFG0_PA10_FMPEN                                     /*!< I2C Fm+ mode on PA10 pin enable */
#define SYSCFG_PC14_FMPEN                       SYSCFG_CFG0_PC14_FMPEN                                     /*!< I2C Fm+ mode on PC14 pin enable */
#endif

/* SYSCFG module lockup */
#define SYSCFG_LOCKUP_LOCK                      SYSCFG_CFG1_LOCKUP_LOCK                                    /*!< CPU lockup signal connected  */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_SRAM_LOCKUP                      SYSCFG_CFG1_SRAM_ECC_LOCK                                  /*!< SRAM ECC check error signal connected */
#endif
#if defined(GD32C211)
#define SYSCFG_SRAM_LOCKUP                      SYSCFG_CFG1_SRAM_LOCK                                      /*!< SRAM check error signal connected */
#endif

/* SYSCFG flags */
#if (defined(GD32C231) || defined(GD32C221))
#define SYSCFG_FLAG_ECCME                       SYSCFG_STAT_ECCMEIF                                        /*!< SRAM two bits non-correction event flag */ 
#define SYSCFG_FLAG_ECCSE                       SYSCFG_STAT_ECCSEIF                                        /*!< SRAM single bit correction event flag */
#endif
#if defined(GD32C211)
#define SYSCFG_FLAG_PARITY_ERR                 SYSCFG_CFG1_SRAM_PARITY_ERR                                 /*!< SRAM parity error signal connected */
#endif

/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);

#if (defined(GD32C231) || defined(GD32C221))
/* enable I2C Fm+ mode */
void syscfg_i2c_fast_mode_plus_enable(uint32_t syscfg_gpio);
/* disable I2C Fm+ mode */
void syscfg_i2c_fast_mode_plus_disable(uint32_t syscfg_gpio);
#endif

/* enable remap pin function for small packages */
void syscfg_pin_remap_enable(uint32_t remap_pin);
/* disable remap pin function for small packages */
void syscfg_pin_remap_disable(uint32_t remap_pin);

/* get the boot mode */
uint8_t syscfg_bootmode_get(void);

/* configure the GPIO pin as EXTI Line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);

/* enable module lockup */
void syscfg_lockup_enable(uint32_t lockup);


#if (defined(GD32C231) || defined(GD32C221))
/* get SRAM ECC single correctable bit */
uint32_t syscfg_sram_ecc_single_correctable_bit_get(void);
/* get SRAM ECC error address */
uint32_t syscfg_sram_ecc_error_address_get(void);
#endif

/* set the IRQ_LATENCY value */
void syscfg_irq_latency_set(uint32_t irq_latency);

/* enable interrupt */
void syscfg_interrupt_enable(uint32_t interrupt);
/* disable interrupt */
void syscfg_interrupt_disable(uint32_t interrupt);
#if (defined(GD32C231) || defined(GD32C221))
/* interrupt flag get */
FlagStatus syscfg_interrupt_flag_get(uint32_t flag);
/* interrupt flag clear */
void syscfg_interrupt_flag_clear(uint32_t flag);
#endif
#if defined(GD32C211)
/* pinmux configuration */
void syscfg_pinmux_config(syscfg_pinmux_enum syscfg_pinmux_pin, syscfg_pin_enum syscfg_pin);
/* flag get */
FlagStatus syscfg_flag_get(uint32_t flag);
/* flag clear */
void syscfg_flag_clear(uint32_t flag);
#endif

#endif /* gd32c2x1_SYSCFG_H */

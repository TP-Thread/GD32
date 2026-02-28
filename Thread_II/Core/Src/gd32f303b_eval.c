/*!
    \file  gd32f303b_eval.c
    \brief firmware functions to manage leds, keys, COM ports

    \version 2025-08-20, V3.0.2, demo for GD32F30x
*/

#include "main.h"


static rcu_periph_enum COM_CLK[COMn] = {EVAL_COM0_CLK};
static uint32_t COM_TX_PIN[COMn] = {EVAL_COM0_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {EVAL_COM0_RX_PIN};
static uint32_t COM_GPIO_PORT[COMn] = {EVAL_COM0_GPIO_PORT};
static rcu_periph_enum COM_GPIO_CLK[COMn] = {EVAL_COM0_GPIO_CLK};

static uint32_t KEY_PORT[KEYn]            = {KEY_A_GPIO_PORT, 
                                             KEY_B_GPIO_PORT,
                                             KEY_C_GPIO_PORT,
                                             KEY_D_GPIO_PORT,
                                             KEY_CET_GPIO_PORT};
static uint32_t KEY_PIN[KEYn]             = {KEY_A_PIN,
                                             KEY_B_PIN,
                                             KEY_C_PIN,
                                             KEY_D_PIN,
                                             KEY_CET_PIN};
static rcu_periph_enum KEY_CLK[KEYn]      = {KEY_A_GPIO_CLK,
                                             KEY_B_GPIO_CLK,
                                             KEY_C_GPIO_CLK,
                                             KEY_D_GPIO_CLK,
                                             KEY_CET_GPIO_CLK};
static exti_line_enum KEY_EXTI_LINE[KEYn] = {KEY_A_EXTI_LINE,
                                             KEY_B_EXTI_LINE,
                                             KEY_C_EXTI_LINE,
                                             KEY_D_EXTI_LINE,
                                             KEY_CET_EXTI_LINE};
static uint8_t KEY_PORT_SOURCE[KEYn]      = {KEY_A_EXTI_PORT_SOURCE,
                                             KEY_B_EXTI_PORT_SOURCE,
                                             KEY_C_EXTI_PORT_SOURCE,
                                             KEY_D_EXTI_PORT_SOURCE,
                                             KEY_CET_EXTI_PORT_SOURCE};
static uint8_t KEY_PIN_SOURCE[KEYn]       = {KEY_A_EXTI_PIN_SOURCE,
                                             KEY_B_EXTI_PIN_SOURCE,
                                             KEY_C_EXTI_PIN_SOURCE,
                                             KEY_D_EXTI_PIN_SOURCE,
                                             KEY_CET_EXTI_PIN_SOURCE};
static IRQn_Type KEY_IRQn[KEYn]             = {KEY_A_EXTI_IRQn,
                                             KEY_B_EXTI_IRQn,
                                             KEY_C_EXTI_IRQn,
                                             KEY_D_EXTI_IRQn,
                                             KEY_CET_EXTI_IRQn};


/*!
    \brief      configure key
    \param[in]  key_num: specify the key to be configured
      \arg        KEY_A: wakeup key
      \arg        KEY_B: tamper key
      \arg        KEY_C: user key
      \arg        KEY_D: extension key
      \arg        KEY_CET: extension key
    \param[in]  key_mode: specify button mode
      \arg        KEY_MODE_GPIO: key will be used as simple IO
      \arg        KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
    \param[out] none
    \retval     none
*/
void gd_eval_key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode)
{
    /* enable the key clock */
    rcu_periph_clock_enable(KEY_CLK[key_num]);
    rcu_periph_clock_enable(RCU_AF);

    /* configure button pin as input */
    gpio_init(KEY_PORT[key_num], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_PIN[key_num]);

    if (key_mode == KEY_MODE_EXTI) {
        /* enable and set key EXTI interrupt to the lowest priority */
        nvic_irq_enable(KEY_IRQn[key_num], 2U, 0U);

        /* connect key EXTI line to key GPIO pin */
        gpio_exti_source_select(KEY_PORT_SOURCE[key_num], KEY_PIN_SOURCE[key_num]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[key_num], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[key_num]);
    }
}

/*!
    \brief      return the selected key state
    \param[in]  key: specify the key to be checked
      \arg        KEY_A: wakeup key
      \arg        KEY_B: tamper key
      \arg        KEY_C: user key
      \arg        KEY_D: extension key
      \arg        KEY_CET: extension key
    \param[out] none
    \retval     the key's GPIO pin value
*/
uint8_t gd_eval_key_state_get(key_typedef_enum key)
{
    return gpio_input_bit_get(KEY_PORT[key], KEY_PIN[key]);
}



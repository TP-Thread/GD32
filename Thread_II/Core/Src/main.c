/**
 * @file main.c
 * @author A-rtos (A-rtos@outlook.com)
 * @brief Main program body
 * @version 0.1
 * @date 2026-02-28
 *
 * @copyright Copyright (c) 2026 A-rtos
 *
 */

#include "main.h"
#include "systick.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void gd_gpio_init(void);
static void gd_uart0_init(void);
// static void MX_DMA_Init(void);
// static void MX_ADC2_Init(void);
// static void MX_TIM1_Init(void);
// static void MX_SPI3_Init(void);
// static void MX_TIM2_Init(void);

/* Private user code ---------------------------------------------------------*/
/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
        ;
    return ch;
}

/* retarget the C library printf function to the USART, in IAR __VER__ >= 9000000 environment */
size_t __write(int handle, const unsigned char *buffer, size_t size)
{
    size_t nChars = 0;

    for (; size != 0; --size)
    {
        usart_data_transmit(USART0, (uint8_t)*buffer++);
        while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
            ;
        ++nChars;
    }

    return nChars;
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* Configure systick */
    systick_config();

    /* Initialize all configured peripherals */
    gd_gpio_init();
    gd_uart0_init();

    /* configure TAMPER key */
    gd_eval_key_init(KEY_B, KEY_MODE_GPIO);

    printf("\r\n USART printf example: please press the KEY_B \r\n");

    while (1)
    {
        /* check if the tamper key is pressed */
        // if (RESET == gd_eval_key_state_get(KEY_B))
        // {
        //     delay_1ms(50);
        //     if (RESET == gd_eval_key_state_get(KEY_B))
        //     {
        //         delay_1ms(50);
        //         if (RESET == gd_eval_key_state_get(KEY_B))
        //         {
        //             /* turn on LED2 */
        //             led_b_on();
        //             /* output a message on hyperterminal using printf function */
        //             printf("\r\n USART printf example \r\n");
        //             /* wait for completion of USART transmission */
        //             while (RESET == usart_flag_get(USART0, USART_FLAG_TC))
        //             {
        //             }
        //         }
        //         else
        //         {
        //             /* turn off LED2 */
        //             led_b_off();
        //         }
        //     }
        //     else
        //     {
        //         /* turn off LED2 */
        //         led_b_off();
        //     }
        // }
        // else
        // {
        //     /* turn off LED2 */
        //     led_b_off();
        // }


        delay_1ms(1000);
        led_r_on();
        delay_1ms(1000);
        led_r_off();

    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void gd_gpio_init(void)
{
    /* GPIO Ports Clock Enable */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOD);

    /*Configure GPIO pins */
    gpio_init(LED_B_GPIO_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_B_Pin);
    gpio_init(LED_G_GPIO_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_G_Pin);
    gpio_init(LED_R_GPIO_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_R_Pin);

    /*Configure GPIO pin Output Level */
    gpio_bit_set(LED_B_GPIO_Port, LED_B_Pin);
    gpio_bit_set(LED_G_GPIO_Port, LED_G_Pin);
    gpio_bit_set(LED_R_GPIO_Port, LED_R_Pin);
}

/**
  * @brief UART0 Initialization Function
  * @param None
  * @retval None
  */
static void gd_uart0_init(void)
{
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}

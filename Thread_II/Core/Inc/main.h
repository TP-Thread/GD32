#ifndef MAIN_H
#define MAIN_H

#include "gd32f30x.h"
     
/* Private defines -----------------------------------------------------------*/

typedef enum 
{
    KEY_A = 0,
    KEY_B = 1,
    KEY_C = 2,
    KEY_D = 3,
    KEY_CET = 4
} key_typedef_enum;

typedef enum 
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1
} keymode_typedef_enum;


#define LED_B_Pin          GPIO_PIN_13
#define LED_B_GPIO_Port    GPIOD
#define LED_G_Pin          GPIO_PIN_14
#define LED_G_GPIO_Port    GPIOD
#define LED_R_Pin          GPIO_PIN_15
#define LED_R_GPIO_Port    GPIOB



#define KEYn                             5U

/* KEY_A push-button */
#define KEY_A_PIN                        GPIO_PIN_0
#define KEY_A_GPIO_PORT                  GPIOA
#define KEY_A_GPIO_CLK                   RCU_GPIOA
#define KEY_A_EXTI_LINE                  EXTI_0
#define KEY_A_EXTI_PORT_SOURCE           GPIO_PORT_SOURCE_GPIOA
#define KEY_A_EXTI_PIN_SOURCE            GPIO_PIN_SOURCE_0
#define KEY_A_EXTI_IRQn                  EXTI0_IRQn

/* KEY_B push-button */
#define KEY_B_PIN                        GPIO_PIN_13
#define KEY_B_GPIO_PORT                  GPIOC
#define KEY_B_GPIO_CLK                   RCU_GPIOC
#define KEY_B_EXTI_LINE                  EXTI_13
#define KEY_B_EXTI_PORT_SOURCE           GPIO_PORT_SOURCE_GPIOC
#define KEY_B_EXTI_PIN_SOURCE            GPIO_PIN_SOURCE_13
#define KEY_B_EXTI_IRQn                  EXTI10_15_IRQn

/* KEY_C push-button */
#define KEY_C_PIN                        GPIO_PIN_14
#define KEY_C_GPIO_PORT                  GPIOB
#define KEY_C_GPIO_CLK                   RCU_GPIOB
#define KEY_C_EXTI_LINE                  EXTI_14
#define KEY_C_EXTI_PORT_SOURCE           GPIO_PORT_SOURCE_GPIOB
#define KEY_C_EXTI_PIN_SOURCE            GPIO_PIN_SOURCE_14
#define KEY_C_EXTI_IRQn                  EXTI10_15_IRQn

/* KEY_D push-button */
#define KEY_D_PIN                        GPIO_PIN_4
#define KEY_D_GPIO_PORT                  GPIOC
#define KEY_D_GPIO_CLK                   RCU_GPIOC
#define KEY_D_EXTI_LINE                  EXTI_4
#define KEY_D_EXTI_PORT_SOURCE           GPIO_PORT_SOURCE_GPIOC
#define KEY_D_EXTI_PIN_SOURCE            GPIO_PIN_SOURCE_4
#define KEY_D_EXTI_IRQn                  EXTI4_IRQn

/* KEY_CET push-button */
#define KEY_CET_PIN                      GPIO_PIN_5
#define KEY_CET_GPIO_PORT                GPIOC
#define KEY_CET_GPIO_CLK                 RCU_GPIOC
#define KEY_CET_EXTI_LINE                EXTI_5
#define KEY_CET_EXTI_PORT_SOURCE         GPIO_PORT_SOURCE_GPIOC
#define KEY_CET_EXTI_PIN_SOURCE          GPIO_PIN_SOURCE_5
#define KEY_CET_EXTI_IRQn                EXTI5_9_IRQn

#define led_b_on()     gpio_bit_reset(LED_B_GPIO_Port, LED_B_Pin)
#define led_b_off()    gpio_bit_set(LED_B_GPIO_Port, LED_B_Pin)
#define led_g_on()     gpio_bit_reset(LED_G_GPIO_Port, LED_G_Pin)
#define led_g_off()    gpio_bit_set(LED_G_GPIO_Port, LED_G_Pin)
#define led_r_on()     gpio_bit_reset(LED_R_GPIO_Port, LED_R_Pin)
#define led_r_off()    gpio_bit_set(LED_R_GPIO_Port, LED_R_Pin)
   
   


/* configure key */
void gd_eval_key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode);
/* return the selected key state */
uint8_t gd_eval_key_state_get(key_typedef_enum key);

#endif /* MAIN_H */

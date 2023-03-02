/*
按键left和right控制
*/

#include "key.h"


void key_init(void)
{
    /* enable the Tamper key GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOI);
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure button pin as input */
    gpio_mode_set(GPIOI, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_11);//right
    gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_2);//left
    gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_1);//ok
}

bool key_left(void)
{
    return  gpio_input_bit_get(GPIOF, GPIO_PIN_2);
}

bool key_right(void)
{
return gpio_input_bit_get(GPIOI, GPIO_PIN_11);
}

bool key_OK(void)
{
return gpio_input_bit_get(GPIOF, GPIO_PIN_1);
}












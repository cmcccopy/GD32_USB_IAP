
/*
led initial
create：chenxuefei
date：2023-2-12
*/

#include "led.h"
void led_init(void)
{
    //GPIO时钟使能
    rcu_periph_clock_enable(RCU_GPIOI);
    rcu_periph_clock_enable(RCU_GPIOF);

    /* configure LED1 GPIO port */
    gpio_mode_set(GPIOI, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    gpio_mode_set(GPIOI, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_mode_set(GPIOI, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);

    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    gpio_bit_set(GPIOI,GPIO_PIN_5);
    gpio_bit_set(GPIOI,GPIO_PIN_6);
    gpio_bit_set(GPIOI,GPIO_PIN_7);
 
    /* configure LED2 GPIO port */
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);

    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    gpio_bit_set(GPIOF,GPIO_PIN_8);
    gpio_bit_set(GPIOF,GPIO_PIN_9);
    gpio_bit_set(GPIOF,GPIO_PIN_10);
}

void led1_open(unsigned char led_colour)
{
    switch (led_colour)
    {
        case R://red
            gpio_bit_reset(GPIOI,GPIO_PIN_5);
            break;
        case G://green
            gpio_bit_reset(GPIOI,GPIO_PIN_6);
            break;
        case B://blue
            gpio_bit_reset(GPIOI,GPIO_PIN_7);
            break;
        default:
            break;
    }
}

void led1_close(unsigned char led_colour)
{
    switch (led_colour)
    {
        case R://red
            gpio_bit_toggle(GPIOI,GPIO_PIN_5);
            break;
        case G://green
            gpio_bit_set(GPIOI,GPIO_PIN_6);
            break;
        case B://blue
            gpio_bit_set(GPIOI,GPIO_PIN_7);
            break;
        default:
            break;
    }
}


void led2_open(unsigned char led_colour)
{
    switch (led_colour)
    {
        case R://red
            gpio_bit_reset(GPIOF,GPIO_PIN_8);
            break;
        case G://green
            gpio_bit_reset(GPIOF,GPIO_PIN_9);
            break;
        case B://blue
            gpio_bit_reset(GPIOF,GPIO_PIN_10);
            break;
        default:
            break;
    }
}

void led2_close(unsigned char led_colour)
{
    switch (led_colour)
    {
         case R://red
            gpio_bit_set(GPIOF,GPIO_PIN_8);
            break;
        case G://green
            gpio_bit_set(GPIOF,GPIO_PIN_9);
            break;
        case B://blue
            gpio_bit_set(GPIOF,GPIO_PIN_10);
            break;
        default:
            break;
    }
}

void delay_ms(float time)
{
   int num=time*20;
    while (num--)
    {
        
    }
}


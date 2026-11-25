#ifndef STM32F407_GPIO_H
#define STM32F407_GPIO_H

#include <stdint.h>

/*
 * STM32F407 Discovery: green user LED is connected to PD12.
 * Register addresses are from the STM32F407 reference manual.
 */
#define RCC_AHB1ENR  (*(volatile uint32_t *)0x40023830U)
#define GPIOD_MODER  (*(volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR    (*(volatile uint32_t *)0x40020C14U)

#define LED_PIN      (1U << 12)

static inline void led_init(void)
{
    /* Enable the GPIOD peripheral clock. */
    RCC_AHB1ENR |= (1U << 3);

    /* Set PD12 MODER bits to 01 (general-purpose output). */
    GPIOD_MODER &= ~(3U << 24);
    GPIOD_MODER |=  (1U << 24);
}

static inline void led_toggle(void)
{
    GPIOD_ODR ^= LED_PIN;
}

static inline void delay(void)
{
    volatile uint32_t count = 2000000U;

    while (count--) {
        __asm__ volatile ("nop");
    }
}

#endif /* STM32F407_GPIO_H */

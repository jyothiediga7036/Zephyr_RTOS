#ifndef LPC2129_GPIO_H
#define LPC2129_GPIO_H

#include <stdint.h>

/*
 * LPC2129 example: P0.10 configured as GPIO output.
 * Connect an LED (with a suitable current-limiting resistor) to P0.10
 * according to your board's wiring and LED polarity.
 */
#define PINSEL0  (*(volatile uint32_t *)0xE002C000U)
#define IO0DIR   (*(volatile uint32_t *)0xE0028008U)
#define IO0SET   (*(volatile uint32_t *)0xE0028004U)
#define IO0CLR   (*(volatile uint32_t *)0xE002800CU)

#define LED_PIN  (1U << 10)

static inline void led_init(void)
{
    /* PINSEL0 bits [21:20] = 00 selects GPIO for P0.10. */
    PINSEL0 &= ~(3U << 20);

    /* Configure P0.10 as output. */
    IO0DIR |= LED_PIN;
}

static inline void led_toggle(void)
{
    static uint8_t state;

    if (state) {
        IO0CLR = LED_PIN;
        state = 0U;
    } else {
        IO0SET = LED_PIN;
        state = 1U;
    }
}

static inline void delay(void)
{
    volatile uint32_t count = 2000000U;

    while (count--) {
        __asm__ volatile ("nop");
    }
}

#endif /* LPC2129_GPIO_H */

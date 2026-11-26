/*
 * Copyright (c) 2016 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

//#define SLEEP_TIME_MS 20

// Devicetree node identifiers 
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

#define SW0_NODE DT_ALIAS(sw0)

// GPIO specifications 
static const struct gpio_dt_spec led0 =GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec led1 =  GPIO_DT_SPEC_GET(LED1_NODE, gpios);

static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

static const struct gpio_dt_spec led3 =GPIO_DT_SPEC_GET(LED3_NODE, gpios);

static const struct gpio_dt_spec button =GPIO_DT_SPEC_GET(SW0_NODE, gpios);

// Store all four LED specifications in an array 
static const struct gpio_dt_spec *leds[] = {
    &led0,
    &led1,
    &led2,
    &led3
};

int main(void)
{
    int ret;
    int i;

    //Check and configure all four LEDs 
    for (i = 0; i < 4; i++)
    {
        if (!gpio_is_ready_dt(leds[i]))
        {
            printk("LED %d device is not ready\n", i);
            return 0;
        }

        ret = gpio_pin_configure_dt(leds[i], GPIO_OUTPUT_INACTIVE);

        if (ret < 0)
        {
            printk("LED %d configuration failed\n", i);
            return 0;
        }
    }

    while (1)
    {

        // Control all four LEDs based on button state 
        for (i = 0; i < 4; i++)
        {
            ret = gpio_pin_set_dt(leds[i],1);

            if (ret < 0)
            {
                printk("LED %d control failed\n", i);
                return 0;
            }
            k_msleep(CONFIG_DELAY);
            gpio_pin_set_dt(leds[i], 0);
        }

        //printk("Button: %s\n",button_state ? "PRESSED" : "RELEASED");

       
    }

    return 0;
}

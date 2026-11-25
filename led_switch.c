
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 20 milliseconds polling interval */
//#define SLEEP_TIME_MS 20

/* Devicetree node identifiers */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE  DT_ALIAS(sw0) //switch

/* GPIO specifications */
static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(SW0_NODE, gpios);

int main(void)
{
    int ret;
    int button_state;

    /* Check LED GPIO controller */
    if (!gpio_is_ready_dt(&led)) {
        printf("LED device is not ready\n");
        return 0;
    }

    /* Check button GPIO controller */
    if (!gpio_is_ready_dt(&button)) {
        printf("Button device is not ready\n");
        return 0;
    }

    /* Configure LED as output */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

    if (ret < 0) {
        printf("LED configuration failed\n");
        return 0;
    }

    /* Configure switch as input */
    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);

    if (ret < 0) {
        printf("Button configuration failed\n");
        return 0;
    }

    while (1)
    {
        /* Read switch state */
        button_state = gpio_pin_get_dt(&button);

        if (button_state < 0) {
            printf("Button read failed\n");
            return 0;
        }

        /* Control LED based on switch state */
        ret = gpio_pin_set_dt(&led, button_state);

        if (ret < 0) {
            printf("LED control failed\n");
            return 0;
        }

        printf("Button: %s | LED: %s\n",
               button_state ? "PRESSED" : "RELEASED",
               button_state ? "ON" : "OFF");

        k_msleep(CONFIG_DELAY);
    }

    return 0;
}


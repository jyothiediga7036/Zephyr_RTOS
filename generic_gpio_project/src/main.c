#include <stdint.h>

#if defined(CONFIG_BOARD_STM32F4_DISCO)
#include "stm32f407_gpio.h"
#elif defined(CONFIG_BOARD_LPC2129)
#include "lpc2129_gpio.h"
#else
#error "Unsupported board: select an implementation for this board"
#endif

int main(void)
{
    led_init();

    while (1) {
        led_toggle();
        delay();
    }

    return 0;
}

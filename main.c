
/**
 * @file main.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-08 09:06:72
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <HIC.h>
#include "uart.h"
#include "led.h"
#include "adc_ntc.h"

void main()
{
    init_uart();
    uart_send("Hello World !");
    init_led();
    led_light(1);
    init_adc_ntc();

    PBT6 = 1;
    while (1)
    {
        if (PB6 == 1)
        {
            led_light(0);
        }
        else
        {
            led_light(1);
        }
    }
}

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

#include "sys.h"
#include "led.h"
#include "adc_ntc.h"
#include "adc_offset.h"

void main()
{
    init_uart();
    uart_send("Hello World !");
    // init_adc_offset();

    uart_send_char(char_add_num("abc:", 123.12));
    while (1)
    {
    }
}
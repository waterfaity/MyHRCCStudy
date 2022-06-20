
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
#include "t8n.h"
void main()
{

    init_uart();
    uart_send("Hello World !");
    init_adc_offset();
    // init_t8n();
    while (1)
    {
    }
}

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

#include <hic.h>
#include "uart.h"

void main()
{
    init_uart();
    uart_send("Hello World !");

    while (1)
    {
    }
}
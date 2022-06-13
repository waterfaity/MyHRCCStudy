/**
 * @file led.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-09 17:06:40
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <HIC.h>
#include "led.h"

void init_led(void)
{
    // R : PA0 ANSL0
    // G : PA7 ANSL7
    // B : PB7 ANSL6
    //设置端口GPIO 输入 低电平点亮

    ANSL0 = 1;
    ANSL6 = 1;
    ANSL7 = 1;

    PAT0 = 0;
    PAT7 = 0;
    PBT7 = 0;

    PAPU0 = 1;
    PBPU7 = 1;
    PAPU7 = 1;

    PA0 = 1;
    PA7 = 1;
    PB7 = 1;
}

void led_light(unsigned int tag)
{
    PA0 = tag;
    PA7 = tag;
    PB7 = tag;
}

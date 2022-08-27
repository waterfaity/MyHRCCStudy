/**
 * @file function.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-24 15:08:75
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "sys.h"

void handle_data(void) {

    //adc 中断处理
    if (is_interrupt_adc)
    {
        is_interrupt_adc = false;
        handle_adc_ntc_value();
    }

    //key 中断处理 
    if (is_interrupt_key)
    {
        is_interrupt_key = false;
        uart_send("isr_key");
    }

    //pin_zero
    if (is_interrupt_pin_zero)
    {
        is_interrupt_pin_zero = false;
        uart_send("isr_zero");
    }



}
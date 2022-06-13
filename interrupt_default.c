/**
 * @file interrupt_default.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-09 15:06:51
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <HIC.h>
#include "uart.h"
#include "interrupt_key.h"
#include "adc_ntc.h"

/**
 * UART 中断
 * @brief
 *
 */
void isr(void) interrupt
{
// uart 接收中断
#ifdef __UART_H__
    //接收1中断标志位=1 , 接收1中断使能=1
    if (RX1IE == 1 && RX1IF == 1)
    {
        isr_uart();
    }
#endif
//外部按键中断
#ifdef __INTERRUPT_KEY_H__
    //接收1中断标志位=1 , 接收1中断使能=1
    if (KIE == 1 && KIF == 1)
    {
        isr_interrupt_key();
    }
#endif

//温度传感器
#ifdef __ADC_NTC_H__
    //接收1中断标志位=1 , 接收1中断使能=1
    if (ADIE == 1 && ADIF == 1)
    {
        isr_adc_ntc();
    }
#endif
}
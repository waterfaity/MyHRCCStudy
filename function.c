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

    //adc ��Ҫ�жϴ���
    if (is_interrupt_adc)
    {
        is_interrupt_adc = 0;
        handle_adc_ntc_value();
    }

}
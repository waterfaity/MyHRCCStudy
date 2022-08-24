
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

void main() {

    //初始化向量中断
    init_interrupt_vector();
    //初始化T8N
    t8n_init();
    //初始化串口
    init_uart();
    //发送日志
    uart_send("Hello World ! ");
    //初始化adc
    init_adc_offset();
    //亮灯
    // init_led();
    // led_light(0);

    while (1)
    {
        //1s中断需要处理的数据
        handle_one_second();
        //需要实时处理的数据
        handle_data();
    }
}
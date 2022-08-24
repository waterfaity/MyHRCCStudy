
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

    //��ʼ�������ж�
    init_interrupt_vector();
    //��ʼ��T8N
    t8n_init();
    //��ʼ������
    init_uart();
    //������־
    uart_send("Hello World ! ");
    //��ʼ��adc
    init_adc_offset();
    //����
    // init_led();
    // led_light(0);

    while (1)
    {
        //1s�ж���Ҫ���������
        handle_one_second();
        //��Ҫʵʱ���������
        handle_data();
    }
}
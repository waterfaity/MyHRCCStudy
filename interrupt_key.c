/**
 * @file interrupt_key.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-09 15:06:11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h"
#include "interrupt_key.h"
 

void init_interrupt_key_gpio(void)
{
    //������������/���
    ANSH = 0xFF;
    ANSL = 0xFF;

    //��������
    PAT = 0xFF;
    PBT = 0xFF;
    PCT = 0xFF;

    //��ƽ״̬
    PA = 0x00;
    PB = 0x00;
    PC = 0x00;
}

void init_interrupt_key(void)
{
    // init_interrupt_key_gpio();

    //����PB6 ��������:KMSK5

    //��������
    PBT0 = 1;
    //ʹ���ⲿ�����ж϶˿ڵ��ڲ�����������
    PBPU0 = 1;
    //��������
    KMSK2 = 0;
    //�ж�ʹ��
    KIE = 1;
    //ȫ���ж�
    GIE = 1;
    //�����ȼ��ж�
    GIEL = 1;
    //�жϱ�־����
    KIF = 0;
}
void isr_interrupt_key(void)
{
    uart_send_interrupt("zhongdan le");
    KIF = 0;
}

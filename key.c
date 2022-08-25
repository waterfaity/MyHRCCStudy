/**
 * @file key.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-09 15:06:11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h" 

void init_key(void)
{


    //����PB6 ��������:KMSK5
    //�ߵ�ƽ����

    //��������
    PBT6 = 1;
    //ʹ���ⲿ�����ж϶˿ڵ��ڲ�����������
    PBPU6 = 1;
    //��������
    KMSK5 = 1;
    //�ж�ʹ��
    KIE = 1;
    // //ȫ���ж�
    // GIE = 1;
    // //�����ȼ��ж�
    // GIEL = 1; 
    //�жϱ�־����
    KIF = 0;
}
void isr_key(void)
{
    KIF = 0;
    if (PB6 == 1)
    {
        is_interrupt_key = true;
    }

}

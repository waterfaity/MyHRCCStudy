/**
 * @file interrupt_vector.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-24 16:08:12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "sys.h"

bool is_interrupt_adc = false;
bool is_interrupt_key = false;

/**
 * @brief  IG0 �ж�
 * T8N  �� KINT
 *
 */
void vector_isr_t8n(void)  interrupt_high 0x18
{
    if (T8NIE == 1 && T8NIF == 1)
    {
        isr_t8n();
    }
    else if (KIE == 1 && KIF == 1)
    {
        //�����ж�
        isr_key();
    }
}
/**
 * @brief IG4�ж�
 * ����: adc�ж�
 *
 */
void vector_isr_adc(void) interrupt_high 0x8
{
    if (ADIE == 1 && ADIF == 1)
    {
        //adc�ж�
        isr_adc_ntc();
    }
}

/**
 * @brief IG3 �ж�
 * ����: UART
 *
 */
void vector_isr_uart(void) interrupt_low 0x0014
{
    //����1�жϱ�־λ=1 , ����1�ж�ʹ��=1
    if (RX1IE == 1 && RX1IF == 1)
    {
        isr_uart();
    }
}



void init_interrupt_vector(void)
{
    //INTG<7>   GIE         ��ȫ���ж�ʹ��λ��������ȼ��ж�ʹ��λ
    //INTG<6>   GIEL        �������ȼ��ж�ʹ��λ�������ж�ģʽ��
    //INTG<3>   SOFTIF      : ���жϱ�־
    //INTG<2>   INTVEN0     ���ж�ģʽѡ��λ 0��Ĭ���ж�ģʽ 1�������ж�ģʽ��оƬ������ INTVEN1��CFG_WD0<11>��
    //INTG<1:0> INTV<1:0>   ���ж�������ѡ��λ���ο�����������


    //0000 0101

    INTG = 0x06;  //0100 0101        //�����ж�ģʽ���ж�������INTV<1:0>=10

    // GIEL = 1;           //�������ȼ��ж�
    // GIE = 1;            //��ȫ���ж�
    //INTV<1:0> = 01
    //ģʽѡ��01,��������
    //IG0 1 6 7 4 5 2 3

    //IG4 (0008) AD
    //IG5 (000C) SPIINT
    //IG2 (0010) PINTx
    //IG3 (0014) UART

    //IG0 (0018) T8NINT 
    //IG1 (001C) T21INT
    //IG6 (0020) I2CINT
    //IG7 (0024) T21 / T11
}

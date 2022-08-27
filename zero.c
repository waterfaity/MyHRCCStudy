/**
 * @file zero.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-27 16:08:66
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "sys.h"
 /**
  * @brief PA6�˿�
  *
  */
void init_zero(void) {

    //�����������
    ANSH2 = 1;
    //����
    PAT6 = 1;
	//������λ,��ֹ��������һ���ж�
	PAPD6 = 1;
    //PEG2<1:0>��PINT5~PINT4 ��������ѡ��λ
    // 00��PINT5~PINT4 �½��ش���
    // 01��PINT5~PINT4 �����ش���
    // 1x��PINT5~PINT4 ˫�ش���
    //˫�ش���
	PEG21 = 1; 
    //�ж�ʹ��
    PIE4 = 1;
    //�жϱ�־
    PIF4 = 0;
}

void isr_zero(void) {
	PIF4 = 0;
    is_interrupt_pin_zero = 1;
}
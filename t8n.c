/**
 * @file t8n.c
 * @author WaterFairy (995637517@qq.com)
 * @brief   T8N
 * @version 1.0.0
 * @date 2022-06-16 14:06:12
 * 8 λ��ʱ��/������ T8N �������Ĵ������ƣ�һ�� 8 λ�������Ĵ��� T8N ��һ�����Ƽ�
���� T8NC��T8N �Ĵ������ڴ�ż���ֵ��T8NC ���ƼĴ������ڿ��� T8N ��ʹ�ܡ�T8N
��ģʽѡ��T8NCKI ��������ѡ��Ԥ��Ƶ��ʹ��λ�Լ�Ԥ��Ƶ����Ƶ��ѡ��
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h"


 //0.1ms T8N���(�ж�)һ��
#define T8N_OFFSET (256-25)

/**
 * @brief ��Ʋ���
 *
 */
void t8n_test_init() {

    //ģ�� / ����
    ANSL = 0xFF;
    ANSH = 0xFF;
    //���� / ��
    PBT = 0x00;
    PAT = 0x00;
    PCT = 0x00;
    //�ߵ͵�λ
    PA = 0x00;
    PB = 0x00;
    PB = 0x00;


}
void t8n_test() {
    PA0 = ~PA0;
    PA7 = PA0;
    PB7 = PA0;
}


void init_t8n(void)
{
    t8n_test_init();

    // FOSC =16 000 000HZ
    // 32��Ƶ
    // (Fosc/2)/32 = 250000HZ -> 1s
    // 250000 / 250 ->1ms
    // 250000 / 25  ->0.1ms

    //  T8NPRE      T8NPRS<2:0>         T8NCLK=0        T8NCLK=1

    // 0            ��                   Fosc/2          ��
    // 1            000                 (Fosc/2)/2      Fintlrc /2
    // 1            001                 (Fosc/2)/4      Fintlrc /4
    // 1            010                 (Fosc/2)/8      Fintlrc /8
    // 1            011                 (Fosc/2)/16     Fintlrc /16
    // 1            100                 (Fosc/2)/32     Fintlrc /32
    // 1            101                 (Fosc/2)/64     Fintlrc /64
    // 1            110                 (Fosc/2)/128    Fintlrc /128
    // 1            111                 (Fosc/2)/256    Fintlrc /256
    // A 1010 ; B 1011 ; C 1100 ; D 1101 ;  E 1110 ; F 1111

    timer_count = 0;
    T8NC = 0x0C;         //��ʱ��ģʽ��Ԥ��Ƶ1:(Fosc/2)/32
    T8N = T8N_OFFSET;    //����������ֵ
    T8NIE = 1;           //�򿪶�ʱ������ж�
    T8NIF = 0;           //�������־λ
    // GIE = 1;             //��ȫ���ж�
    T8NEN = 1;           //ʹ��T8N
}
void isr_t8n(void)
{
    T8NIF = 0;                  //���T8N�ж�־λ
    T8N += T8N_OFFSET;          //���ж��ȸ���������ֵ
    timer_count++;
    if (timer_count >= TIMES_ONE_SECOND)
    {
        is_timer_one_second = true;
        timer_count = 0;
        t8n_test();
    }
}

/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "uart.h"
#include <HIC.h>

//���ջ���
unsigned char rxbuf;

void init_uart_gpio(void)
{
    // PA/B/C �˿�Ϊ���ö˿� (ģ������+��������/���)
    //  ANSL �� ANSH ֵ��Ӧ����
    //  0 : ģ������
    //  1 : ��������/���

    // ANSL7 : PA7
    // ANSL6 : PB7
    // ANSL5 : PB3
    // ANSL4 : PB2
    // ANSL3 : PB0
    // ANSL2 : PA2
    // ANSL1 : PA1
    // ANSL0 : PA0

    // ANSH4 : PB5
    // ANSH3 : PB1
    // ANSH2 : PA6
    // ANSH1 : PB4
    //��������δ��
    // ANSL = 0xFF; //ѡ���Ӧ�˿�Ϊ����IO����
    // ANSH = 0xFF; //ѡ���Ӧ�˿�Ϊ����IO����

    //����������ƼĴ���
    // 0: ���
    // 1: ����
    // PAT = 0x00;
    // PBT = 0x00;
    // PCT = 0x00;

    //��ƽ״̬
    // PA = 0x00;
    // PB = 0x00;
    // PC = 0x00;
}

void init_uart(void)
{
    //  UART1SEL��UART1 ���ա����Ͷ˿�ѡ��λ
    //  0��TX1 ���� PB5��RX1 ���� PB6
    //  1��TX1 ���� PC1��RX1 ���� PA5
    UART1SEL = 1;
    PCT1 = 0; //�˿�����Ϊ���
    PAT5 = 1; //�˿�����Ϊ����

    //���������ݸ�ʽѡ��λ
    // 0: 8λ���ݸ�ʽ
    // 1: 9λ���ݸ�ʽ
    RX1LEN = 0;
    TX1LEN = 0;

    //����������
    // BRGH1 ����/����ѡ��
    // 0 : ���� Fosc/(64x(BRnR<7:0>+1))
    // 1 : ����
    // BJT1EN С��������ȥ��ʹ��
    // 0 : ��ֹ
    // 1 : ʹ��
    //��ʽ��������: Fosc = 16MHZ
    //      ������              ���㹫ʽ                    BRGHn   BJTnEN
    //      ����ģʽ            Fosc/(64x(BRnR<7:0>+1))     0       0
    //      ����ģʽ            Fosc/(64xBRRDIV)            0       1
    //      ����ģʽ            Fosc/(16x(BRnR<7:0>+1))     1       0
    //      ����ģʽ            Fosc/(16xBRRDIV)            1       1
    BRGH1 = 0;
    BJT1EN = 0;

    //Ƶ����ֵ
    BR1R = 0x19; //������ = 16MHZ / ( 64 x ( 25 + 1 )) �� 9600bps

    //�����ж�ʹ��
    RX1IE = 1;
    //���ж�
    GIE = 1;

    //����/����ʹ��
    RX1EN = 1;
    TX1EN = 1;
}

void init_uart_2(void)
{
    //  UART1SEL��UART1 ���ա����Ͷ˿�ѡ��λ
    //  0��TX1 ���� PB5��RX1 ���� PB6
    //  1��TX1 ���� PC1��RX1 ���� PA5
    UART1SEL = 1;
    PCT1 = 0; //�˿�����Ϊ���
    PAT5 = 1; //�˿�����Ϊ����

    //���������ݸ�ʽѡ��λ
    // 0: 8λ���ݸ�ʽ
    // 1: 9λ���ݸ�ʽ
    RX1LEN = 0;
    TX1LEN = 0;

    //����������
    // BRGH1 ����/����ѡ��
    // 0 : ���� Fosc/(64x(BRnR<7:0>+1))
    // 1 : ����
    // BJT1EN С��������ȥ��ʹ��
    // 0 : ��ֹ
    // 1 : ʹ��
    //��ʽ��������: Fosc = 16MHZ
    //      ������              ���㹫ʽ                    BRGHn   BJTnEN
    //      ����ģʽ            Fosc/(64x(BRnR<7:0>+1))     0       0
    //      ����ģʽ            Fosc/(64xBRRDIV)            0       1
    //      ����ģʽ            Fosc/(16x(BRnR<7:0>+1))     1       0
    //      ����ģʽ            Fosc/(16xBRRDIV)            1       1
    BRGH1 = 0;
    BJT1EN = 0;

    //Ƶ����ֵ
    BR1R = 0x19; //������ = 16MHZ / ( 64 x ( 25 + 1 )) �� 9600bps

    //�����ж�ʹ��
    RX1IE = 1;

    //���ж�
    GIE = 1;

    // INTVEN0 �ж�ģʽѡ��λ
    // 0��Ĭ���ж�ģʽ
    // 1�������ж�ģʽ��оƬ������ INTVEN1��CFG_WD0<11>������Ϊ 1��
    INTVEN0 = 1;

    //�ж�������ѡ��λ
    INTV1 = 1;
    INTV0 = 1;

    //����/����ʹ��
    RX1EN = 1;
    TX1EN = 1;
}

void isr_uart(void)
{
    rxbuf = RX1B;
    // �ձ�־λ TRMT1 = 1ʱ ����
    while (!TRMT1)
        ;
    TX1B = rxbuf;
}

char num_str[12];
const char itoa_index[] = "0123456789"; // itoa ������

char *myitoa(signed long num)
{
    signed long unum = num; /* �м���� */
    signed long i = 0, j, k = 0;
    char temp;
    /* ȷ��unum��ֵ */
    if (num < 0) /* ʮ���Ƹ��� */
    {
        unum = -num;
        num_str[i++] = '-';
    }
    /* ���� */
    do
    {
        num_str[i++] = itoa_index[unum % 10];
        unum /= 10;
    } while (unum);
    num_str[i] = '\0';

    /* ת�� */
    if (num_str[0] == '-')
    {
        k = 1; /* ʮ���Ƹ��� */
    }

    for (j = 0; j < (i - k) / 2; j++)
    {
        temp = num_str[j + k];
        num_str[j + k] = num_str[i - j - 1];
        num_str[i - j - 1] = temp;
    }
    return (char *)num_str;
}

/**
 * UART �ж�
 * 0x18
 * @brief
 *
 */

void uart_send(const char *data)
{
    while (*data)
    {
        while (!TRMT1)
            ;
        TX1B = *(data++);
    }
}
void uart_send_interrupt(const char *data)
{
    while (*data)
    {
        while (!TRMT1)
            ;
        TX1B = *(data++);
    }
}

void uart_send_interrupt_2(unsigned char *data)
{
    while (*data)
    {
        while (!TRMT1)
            ;
        TX1B = *(data++);
    }
}

void uart_send_interrupt_3(char *data)
{
    while (*data)
    {
        while (!TRMT1)
            ;
        TX1B = *(data++);
    }
}

void uart_send_num(signed long num)
{
    char *data = myitoa(num);
    while (*data)
    {
        while (!TRMT1)
            ;
        TX1B = *(data++);
    }
}

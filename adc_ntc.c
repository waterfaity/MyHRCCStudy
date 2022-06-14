/**
 * @file adc_ntc.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-13 09:06:54
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "adc_ntc.h"
#include "sys.h"
/**
 *
 * @brief PB3
 *
 */
void init_adc_ntc(void)
{
#if 0

        // 1.����
        //  ADC ��·ʹ��ǰ��������Ҫ�����¼������������ȷ�����ã��ſɵõ���ȷת�������
        //  ��������� ADCCM �Ĵ����� VREFSEL λ�̶�Ϊ 0��ADVREFNS λ�̶�Ϊ 1��
        //  ADOFSTS<1:0>λ�̶�Ϊ 10��ADBITSEL<1:0>λ�̶�Ϊ 11������ ADCCSH �Ĵ�����
        //  ADC_LP_EN λ�̶�Ϊ 1��

        // ADCCM  ADC ���ƼĴ����θ� 8 λ
        VREFSEL = 0;
        ADVREFNS = 1;
        ADOFSTS1 = 1;
        ADOFSTS0 = 0;
        ADBITSEL0 = 1;
        ADBITSEL1 = 1;
        ADC_LP_EN = 1;

        // 2.����ת��Ƶ��
        //ѡ�� ADC ת��ʱ�ӣ�ͨ�� ADCCH �Ĵ����е� ADCKS<2:0>ѡ�� ADC ת��ʱ�ӡ�
        // ADC ת��ʱ��Ƶ�ʽ��������� 32KHz~2MHz ֮�䡣
        ADCKS2 = 1;
        ADCKS1 = 0;
        ADCKS0 = 1;

        // 3.ʹ��adc
        //ʹ�� ADC ��·���� ADCCL �Ĵ����е� ADC ʹ��λ ADEN ����Ϊ��1����
        ADEN = 1;

        // 4.
        // ѡ�� ADC ���ο���ѹԴ��ͨ�� ADCCM �Ĵ����е� ADVREFPS <1:0>λ����ѡ
        // �����ѡ���ڲ��ο����������� ADCCH �Ĵ����е� VREFEN λʹ���ڲ��ο���
        // ���� �� 300us �Ժ������� ADCCH �Ĵ����е� VREF_CHOPEN λʹ���ڲ��ο���ѹն������
        // �����ڲ��ο���ѹ���ܹ������ȶ���Ȼ��ȴ� 1ms �������� ADC ת�������ѡ�� VDD
        // ��Ϊ ADC �ο���ѹ��������ʹ�� VREFEN �� VREF_CHOPEN���� ADC ����֮ǰ����
        // ����Ӹõȴ�ʱ�䡣
        VREFSEL = 0;
        ADVREFNS = 1;
        ADOFSTS1 = 1;
        ADOFSTS0 = 0;
        ADBITSEL1 = 1;
        ADBITSEL0 = 1;
        unsigned int i = 0;
        VREF_CHOPEN = 1;

        ADVREFPS1 = 1;
        ADVREFPS0 = 0;
        VREFEN = 1;
        for (i = 0; i < 300 * 16; i++)
        {
        }

        // 5.ѡ�� ADC ����ʱ�䣬ͨ�� ADCCH �Ĵ����е� A/D ����ʱ��ѡ��λ ADST <1:0>
        // �趨��һ�㽨������Ϊ���� 8 �� Tadclk
        ADST1 = 1;
        ADST0 = 0;

        // 6 ѡ�� ADC ����ģʽ��ͨ�� ADCCL �Ĵ����е� A/D ����ģʽѡ��λ SMPS ѡ��
        // ���������Ӳ��������
        // �������
        SMPS = 0;

        // 7 ���ø��ö˿�Ϊģ�����ͣ���ѡ����Щ�ܽ���Ϊ ADC ת������ܽţ��ɶ˿���
        // ģ���ƼĴ��� ANSL �� ANSH ����ѡ�񣬲�����ͨ���Ĵ��� PAT �� PBT ����ѡ���ģ��
        // �ܽ�����Ϊ���롣
        ANSL5 = 0;
        PBT3 = 1;

        //     8 ѡ��ģ���ź�����ͨ�� AINx��ͨ�� ADCCL �Ĵ����е� ADCHS <3:0>ѡ�� ADC
        // ģ��ͨ����
        // ͨ�� 5��AIN5��
        ADCHS3 = 0;
        ADCHS2 = 0;
        ADCHS1 = 0;
        ADCHS0 = 0;

        // 9 ����ת��������뷽ʽ��ͨ�� ADCCH �Ĵ����е� ADFM λ��ѡ���λ�������
        // ���ǵ�λ������á�
        //��λ����
        ADFM = 0;

        //     10 �����Ҫʹ���жϣ����жϿ��ƼĴ�����Ҫ��ȷ�����ã���ȷ�� A/D �жϹ��ܱ�
        // ��ȷ�����Ĭ���ж�ģʽ�£��轫ȫ���ж�ʹ��λ/�����ȼ��ж�ʹ��λ GIE �á�1������
        // ADC �ж�ʹ��λ�á�1�����������ж�ģʽ�£��轫ȫ���ж�ʹ��λ/�����ȼ��ж�ʹ��λ GIE
        // �á�1�������� A/D �ж�����������ȼ������Ƿ�Ҫ���������ȼ��ж�ʹ��λ GIEL���� ADC
        // �ж�ʹ��λ�á�1����
        GIE = 1;
        ADIE = 1;
        ADIF = 0;

        // 11  ADCCL �Ĵ����е� SMPS=0 ʱ��ѡ���������ģʽ������ ADCCL �Ĵ���
        // �е� SMPON=1 ����������ADCCL �Ĵ����е� ADTRG λӲ���Զ��� 1���� SMPS=1 ʱ��
        // ѡ��Ӳ������ģʽ���� ADC ת������λ ADTRG λ����Ϊ��1������ʼ ADC ת����
        SMPS = 0;
        SMPON = 1;

        // 12 ��
        ѯ ADCCL �Ĵ����е�ת��״̬λ ADTRG λ��ȷ���˴� A/D ת���Ƿ���ɡ�
        // 13 ��ȡ ADCRH �� ADCRL �Ĵ����е�ת�������
        // 14  ADC ת������������У׼����ȥ��ʼʧ����

#endif

    unsigned int i = 10000; //��ʱ����
    unsigned int j = 3000;  //��ʱ����

    ANSL5 = 0;     //ѡ��AIN5Ϊģ���
    ADCCL |= 0xF0; // ADCCL<7:4>ѡ��ͨ��
    ADCCL &= 0x7F; //ѡ��ͨ��7
    ADCCM = 0x6B;  //�ο�Դ�ڲ��̶�ѡ��2.048V,���ο��̶�ѡ��VSS��ת��λ���̶�ѡ��12λ��AD����offset�̶�ѡ��λ1
    ADCCH = 0xC8;  //��λ����;ʱ������FOSC/16
    ADEN = 1;      //ʹ��ADCģ��
    VREFEN = 1;    //�ο���ѹģ��ʹ��
    while (j--)
        ;            //�ȴ�300us����
    VREF_CHOPEN = 1; //�ڲ��ο�����ʹ�ܵ�ѹն����
    while (i--)
        ; //�ȴ�1ms����������ת��

    ADC_LP_EN = 1; // ADC�͹��ı���̶�ʹ��
    PBT3 = 1;

    while (1)
    {
        ADTRG = 1;
        while (ADTRG)
            ;
        ADIF = 0;
        unsigned int current = (ADCRH << 8) | ADCRL;
        uart_send_num(current);
    }
}
int avrage = 0;
int times = 0;
unsigned int total = 0;
void isr_adc_ntc(void)
{
    // uart_send_num(12);
    ADTRG = 1;
    while (ADTRG)
        ;
    ADIF = 0;

    unsigned int current = (ADCRH << 8) | ADCRL;
    // uart_send_num(current);
}
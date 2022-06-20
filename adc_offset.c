/*********************************************************
*Copyright (C), 2020, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  adc_offset.c
*��  ��:  AE Team
*��  ��:  v1.0��������iDesigner(v4.2.3.166) + ������HRCC(v1.2.0.106)
*��  ��:  2020/12/25
*��  ��:  ADCͨ����ʾ
          PB3��ģ������˿�
          �궨��VDDVREFѡ��VDD��Ϊ�ο���ѹ���ˣ�
          ����ѡ���ڲ�2.048V��Ϊ�ο���ѹ���ˡ�
          ת��ֵ��ȥoffset����ADC���������offsetΪ802FH���ڲ�2.048V���ο�����8030H��VDD���ο�����8λ���ݣ�
          IAP��16λ���ݺ������ж��Ƿ�����ߵ�8λȡ����
          ע�⣺����offset�Ĵ��ڣ�Ϊ��ֹ�����ת��ֵС��offsetʱ��ADC���ֱ�ӹ�0������ADC���ֻ�ܲ⵽(0xFFF-offset)��
*��  ע:  ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "sys.h"
#include "adc_offset.h"
// ntc �¶ȿ�ʼ
const int START_TEMP_CODE = -20;
// adc�¶ȱ���
const int START_TEMP_CODE_LEN = 220;
// adc�¶ȱ�
const unsigned long RES_TEMP_CODE[] = // ADC��Ӧ�¶�ֵ ���µ�����������90��
    {
        3911, 3901, 3890, 3878, 3866, 3853, 3840, 3827, 3813, 3799, // -20~ -11
        3784, 3768, 3752, 3736, 3719, 3701, 3683, 3664, 3644, 3624, // -10~ -1
        3603, 3582, 3559, 3537, 3513, 3489, 3464, 3439, 3412, 3386, //   0~9
        3358, 3330, 3301, 3271, 3241, 3210, 3178, 3146, 3113, 3080, //  10~19
        3046, 3011, 2976, 2940, 2903, 2864, 2829, 2791, 2753, 2714, //  20~29
        2675, 2636, 2596, 2556, 2515, 2475, 2434, 2393, 2352, 2311, //  30~39
        2270, 2229, 2188, 2146, 2105, 2064, 2024, 1983, 1943, 1903, //  40~49
        1863, 1823, 1784, 1745, 1707, 1669, 1631, 1594, 1557, 1521, //  50~59
        1485, 1450, 1415, 1381, 1347, 1314, 1282, 1250, 1218, 1188, //  60~69
        1157, 1128, 1099, 1071, 1043, 1016, 989, 963, 938, 913,     //  70~79
        889, 865, 842, 819, 798, 775, 755, 735, 715, 696,           //  80~89
        677, 658, 641, 623, 606, 590, 574, 558, 543, 528,           //  90~99
        514, 500, 487, 473, 461, 448, 436, 424, 413, 402,           // 100~109
        391, 381, 370, 360, 351, 342, 333, 324, 315, 307,           // 110~119
        299, 291, 283, 276, 269, 262, 255, 248, 242, 236,           // 120~129
        230, 224, 218, 213, 207, 202, 197, 192, 187, 182,           // 130~139
        178, 173, 169, 165, 161, 157, 153, 149, 146, 142,           // 140~149
        139, 136, 132, 129, 126, 123, 120, 117, 115, 112,           // 150~159
        109, 107, 104, 102, 100, 97, 95, 93, 91, 89,                // 160~169
        87, 85, 83, 81, 79, 77, 76, 74, 72, 71,                     // 170~179
        69, 68, 66, 65, 63, 62, 61, 60, 58, 57,                     // 180~189
        56, 55, 53, 52, 51, 50, 49, 48, 47, 46                      // 190~199
};                                                                  //����¶���Ҫ�����������������¼����¶�+22+5+5 = XX+32 = YY

// �ڲ��ο���ѹflash��ַ
#define ADD_VREFEN 0x802F
// VDD�ο���ѹflash��ַ
#define ADD_VREFEN_NOT 0x8030

// #define VDDVREF //�궨��ѡ��VDD��Ϊ�ο���ѹ��ע�ͱ�����ѡ���ڲ�2.048V��Ϊ�ο���ѹ����

unsigned int adc_value;
unsigned int offset_value = 0; //����ADCУ׼ֵ

/**********************************************
��������ADC_convert(uchar ch)
��  ����ADCת������
����ֵ��ת��ͨ��ch
���ֵ����
����ֵ��ת����12λ���
**********************************************/
unsigned int ADC_convert(void)
{
    ADTRG = 1; //����ADת��
    while (ADTRG)
        ;
    ADIF = 0;
    return (unsigned int)ADCRH << 8 | ADCRL;
}

/**********************************************
��������main()
��  ����������,ѡ��AIN5ͨ��������ֵ��UART���͵���λ��
����ֵ����
���ֵ����
����ֵ����
**********************************************/
void init_adc_offset(void)
{
    unsigned int i = 10000; //��ʱ����
    unsigned int j = 3000;  //��ʱ����
    unsigned char cnt = 3;

/****************��ʼ��ADC********************/
#ifdef VDDVREF
    while (cnt != 0)
    {
        offset_value = flash_read(ADD_VREFEN_NOT);             //��ȡoffsetֵ
        if ((offset_value >> 8) == ((~offset_value) & 0x00FF)) //�Ƿ�����ߵ�8λȡ��������ȡ��8λ��Ϊoffset
        {
            offset_value = offset_value & 0x00FF;
            break;
        }
        else
        {
            cnt--;
            if (cnt == 0)
                offset_value = 0; //��IAP����3�κ��Բ�����ߵ�8λȡ����offset�̶�Ϊ0
        }
    }
    ANSL5 = 0; //ѡ��AIN5Ϊģ��� PB3
    // ADCCL ������������Ϊ ����ͨ��7
    ADCCL |= 0xF0; // ADCCL<7:4>ѡ��ͨ�� 1111 0000 ��λ��1 ��λ����
    ADCCL &= 0x7F; //ѡ��ͨ��0  0101 1111, ��λ���� 111 ,��λ����
    ADCCM = 0x4B;  //�ο�ԴVDD,���ο��̶�ѡ��VSS��ת��λ���̶�ѡ��12λ��AD����offset�̶�ѡ��λ1
    ADCCH = 0xC8;  //��λ����;ʱ������FOSC/16
    ADEN = 1;      //ʹ��ADCģ��
#else
    while (cnt != 0)
    {
        offset_value = flash_read(ADD_VREFEN);                 //��ȡoffsetֵ
        if ((offset_value >> 8) == ((~offset_value) & 0x00FF)) //�Ƿ�����ߵͰ�λȡ��������ȡ��8λ��Ϊoffset
        {
            offset_value = offset_value & 0x00FF;

            break;
        }
        else
        {
            cnt--;
            if (cnt == 0)
                offset_value = 0; //��IAP����3�κ��Բ�����ߵ�8λȡ����offset�̶�Ϊ0
        }
    }
    ANSL5 = 0;     //ѡ��AIN5Ϊģ���
    ADCCL |= 0xF0; // ADCCL<7:4>ѡ��ͨ��
    ADCCL &= 0x5F; //ѡ��ͨ��5
    ADCCH = 0xC8;  //��λ����;ʱ������FOSC/16
    ADEN = 1;      //ʹ��ADCģ��
    VREFEN = 1;    //�ο���ѹģ��ʹ��
    while (j--)
        ;            //�ȴ�300us����
    VREF_CHOPEN = 1; //�ڲ��ο�����ʹ�ܵ�ѹն����
    while (i--)
        ; //�ȴ�1ms����������ת��
#endif

    ADC_LP_EN = 1; // ADC�͹��ı���̶�ʹ��
    PAT7 = 1;
    SMPS = 1; //Ӳ�����Ʋ�����ADTRG=1ʱ����AD����ת��

    GIE = 1;
    ADIE = 1;

    //��ʼת��
    ADTRG = 1;
}

unsigned int calc_adc_value()
{
    unsigned int adc_value = (unsigned int)ADCRH << 8 | ADCRL;

    if (adc_value > offset_value) // ADת��ֵ����offsetֵ���ȥoffset������ADC�����0
        adc_value -= offset_value;
    else
        adc_value = 0;

    return adc_value;
}

double calc_ntc(unsigned int adc_value)
{

    //���ֱȽϷ��±�
    int temp_index = 0;

    unsigned long temp_adc = 0;
    int start_index = 0, end_index = START_TEMP_CODE_LEN - 1;
    int i = 0;

    for (i = 0; i < START_TEMP_CODE_LEN / 2; i++)
    {
        temp_index = (end_index + start_index) / 2;
        temp_adc = RES_TEMP_CODE[temp_index];

        if (adc_value == temp_adc)
        {
            break;
        }
        else if (adc_value > temp_adc)
        {
            end_index = temp_index;
        }
        else
        {
            start_index = temp_index;
        }
        if (temp_index == START_TEMP_CODE_LEN - 2)
        {
            //���ַ������ڶ����ȽϽ���->�Ƚ����
            if (adc_value == RES_TEMP_CODE[START_TEMP_CODE_LEN - 1])
            {
                temp_adc = adc_value;
                temp_index = START_TEMP_CODE_LEN - 1;
            }

            break;
        }
        else if (temp_index == 1)
        {
            //���ַ��ڶ����ȽϽ���->�Ƚ���С
            if (adc_value == RES_TEMP_CODE[0])
            {
                temp_adc = adc_value;
                temp_index = 0;
            }
            break;
        }
    }

    double ntc = 0;
    long adc_offset = adc_value - temp_adc;
    long code_offset = RES_TEMP_CODE[end_index] - RES_TEMP_CODE[start_index];

    double ntc_offset = adc_offset / (double)code_offset;
    ntc = START_TEMP_CODE + temp_index + ntc_offset;
    return ntc;
}

void isr_adc_offset(void)
{
    unsigned int adc_value = calc_adc_value();
    double ntc_value = calc_ntc(adc_value);

    uart_send_char(char_add_num("�¶�:", ntc_value));

    // char *data1 = doble_to_char(ntc_value);
    // uart_send_interrupt_2((unsigned char *)data1);
    // uart_send_num(adc_value);
    uart_send_interrupt("\n");
    ADIF = 0;

    //�ٴ�ת��
    ADTRG = 1;
}
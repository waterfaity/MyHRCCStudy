/*********************************************************
*Copyright (C), 2020, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  adc_offset.c
*作  者:  AE Team
*版  本:  v1.0，编译于iDesigner(v4.2.3.166) + 工具链HRCC(v1.2.0.106)
*日  期:  2020/12/25
*描  述:  ADC通信演示
          PB3：模拟输入端口
          宏定义VDDVREF选择VDD作为参考电压正端，
          否则选择内部2.048V作为参考电压正端。
          转换值减去offset进行ADC软件补偿，offset为802FH（内部2.048V作参考）和8030H（VDD作参考）低8位数据，
          IAP读16位数据后需先判断是否满足高低8位取反。
          注意：由于offset的存在，为防止溢出，转换值小于offset时，ADC结果直接归0；并且ADC最大只能测到(0xFFF-offset)。
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "sys.h"
#include "adc_offset.h"
// ntc 温度开始
const int START_TEMP_CODE = -20;
// adc温度表长度
const int START_TEMP_CODE_LEN = 220;
// adc温度表
const unsigned long RES_TEMP_CODE[] = // ADC对应温度值 恒温档测试下来在90度
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
};                                                                  //最高温度需要满足的条件；量产记录最高温度+22+5+5 = XX+32 = YY

// 内部参考电压flash地址
#define ADD_VREFEN 0x802F
// VDD参考电压flash地址
#define ADD_VREFEN_NOT 0x8030

// #define VDDVREF //宏定义选择VDD作为参考电压，注释本句则选择内部2.048V作为参考电压正端

unsigned int adc_value;
unsigned int offset_value = 0; //保存ADC校准值

/**********************************************
函数名：ADC_convert(uchar ch)
描  述：ADC转换函数
输入值：转换通道ch
输出值：无
返回值：转换的12位结果
**********************************************/
unsigned int ADC_convert(void)
{
    ADTRG = 1; //启动AD转换
    while (ADTRG)
        ;
    ADIF = 0;
    return (unsigned int)ADCRH << 8 | ADCRL;
}

/**********************************************
函数名：main()
描  述：主函数,选择AIN5通道，测量值经UART传送到上位机
输入值：无
输出值：无
返回值：无
**********************************************/
void init_adc_offset(void)
{
    unsigned int i = 10000; //延时变量
    unsigned int j = 3000;  //延时变量
    unsigned char cnt = 3;

/****************初始化ADC********************/
#ifdef VDDVREF
    while (cnt != 0)
    {
        offset_value = flash_read(ADD_VREFEN_NOT);             //获取offset值
        if ((offset_value >> 8) == ((~offset_value) & 0x00FF)) //是否满足高低8位取反，是则取低8位作为offset
        {
            offset_value = offset_value & 0x00FF;
            break;
        }
        else
        {
            cnt--;
            if (cnt == 0)
                offset_value = 0; //读IAP超过3次后仍不满足高低8位取反则offset固定为0
        }
    }
    ANSL5 = 0; //选择AIN5为模拟口 PB3
    // ADCCL 的两步操作即为 设置通道7
    ADCCL |= 0xF0; // ADCCL<7:4>选择通道 1111 0000 高位设1 低位不变
    ADCCL &= 0x7F; //选择通道0  0101 1111, 高位设置 111 ,低位不变
    ADCCM = 0x4B;  //参考源VDD,负参考固定选择VSS，转换位数固定选择12位，AD调整offset固定选择档位1
    ADCCH = 0xC8;  //低位对齐;时钟周期FOSC/16
    ADEN = 1;      //使能ADC模块
#else
    while (cnt != 0)
    {
        offset_value = flash_read(ADD_VREFEN);                 //获取offset值
        if ((offset_value >> 8) == ((~offset_value) & 0x00FF)) //是否满足高低八位取反，是则取低8位作为offset
        {
            offset_value = offset_value & 0x00FF;

            break;
        }
        else
        {
            cnt--;
            if (cnt == 0)
                offset_value = 0; //读IAP超过3次后仍不满足高低8位取反则offset固定为0
        }
    }
    ANSL5 = 0;     //选择AIN5为模拟口
    ADCCL |= 0xF0; // ADCCL<7:4>选择通道
    ADCCL &= 0x5F; //选择通道5
    ADCCH = 0xC8;  //低位对齐;时钟周期FOSC/16
    ADEN = 1;      //使能ADC模块
    VREFEN = 1;    //参考电压模块使能
    while (j--)
        ;            //等待300us以上
    VREF_CHOPEN = 1; //内部参考必须使能电压斩波器
    while (i--)
        ; //等待1ms以上再启动转换
#endif

    ADC_LP_EN = 1; // ADC低功耗必须固定使能
    PAT7 = 1;
    SMPS = 1; //硬件控制采样，ADTRG=1时启动AD采样转换

    GIE = 1;
    ADIE = 1;

    //开始转换
    ADTRG = 1;
}

unsigned int calc_adc_value()
{
    unsigned int adc_value = (unsigned int)ADCRH << 8 | ADCRL;

    if (adc_value > offset_value) // AD转换值大于offset值则减去offset，否则ADC结果归0
        adc_value -= offset_value;
    else
        adc_value = 0;

    return adc_value;
}

double calc_ntc(unsigned int adc_value)
{

    //二分比较法下标
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
            //二分法倒数第二个比较结束->比较最大
            if (adc_value == RES_TEMP_CODE[START_TEMP_CODE_LEN - 1])
            {
                temp_adc = adc_value;
                temp_index = START_TEMP_CODE_LEN - 1;
            }

            break;
        }
        else if (temp_index == 1)
        {
            //二分法第二个比较结束->比较最小
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

    uart_send_char(char_add_num("温度:", ntc_value));

    // char *data1 = doble_to_char(ntc_value);
    // uart_send_interrupt_2((unsigned char *)data1);
    // uart_send_num(adc_value);
    uart_send_interrupt("\n");
    ADIF = 0;

    //再次转换
    ADTRG = 1;
}
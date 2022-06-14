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

        // 1.配置
        //  ADC 电路使用前，根据需要对以下几个方面进行正确的配置，才可得到正确转换结果。
        //  需软件设置 ADCCM 寄存器的 VREFSEL 位固定为 0，ADVREFNS 位固定为 1，
        //  ADOFSTS<1:0>位固定为 10，ADBITSEL<1:0>位固定为 11；设置 ADCCSH 寄存器的
        //  ADC_LP_EN 位固定为 1。

        // ADCCM  ADC 控制寄存器次高 8 位
        VREFSEL = 0;
        ADVREFNS = 1;
        ADOFSTS1 = 1;
        ADOFSTS0 = 0;
        ADBITSEL0 = 1;
        ADBITSEL1 = 1;
        ADC_LP_EN = 1;

        // 2.设置转换频率
        //选择 ADC 转换时钟，通过 ADCCH 寄存器中的 ADCKS<2:0>选择 ADC 转换时钟。
        // ADC 转换时钟频率建议设置在 32KHz~2MHz 之间。
        ADCKS2 = 1;
        ADCKS1 = 0;
        ADCKS0 = 1;

        // 3.使能adc
        //使能 ADC 电路，将 ADCCL 寄存器中的 ADC 使能位 ADEN 设置为“1”。
        ADEN = 1;

        // 4.
        // 选择 ADC 正参考电压源，通过 ADCCM 寄存器中的 ADVREFPS <1:0>位进行选
        // 择，如果选择内部参考，需先设置 ADCCH 寄存器中的 VREFEN 位使能内部参考，
        // 并等 待 300us 以后，再设置 ADCCH 寄存器中的 VREF_CHOPEN 位使能内部参考电压斩波器，
        // 否则内部参考电压可能工作不稳定，然后等待 1ms 后再启动 ADC 转换；如果选择 VDD
        // 作为 ADC 参考电压，则无需使能 VREFEN 和 VREF_CHOPEN，在 ADC 启动之前，无
        // 需添加该等待时间。
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

        // 5.选择 ADC 采样时间，通过 ADCCH 寄存器中的 A/D 采样时间选择位 ADST <1:0>
        // 设定，一般建议设置为至少 8 个 Tadclk
        ADST1 = 1;
        ADST0 = 0;

        // 6 选择 ADC 采样模式，通过 ADCCL 寄存器中的 A/D 采样模式选择位 SMPS 选择
        // 软件采样或硬件采样。
        // 软件采样
        SMPS = 0;

        // 7 设置复用端口为模拟类型，即选择哪些管脚作为 ADC 转换输入管脚，由端口数
        // 模控制寄存器 ANSL 和 ANSH 控制选择，并且需通过寄存器 PAT 和 PBT 将被选择的模拟
        // 管脚设置为输入。
        ANSL5 = 0;
        PBT3 = 1;

        //     8 选择模拟信号输入通道 AINx，通过 ADCCL 寄存器中的 ADCHS <3:0>选择 ADC
        // 模拟通道。
        // 通道 5（AIN5）
        ADCHS3 = 0;
        ADCHS2 = 0;
        ADCHS1 = 0;
        ADCHS0 = 0;

        // 9 设置转换结果对齐方式，通过 ADCCH 寄存器中的 ADFM 位，选择高位对齐放置
        // 还是低位对齐放置。
        //低位对齐
        ADFM = 0;

        //     10 ：如果要使用中断，则中断控制寄存器需要正确地设置，以确保 A/D 中断功能被
        // 正确激活。在默认中断模式下，需将全局中断使能位/高优先级中断使能位 GIE 置“1”，将
        // ADC 中断使能位置“1”；在向量中断模式下，需将全局中断使能位/高优先级中断使能位 GIE
        // 置“1”，根据 A/D 中断所在组的优先级决定是否要开启低优先级中断使能位 GIEL，将 ADC
        // 中断使能位置“1”。
        GIE = 1;
        ADIE = 1;
        ADIF = 0;

        // 11  ADCCL 寄存器中的 SMPS=0 时，选择软件采样模式，设置 ADCCL 寄存器
        // 中的 SMPON=1 启动采样，ADCCL 寄存器中的 ADTRG 位硬件自动置 1；当 SMPS=1 时，
        // 选择硬件采样模式，将 ADC 转换启动位 ADTRG 位设置为“1”，开始 ADC 转换。
        SMPS = 0;
        SMPON = 1;

        // 12 轮
        询 ADCCL 寄存器中的转换状态位 ADTRG 位，确定此次 A/D 转换是否完成。
        // 13 读取 ADCRH 和 ADCRL 寄存器中的转换结果。
        // 14  ADC 转换结果进行软件校准，减去初始失调误差。

#endif

    unsigned int i = 10000; //延时变量
    unsigned int j = 3000;  //延时变量

    ANSL5 = 0;     //选择AIN5为模拟口
    ADCCL |= 0xF0; // ADCCL<7:4>选择通道
    ADCCL &= 0x7F; //选择通道7
    ADCCM = 0x6B;  //参考源内部固定选择2.048V,负参考固定选择VSS，转换位数固定选择12位，AD调整offset固定选择档位1
    ADCCH = 0xC8;  //低位对齐;时钟周期FOSC/16
    ADEN = 1;      //使能ADC模块
    VREFEN = 1;    //参考电压模块使能
    while (j--)
        ;            //等待300us以上
    VREF_CHOPEN = 1; //内部参考必须使能电压斩波器
    while (i--)
        ; //等待1ms以上再启动转换

    ADC_LP_EN = 1; // ADC低功耗必须固定使能
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
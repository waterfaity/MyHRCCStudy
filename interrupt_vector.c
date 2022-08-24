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

unsigned int is_interrupt_adc = 0;

/**
 * @brief T8N中断
 *
 */
void vector_isr_t8n(void)  interrupt_high 0x18
{
    if (T8NIE == 1 && T8NIF == 1)
    {
        isr_t8n();
    }
}
/**
 * @brief adc中断
 *
 */
 void vector_isr_adc(void) interrupt_high 0x8
 {
     if (ADIE == 1 && ADIF == 1)
     {
         isr_adc_ntc();
     }
 }


void init_interrupt_vector(void)
{
    //INTG<7>   GIE         ：全局中断使能位，或高优先级中断使能位
    //INTG<6>   GIEL        ：低优先级中断使能位（向量中断模式）
    //INTG<3>   SOFTIF      : 软中断标志
    //INTG<2>   INTVEN0     ：中断模式选择位 0：默认中断模式 1：向量中断模式（芯片配置字 INTVEN1（CFG_WD0<11>）
    //INTG<1:0> INTV<1:0>   ：中断向量表选择位，参考向量表配置


    //0000 0101

    INTG = 0x46;  //0100 0101        //向量中断模式，中断向量表INTV<1:0>=10

    // GIEL = 1;           //开低优先级中断
    // GIE = 1;            //开全局中断
    //INTV<1:0> = 01
    //模式选择01,排序如下
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

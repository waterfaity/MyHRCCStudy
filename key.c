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


    //按键PB6 按键屏蔽:KMSK5
    //高调平点亮

    //配置输入
    PBT6 = 1;
    //使能外部按键中断端口的内部弱上拉电阻
    PBPU6 = 1;
    //按键屏蔽
    KMSK5 = 1;
    //中断使能
    KIE = 1;
    // //全局中断
    // GIE = 1;
    // //低优先级中断
    // GIEL = 1; 
    //中断标志清零
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

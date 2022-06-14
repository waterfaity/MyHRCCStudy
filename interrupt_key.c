/**
 * @file interrupt_key.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-09 15:06:11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h"
#include "interrupt_key.h"
 

void init_interrupt_key_gpio(void)
{
    //设置数字输入/输出
    ANSH = 0xFF;
    ANSL = 0xFF;

    //设置输入
    PAT = 0xFF;
    PBT = 0xFF;
    PCT = 0xFF;

    //电平状态
    PA = 0x00;
    PB = 0x00;
    PC = 0x00;
}

void init_interrupt_key(void)
{
    // init_interrupt_key_gpio();

    //按键PB6 按键屏蔽:KMSK5

    //配置输入
    PBT0 = 1;
    //使能外部按键中断端口的内部弱上拉电阻
    PBPU0 = 1;
    //按键屏蔽
    KMSK2 = 0;
    //中断使能
    KIE = 1;
    //全局中断
    GIE = 1;
    //低优先级中断
    GIEL = 1;
    //中断标志清零
    KIF = 0;
}
void isr_interrupt_key(void)
{
    uart_send_interrupt("zhongdan le");
    KIF = 0;
}

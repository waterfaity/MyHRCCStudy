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
#include "key.h"

void init_key(void)
{

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
void isr_key(void)
{
    uart_send_interrupt("zhongdan le");
    KIF = 0;
}

/**
 * @file t8n.c
 * @author WaterFairy (995637517@qq.com)
 * @brief   T8N
 * @version 1.0.0
 * @date 2022-06-16 14:06:12
 * 8 位定时器/计数器 T8N 由两个寄存器控制，一个 8 位计数器寄存器 T8N 和一个控制寄
存器 T8NC。T8N 寄存器用于存放计数值，T8NC 控制寄存器用于控制 T8N 的使能、T8N
的模式选择、T8NCKI 计数边沿选择、预分频器使能位以及预分频器分频比选择。
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "t8n.h"
#include "sys.h"
unsigned int timer_cnt;
// 1hz =
unsigned int C_1000_MS = 0;

void init_t8n(void)
{

    // FOSC =16 000 000HZ
    // 32分频
    // (Fosc/2)/32 = 250000HZ -> 1s
    // 250000 / 250 ->1ms
    // 250000 / 25  ->0.1ms

    //  T8NPRE      T8NPRS<2:0>         T8NCLK=0        T8NCLK=1

    // 0            —                   Fosc/2          —
    // 1            000                 (Fosc/2)/2      Fintlrc /2
    // 1            001                 (Fosc/2)/4      Fintlrc /4
    // 1            010                 (Fosc/2)/8      Fintlrc /8
    // 1            011                 (Fosc/2)/16     Fintlrc /16
    // 1            100                 (Fosc/2)/32     Fintlrc /32
    // 1            101                 (Fosc/2)/64     Fintlrc /64
    // 1            110                 (Fosc/2)/128    Fintlrc /128
    // 1            111                 (Fosc/2)/256    Fintlrc /256
    // A 1010
    // B 1011
    // C 1100
    // D 1101
    // E 1110
    // F 1111
    timer_cnt = 0;
    T8NC = 0x0C; //定时器模式，预分频1:(Fosc/2)/32  1100 =  C
    T8N = (256 - 250);
    T8NIE = 1; //中断使能
    T8NIF = 0; //中断标志
    GIE = 1;   //全局中断
    T8NEN = 1; //使能
}
void isr_t8n(void)
{
    T8N += 6;
    if (++timer_cnt >= C_1000_MS)
    {
        timer_cnt = 0;
        uart_send_interrupt("-t8n-");
    }

    T8NIF = 0;
}
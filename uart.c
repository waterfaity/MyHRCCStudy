
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

//接收缓存
unsigned char rxbuf;

void init_gpio()
{
    // PA/B/C 端口为复用端口 (模拟输入+数字输入/输出)
    //  ANSL 和 ANSH 值对应如下
    //  0 : 模拟输入
    //  1 : 数字输入/输出

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
    //其它保留未用
    ANSL = 0xFF; //选择对应端口为数字IO功能
    ANSH = 0xFF; //选择对应端口为数字IO功能

    //输入输出控制寄存器
    // 0: 输出
    // 1: 输入
    PAT = 0x00;
    PBT = 0x00;
    PCT = 0x00;

    //电平状态
    PA = 0x00;
    PB = 0x00;
    PC = 0x00;
}

void init_uart(void)
{
    //  UART1SEL：UART1 接收、发送端口选择位
    //  0：TX1 复用 PB5，RX1 复用 PB6
    //  1：TX1 复用 PC1，RX1 复用 PA5
    UART1SEL = 1;
    PCT1 = 0; //端口设置为输出
    PAT5 = 1; //端口设置为输入

    //发送器数据格式选择位
    // 0: 8位数据格式
    // 1: 9位数据格式
    RX1LEN = 0;
    TX1LEN = 0;

    //波特率设置
    // BRGH1 高速/低速选择
    // 0 : 低速 Fosc/(64x(BRnR<7:0>+1))
    // 1 : 高速
    // BJT1EN 小数波特率去抖使能
    // 0 : 禁止
    // 1 : 使能
    //公式计算如下: Fosc = 16MHZ
    //      波特率              计算公式                    BRGHn   BJTnEN
    //      低速模式            Fosc/(64x(BRnR<7:0>+1))     0       0
    //      低速模式            Fosc/(64xBRRDIV)            0       1
    //      高速模式            Fosc/(16x(BRnR<7:0>+1))     1       0
    //      高速模式            Fosc/(16xBRRDIV)            1       1
    BRGH1 = 0;
    BJT1EN = 0;

    //频率设值
    BR1R = 0x19; //波特率 = 16MHZ / ( 64 x ( 25 + 1 )) ≈ 9600bps

    //接收中断使能
    RX1IE = 1;
    //总中断
    GIE = 1;

    //发送/接收使能
    RX1EN = 1;
    TX1EN = 1;
}

void init_uart_2(void)
{
    //  UART1SEL：UART1 接收、发送端口选择位
    //  0：TX1 复用 PB5，RX1 复用 PB6
    //  1：TX1 复用 PC1，RX1 复用 PA5
    UART1SEL = 1;
    PCT1 = 0; //端口设置为输出
    PAT5 = 1; //端口设置为输入

    //发送器数据格式选择位
    // 0: 8位数据格式
    // 1: 9位数据格式
    RX1LEN = 0;
    TX1LEN = 0;

    //波特率设置
    // BRGH1 高速/低速选择
    // 0 : 低速 Fosc/(64x(BRnR<7:0>+1))
    // 1 : 高速
    // BJT1EN 小数波特率去抖使能
    // 0 : 禁止
    // 1 : 使能
    //公式计算如下: Fosc = 16MHZ
    //      波特率              计算公式                    BRGHn   BJTnEN
    //      低速模式            Fosc/(64x(BRnR<7:0>+1))     0       0
    //      低速模式            Fosc/(64xBRRDIV)            0       1
    //      高速模式            Fosc/(16x(BRnR<7:0>+1))     1       0
    //      高速模式            Fosc/(16xBRRDIV)            1       1
    BRGH1 = 0;
    BJT1EN = 0;

    //频率设值
    BR1R = 0x19; //波特率 = 16MHZ / ( 64 x ( 25 + 1 )) ≈ 9600bps

    //接收中断使能
    RX1IE = 1;

    //总中断
    GIE = 1;

    // INTVEN0 中断模式选择位
    // 0：默认中断模式
    // 1：向量中断模式（芯片配置字 INTVEN1（CFG_WD0<11>）必须为 1）
    INTVEN0 = 1;

    //中断向量表选择位
    INTV1 = 1;
    INTV0 = 1;

    //发送/接收使能
    RX1EN = 1;
    TX1EN = 1;
}

/**
 * UART 中断
 * @brief
 *
 */
void isr(void) interrupt
{
    //接收1中断标志位=1 , 接收1中断使能=1
    if (RX1IE == 1 && RX1IF == 1)
    {
        rxbuf = RX1B;
        // 空标志位 TRMT1 = 1时 空闲
        while (!TRMT1)
            ;
        TX1B = rxbuf;
    }
}

/**
 * UART 中断
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

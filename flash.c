/**
 * @file flash.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-14 10:06:14
 *
 * @copyright Copyright (c) 2022
 *
 */
#define CLRWDT()    \
    {               \
        __Asm CWDT; \
    } //宏定义清狗指令

#include "sys.h"

unsigned int flash_read(unsigned int address)
{
    unsigned int value = 0;
    unsigned char gie_bk = GIE;
    CLRWDT();
    while (GIE)
    {
        GIE = 0;
    }
    //使能数据读取
    DATARDEN = 1;
    //获取数据的地址的高/低位
    FRAH = address >> 8;
    FRAL = address;
    //读取标志
    DATARDTRG = 1;
    //等待读取
    while (DATARDTRG)
        ;
    //查表读指令
    __Asm TBR;
    //数据处理
    value = ROMDH << 8 | ROMDL;
    //退出AIP
    ROMCL = 0x00;
    GIE = gie_bk;
    return value;
}

/******************************************************
函数名：void RAMclear(void)
描  述：RAM区数据清零，RAM区地址0x0000~0x03FF
输入值：无
输出值：无
返回值：无
*******************************************************/
void RAMclear(void)
{
    for (IAAH = 0; IAAH <= 0x03; IAAH++)
    {
        for (IAAL = 0; IAAL < 0xFF; IAAL++)
            IAD = 0x00;
        IAD = 0x00;
    }
}
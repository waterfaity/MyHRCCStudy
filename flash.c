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
    } //�궨���幷ָ��

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
    //ʹ�����ݶ�ȡ
    DATARDEN = 1;
    //��ȡ���ݵĵ�ַ�ĸ�/��λ
    FRAH = address >> 8;
    FRAL = address;
    //��ȡ��־
    DATARDTRG = 1;
    //�ȴ���ȡ
    while (DATARDTRG)
        ;
    //����ָ��
    __Asm TBR;
    //���ݴ���
    value = ROMDH << 8 | ROMDL;
    //�˳�AIP
    ROMCL = 0x00;
    GIE = gie_bk;
    return value;
}

/******************************************************
��������void RAMclear(void)
��  ����RAM���������㣬RAM����ַ0x0000~0x03FF
����ֵ����
���ֵ����
����ֵ����
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
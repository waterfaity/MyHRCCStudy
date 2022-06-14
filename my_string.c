/**
 * @file my_string.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-14 15:06:56
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "sys.h"

char char_str[20];
char char_str_2[5] = {'a', 'b', '\0'};
long char_to_num(char *data)
{
    long num = 0;
    return num;
}

char *float_to_char(float num)
{
    unsigned long addr_index = 0;
    unsigned long abs_num = num;

    char temp[5];
    // ------- ����

    if (num < 0)
    {
        // ȡ����
        char_str_2[addr_index++] = '-';
        abs_num = (long)(-num);
    }
    else
    {
        //ȡ��
        abs_num = (long)num;
    }
    // ------- ��������

    //ȡ�������������� ���� �� num = 12345  ȡֵΪ temp = {5,4,3,2,1}
    int num_index = 0;
    temp[num_index++] = abs_num % 10 + '0';
    do
    {
        abs_num /= 10;
        temp[num_index++] = abs_num % 10 + '0';

    } while (abs_num > 10);
    //����˳�򷴹���
    int i = 0;
    for (i = 0; i < num_index; i++)
    {
        char_str_2[addr_index++] = temp[num_index - 1 - i];
    }

    // ------- С������

    if (num - (signed long)num != 0)
    {
        //��С������
        char_str_2[addr_index++] = '.';
    }

    char_str_2[addr_index++] = '\0';

    return (char *)char_str_2;
}

const char itoa_index[] = "0123456789"; // itoa ������
char *num_to_char(signed long num)
{
    signed long unum = num; /* �м���� */
    signed long i = 0, j, k = 0;
    char temp;
    /* ȷ��unum��ֵ */
    if (num < 0) /* ʮ���Ƹ��� */
    {
        unum = -num;
        char_str[i++] = '-';
    }
    /* ���� */
    do
    {
        char_str[i++] = itoa_index[unum % 10];
        unum /= 10;
    } while (unum);
    char_str[i] = '\0';

    /* ת�� */
    if (char_str[0] == '-')
    {
        k = 1; /* ʮ���Ƹ��� */
    }

    for (j = 0; j < (i - k) / 2; j++)
    {
        temp = char_str[j + k];
        char_str[j + k] = char_str[i - j - 1];
        char_str[i - j - 1] = temp;
    }
    return (char *)char_str;
}

char *char_add_num(char *str, signed long num);

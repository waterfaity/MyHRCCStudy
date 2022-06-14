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
    // ------- 负号

    if (num < 0)
    {
        // 取负号
        char_str_2[addr_index++] = '-';
        abs_num = (long)(-num);
    }
    else
    {
        //取整
        abs_num = (long)num;
    }
    // ------- 整数部分

    //取出整数部分数字 倒序 如 num = 12345  取值为 temp = {5,4,3,2,1}
    int num_index = 0;
    temp[num_index++] = abs_num % 10 + '0';
    do
    {
        abs_num /= 10;
        temp[num_index++] = abs_num % 10 + '0';

    } while (abs_num > 10);
    //整数顺序反过来
    int i = 0;
    for (i = 0; i < num_index; i++)
    {
        char_str_2[addr_index++] = temp[num_index - 1 - i];
    }

    // ------- 小数部分

    if (num - (signed long)num != 0)
    {
        //有小数部分
        char_str_2[addr_index++] = '.';
    }

    char_str_2[addr_index++] = '\0';

    return (char *)char_str_2;
}

const char itoa_index[] = "0123456789"; // itoa 索引表
char *num_to_char(signed long num)
{
    signed long unum = num; /* 中间变量 */
    signed long i = 0, j, k = 0;
    char temp;
    /* 确定unum的值 */
    if (num < 0) /* 十进制负数 */
    {
        unum = -num;
        char_str[i++] = '-';
    }
    /* 逆序 */
    do
    {
        char_str[i++] = itoa_index[unum % 10];
        unum /= 10;
    } while (unum);
    char_str[i] = '\0';

    /* 转换 */
    if (char_str[0] == '-')
    {
        k = 1; /* 十进制负数 */
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

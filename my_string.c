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
#include "my_math.h"
#include <string.h>
long char_to_num(char *data)
{
    long num = 0;
    return num;
}

char temp_double_to_char[100];
/**
 * @brief  ������ת�ַ�
 *
 * @param num
 * @return char*
 */
char *doble_to_char(double num)
{

    my_memset(temp_double_to_char, '\0', 100);
    long addr_index = 0;
    unsigned long abs_num = num;

    char temp[10];
    // ------- ����

    if (num < 0)
    {
        // ȡ����
        temp_double_to_char[addr_index++] = '-';
        abs_num = (long)(-num);
    }
    else
    {
        //ȡ��
        abs_num = (long)num;
    }
    // ------- ��������

    //ȡ�������������� ���� �� num = 12345  ȡֵΪ temp = {5,4,3,2,1}
    int temp_index = 0;
    do
    {
        temp[temp_index++] = abs_num % 10 + '0';
        abs_num /= 10;

    } while (abs_num >= 1);
    //����˳�򷴹���
    int i = 0;
    for (i = 0; i < temp_index; i++)
    {
        temp_double_to_char[addr_index++] = temp[temp_index - 1 - i];
    }

    // ------- С������

    if (num - (long)num != 0)
    {
        //��С������ -> 0.12345
        temp_double_to_char[addr_index++] = '.';
        //����С���̺�7λ *10000000 ������ -> 1234500
        double decimal = (num - (long)num);

        decimal = decimal < 0 ? (-decimal) : decimal;
        abs_num = (long)(decimal * 10000000L);

        //��¼���һ��0��λ�� , ���˶����0  ->12345
        int last_zero_index = 0;
        int is_last_zero = 1;
        temp_index = 0;
        do
        {
            if (abs_num % 10 == 0 && is_last_zero)
            {
                is_last_zero = 1;
                last_zero_index = temp_index;
            }
            else
            {
                is_last_zero = 0;
            }

            temp[temp_index++] = abs_num % 10 + '0';
            abs_num /= 10;
        } while (abs_num >= 1);
        for (i = 0; i < temp_index - last_zero_index; i++)
        {
            temp_double_to_char[addr_index++] = temp[temp_index - 1 - i];
        }
    }
    //ĩβ��0
    temp_double_to_char[addr_index++] = '\0';
    return (char *)temp_double_to_char;
}

char temp_num_to_char[100];
/**
 * @brief ���ֻ��ַ�
 *
 * @param num
 * @return char*
 */
char *num_to_char(long num)
{

    my_memset(temp_num_to_char, '\0', 100);
    long addr_index = 0;
    unsigned long abs_num = num;

    char temp[10];
    // ------- ����

    if (num < 0)
    {
        // ȡ����
        temp_num_to_char[addr_index++] = '-';
        abs_num = (long)(-num);
    }
    else
    {
        //ȡ��
        abs_num = (long)num;
    }
    // ------- ��������

    //ȡ�������������� ���� �� num = 12345  ȡֵΪ temp = {5,4,3,2,1}
    int temp_index = 0;
    do
    {
        temp[temp_index++] = abs_num % 10 + '0';
        abs_num /= 10;

    } while (abs_num >= 1);
    //����˳�򷴹���
    int i = 0;
    for (i = 0; i < temp_index; i++)
    {
        temp_num_to_char[addr_index++] = temp[temp_index - 1 - i];
    }
    //ĩβ��0
    temp_num_to_char[addr_index++] = '\0';
    return (char *)temp_num_to_char;
}
void *my_memset(void *s, int c, int n)
{
    char *xs = s;

    while (n--)
        *xs++ = c;
    return s;
}
char temp_char_add[100];
char *char_add_num(const char *str, double num)
{

    my_memset(temp_char_add, '\0', 100);
    char *doubleChar = doble_to_char(num);
    int addr_index = 0;
    while (*str != '\0')
    {
        temp_char_add[addr_index++] = *(str++);
    }
    while (*doubleChar != '\0')
    {
        temp_char_add[addr_index++] = *(doubleChar++);
    }
    return (char *)temp_char_add;
}

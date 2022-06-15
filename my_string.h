/**
 * @file my_string.h
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-14 15:06:35
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

extern void *my_memset(void *p1, int c, int n);
extern long char_to_num(char *data);

extern char *doble_to_char(double num);

extern char *num_to_char(signed long num);

extern char *char_add_num(const char *str, double num);

#endif

/**
 * @file function.h
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-24 14:08:81
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __TIMER_H__
#define __TIMER_H__

 //1s计次
#define TIMES_ONE_SECOND 10000
//1秒标志
unsigned int is_timer_one_second;
//计数
unsigned int timer_count;


void handle_one_second(void);

#endif

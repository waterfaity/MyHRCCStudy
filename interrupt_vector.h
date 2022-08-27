/**
 * @file interrupt_vector.h
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-24 16:08:65
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "boolean.h"

#ifndef __INTERRUPT_VECTOR_H__
#define __INTERRUPT_VECTOR_H__

extern bool is_interrupt_adc;
extern bool is_interrupt_key;
extern bool is_interrupt_pin_zero;
/**
 * @brief 初始化向量中断
 *
 */
void init_interrupt_vector(void);

#endif

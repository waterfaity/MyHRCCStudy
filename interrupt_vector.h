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
#ifndef __INTERRUPT_VECTOR_H__
#define __INTERRUPT_VECTOR_H__

extern unsigned int is_interrupt_adc;
/**
 * @brief 初始化向量中断
 *
 */
void init_interrupt_vector(void);

#endif

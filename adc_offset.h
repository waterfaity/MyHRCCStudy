/**
 * @file adc_offset.h
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-14 09:06:82
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ADC_OFFSET_H__
#define __ADC_OFFSET_H__
 /**
  * @brief 初始化adc_offset
  *
  */
void init_adc_offset(void);
/**
 * @brief adc_offset 中断
 *
 */
void isr_adc_ntc(void);
/**
 * @brief 处理adc数据
 *
 */
void handle_adc_ntc_value(void);

#endif

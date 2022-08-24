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
  * @brief ��ʼ��adc_offset
  *
  */
void init_adc_offset(void);
/**
 * @brief adc_offset �ж�
 *
 */
void isr_adc_ntc(void);
/**
 * @brief ����adc����
 *
 */
void handle_adc_ntc_value(void);

#endif

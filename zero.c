/**
 * @file zero.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-27 16:08:66
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "sys.h"
 /**
  * @brief PA6端口
  *
  */
void init_zero(void) {

    //数字输入输出
    ANSH2 = 1;
    //输入
    PAT6 = 1;
	//下拉电位,防止开机触发一次中断
	PAPD6 = 1;
    //PEG2<1:0>：PINT5~PINT4 触发边沿选择位
    // 00：PINT5~PINT4 下降沿触发
    // 01：PINT5~PINT4 上升沿触发
    // 1x：PINT5~PINT4 双沿触发
    //双沿触发
	PEG21 = 1; 
    //中断使能
    PIE4 = 1;
    //中断标志
    PIF4 = 0;
}

void isr_zero(void) {
	PIF4 = 0;
    is_interrupt_pin_zero = 1;
}
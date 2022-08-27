/**
 * @file heat.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-26 09:08:05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h"
 /**
  * @brief 引脚FRS_KZ -> PA1(AIN1)
  *
  */
void init_heat() {
    //输出
    PAT1 = 0;
    //数字输出
    ANSL1 = 1;
    //强电流(初始化为弱电流)
    PA1DS = 1;
    //低电平(初始化为低电平)
    PA1 =1;
}
/**
 * @brief 电流切换
 *
 */
void heat_switch_current(int strong) {
    PA1DS = strong;
}


/**
 * @file function.c
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-08-24 14:08:69
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sys.h" 

bool is_timer_one_second = false;

/**
 * @brief ����1s�ж�
 *
 */
void handle_one_second(void) {

  if (!is_timer_one_second)  return;
  is_timer_one_second = false;

  //��ʼadc����ת��
  ADTRG = 1;

}


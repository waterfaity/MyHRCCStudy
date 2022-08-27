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
  * @brief ����FRS_KZ -> PA1(AIN1)
  *
  */
void init_heat() {
    //���
    PAT1 = 0;
    //�������
    ANSL1 = 1;
    //ǿ����(��ʼ��Ϊ������)
    PA1DS = 1;
    //�͵�ƽ(��ʼ��Ϊ�͵�ƽ)
    PA1 =1;
}
/**
 * @brief �����л�
 *
 */
void heat_switch_current(int strong) {
    PA1DS = strong;
}


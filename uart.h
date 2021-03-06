/**
 * @file uart.h
 * @author WaterFairy (995637517@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2022-06-08 09:06:56
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __UART_H__
#define __UART_H__

void init_uart(void);

void uart_send(const char *data);

void uart_send_char(char *data);

void uart_send_interrupt(const char *data);

void uart_send_interrupt_2(unsigned char *data);
void uart_send_interrupt_3(char *data);

void uart_send_num(signed long num);

void isr_uart(void);

#endif

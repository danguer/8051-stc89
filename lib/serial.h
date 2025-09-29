#include "stc89.h"

#ifndef _STC89_SERIAL_H_
#define _STC89_SERIAL_H_

#define UART_TIMER1 1
#define UART_TIMER2 2

void uart_init(int uart_timer, unsigned int baudrate);
void uart_send_byte(char tx_data);
void uart_send(char *str);

#endif
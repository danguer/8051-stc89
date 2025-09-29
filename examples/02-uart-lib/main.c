#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1

void main()
{
    uart_init(UART_TO_USE, 9600);

    while(1) {
        uart_send("hello world4\r\n");
		delay(1000);
    }
}

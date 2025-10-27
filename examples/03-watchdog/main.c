#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1

void main()
{
    uart_init(UART_TO_USE, 9600);

    // configure watchdog to use prescaler 64
    // this is around 2.27 seconds
    // to calculate is:
    // WDT overflow time = (N * Pre-scale * 32768) / SYSclk
    // When MCU in 12T mode, N=12; When MCU in 6T mode, N=6
    // Source: page 18 of datasheet
    // in this case is:
    // (12*64*32768) / 11059200
    // or 2.275555556
    
    uart_send("reset; enabling watchdog EN_WDT\r\n");
    WDT_CONTR |= EN_WDT | WDT_PRESCALE_64;
    
    unsigned int tries = 10;
    while(1) {
        if (tries > 0) {
            uart_send("clearing watchdog CLR_WDT\r\n");
            WDT_CONTR |= CLR_WDT;
            tries--;
		    delay(500);
        } else {
            uart_send("waiting for watchdog to reset...\r\n");
            delay(2500);
        }
    }
}

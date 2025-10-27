#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1

int putchar (int c) {
    uart_send_byte(c);
    return c;
}

void main()
{
    unsigned char copy_th = 0;
    unsigned char copy_tl = 0;

    uart_init(UART_TO_USE, 9600);

    // clear Timer0 registers and set:
    // C/T will enable use as a counter 
    //   (when exernal T0 goes from high to low)
    // Mode = 1 16 bit counter
    TMOD = (TMOD & 0xF0) | T0_CT | T0_M0;

    // in case, reset timer to start counting from zero
    TL0 = TH0 = 0;

    // enable timer
    TR0 = 1;
    while(1) {
        if (copy_tl != TL0 || copy_th != TH0) {
            unsigned int total_count = (TH0 << 8) | TL0;
            copy_tl = TL0;
            copy_th = TH0;
            printf(
                "Changed count: %u\r\n",
                total_count
            );
        }
    }
}

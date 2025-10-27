#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1

volatile char button_pressed = 0;

int putchar (int c) {
    uart_send_byte(c);
    return c;
}

void int0(void) __interrupt (0)
{
    if (button_pressed < 0xFF) {
        button_pressed++;
    } else {
        button_pressed = 1;
    }
}

void main()
{
    uart_init(UART_TO_USE, 9600);
    printf("enabling external interrupt\r\n");
    EA = 1; // enable interruptions
    EX0 = 1; // enable INT0 interruption
    IT0 = 1; // enable on low
    char last_button_pressed = button_pressed;
    
    while(1) {
        if (last_button_pressed != button_pressed) {
            printf("Button pressed %d times\r\n", button_pressed);
            last_button_pressed = button_pressed;
        } else {
            printf("Waiting for interrupt, connect a button on P3.2\r\n");
        }
        delay(1000);
    }
}

#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1
volatile unsigned char timer_overflow_times = 0;
volatile unsigned char time_finished = 0;

int putchar (int c) {
    uart_send_byte(c);
    return c;
}

void timer0_interrupt(void) __interrupt (1)
{
    if (timer_overflow_times > 0) {
        timer_overflow_times--;
    } else {
        // disable timer
        time_finished = 1;
        TR0 = 0;
    }
}

void start_timer(unsigned char overflow_times, unsigned int timer_base) {
    time_finished = 0;
    timer_overflow_times = overflow_times;
    TH0 = timer_base >> 8; 
    TL0 = timer_base & 0xFF;

    // start timer
    TR0 = 1;
}

void main()
{
    unsigned int seconds_elapsed = 0;
    uart_init(UART_TO_USE, 9600);
    EA = 1; // enable interruptions
    ET0 = 1; // enable Timer0 interruption

    // calculate how many times needs to run the Timer0 for a second
    unsigned long cycles_in_a_second = FOSC / 12;
    unsigned char overflow_times = (cycles_in_a_second / 0xFFFF);
    unsigned int timer_base = 0xFFFF - (cycles_in_a_second - (overflow_times * 0xFFFFl));
    // clear Timer0 registers and set:
    // Mode = 1 16 bit counter
    TMOD = (TMOD & 0xF0) | T0_M0;

    // set timer
    start_timer(overflow_times, timer_base);
    while(1) {
        if (time_finished) {
            seconds_elapsed++;
            printf("%u seconds elapsed...\r\n", seconds_elapsed);

            //reset timer
            start_timer(overflow_times, timer_base);
        }
    }
}

#include "../../lib/stc89.h"
#include "../board_defs.h"
#include "../../lib/utils.h"
#include "../../lib/serial.h"
#include <stdio.h>
#define UART_TO_USE UART_TIMER1
volatile unsigned char int0_flag = 0;
volatile unsigned char timer_overflow_times = 0;

int putchar (int c) {
    uart_send_byte(c);
    return c;
}

void int0_interrupt(void) __interrupt (0)
{
    int0_flag = 1;

    // disable timer until is reset
    TR0 = 0;
}

void timer0_interrupt(void) __interrupt (1)
{
    timer_overflow_times += 1;
}

void main()
{
    uart_init(UART_TO_USE, 9600);
    EA = 1; // enable interruptions

    EX0 = 1; // enable INT0 interruption
    IT0 = 1; // enable INT0 when goes from HIGH to LOW

    ET0 = 1; // enable Timer0 interruption

    // clear Timer0 registers and set:
    // GATE it will only set a signal when P3.2 is high
    // Mode = 1 16 bit counter
    TMOD = (TMOD & 0xF0) | T0_GATE | T0_M0;

    // in case, reset timer to start counting from zero
    TL0 = TH0 = 0; 

    // disable pull-up for INT0
    P3_2 = 0;

    // enable timer
    TR0 = 1;
    while(1) {
        if (int0_flag) {
            // button was release so calculate how many times
            // the timer has overflow and the current counter
            // to calculate how much time has elapsed
            float ms_per_instructions = 1000.0 / (FOSC / 12.0);
            unsigned int time_elapsed = (TH0 << 8) | TL0;
            float ms_time_elapsed = ((timer_overflow_times * 65535.0) + time_elapsed) * ms_per_instructions;
            unsigned int ms_time_elapsed_int = (int)ms_time_elapsed;
            unsigned int ms_time_elapsed_decimal = (int)((ms_time_elapsed-ms_time_elapsed_int)*100);
            printf(
                "Button released, took: %u.%02ums",
                ms_time_elapsed_int,
                ms_time_elapsed_decimal
            );

            // reset timer
            timer_overflow_times = 0;
            int0_flag = 0;
            TL0 = TH0 = 0;

            // enable timer again
            TR0 = 1;
        }

        if (timer_overflow_times) {
            printf("Interrupt timer, timer_flag: %d\r\n", timer_overflow_times);
        }
    }
}

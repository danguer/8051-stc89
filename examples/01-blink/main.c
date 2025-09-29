#include "../../lib/stc89.h"

#define FOSC 11059200L

void run_timer_cycle(unsigned int cycle)
{
    // set timer0 mode 1 (16 bit mode)
    TMOD = 0x01;

    // set timer to cycle part
    TL0 = cycle & 0xFF;
    TH0 = cycle >> 8;

    // start the timer
    TR0 = 0x1;

    // wait until timer flag is raised
    while(!TF0);

    // stop timer and clear flag
    TR0 = 0x0;
    TF0 = 0x0;
}

void delay(unsigned int milliseconds)
{
    // in 8051 each instruction takes 12 cycles
    // so the oscillator (FOSC) divided by 12000
    // will give the number of cycles to run per millisecond
    // 12000 = 12 cycles * 1000us

    unsigned long total_cycles_counter = FOSC/12000 * milliseconds;

    unsigned int total_cycles = total_cycles_counter >> 16;
    unsigned int remain_cycles = 0xFFFF - (total_cycles_counter & 0xFFFF);

    // run a full cycle
    for (int i=0; i<total_cycles; i++) {
        run_timer_cycle(0x0);
    }

    // check if run partial cycle
    if (remain_cycles > 0) {
        run_timer_cycle(remain_cycles);
    }
}

void main(void)
{
    while(1)
    {
         P3 = 0x00; // LED on
         delay(1000);
         P3 = 0xFF; // LED off
         delay(1000);
    }
}
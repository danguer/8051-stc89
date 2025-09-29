#include "utils.h"
#include "board_defs.h"

// for timer
#if DELAY_TIMER == 0
    #define REG_DTL TL0
    #define REG_DTH TH0
    #define REG_START_TIMER TR0
    #define REG_FLAG_TIMER TF0
#elif DELAY_TIMER == 1
    #define REG_DTL TL1
    #define REG_DTH TH1
    #define REG_START_TIMER TR1
    #define REG_FLAG_TIMER TF1
#elif DELAY_TIMER == 2
    #define REG_DTL RCAP2L
    #define REG_DTH RCAP2H
    #define REG_START_TIMER TR2
    #define REG_FLAG_TIMER TF2
#else
#error "DELAY_TIMER only can be 0,1 or 2"
#endif

void run_timer_cycle(unsigned int cycle)
{
    // set timer0 mode 1 (16 bit mode)
#if DELAY_TIMER == 0
    // reset M0 and M1
    TMOD &= ~(T0_M0 | T0_M1);
    // set M0 only
    TMOD |= T0_M0;
#elif DELAY_TIMER == 1
    // reset M0 and M1
    TMOD &= ~(T1_M0 | T1_M1);
    // set M0 only
    TMOD |= T1_M0;
#elif DELAY_TIMER == 2
    //enable 16bit capture
    RCLK = TCLK = 0;
    CP_RL2 = 1;
    EXEN2 = 0;
#endif
    // set timer to cycle part
    REG_DTL = cycle & 0xFF;
    REG_DTH = cycle >> 8;

    // start the timer
    REG_START_TIMER = 0x1;

    // wait until timer flag is raised
    while(!REG_FLAG_TIMER);

    // stop timer and clear flag
    REG_START_TIMER = 0x0;
    REG_FLAG_TIMER = 0x0;
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
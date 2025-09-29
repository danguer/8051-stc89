#include "serial.h"
#include "board_defs.h"
#include "utils.h"

void uart_init(int uart_timer, unsigned int baudrate)
{
    unsigned int baudrate_uint;
    // set 8bit shift register (mode 1)
    SM0 = 0;
    SM1 = 1;

    if (uart_timer == UART_TIMER1) {
        baudrate_uint = (256 - (1.0*FOSC/12/32/baudrate) + 0.5);
        TMOD &= ~(T1_M1 | T1_M0);
        TMOD |= T1_M1;

        TH1 = baudrate_uint;
        TL1 = 0;

        // start Timer1
        TR1 = 1;
    } else if (uart_timer == UART_TIMER2) {
        // formula is from page 102 of datasheet
        baudrate_uint = 0xFFFF - (FOSC/(baudrate*32.0));

        // enable Timer2 for Transmit and Receive
        RCLK = TCLK = 1;

        RCAP2H = baudrate_uint >> 8;
        RCAP2L = baudrate_uint;

        // start Timer2
        TR2 = 1;
    }
}

void uart_send_byte(char tx_data)
{
    SBUF = tx_data; /* Load char in SBUF register */
    while (TI==0);  /* Wait until stop bit transmit */
    TI = 0;         /* Clear TI flag */
}

void uart_send(char *str)
{
    for(int i=0; str[i]!=0; i++)
    {
        uart_send_byte(str[i]);    /* Call transmit data function */
    }
}

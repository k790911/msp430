#include <msp430.h> 
#include <myUart.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    char wel[] = "Welcome to Serial Port Programming!!!";
    volatile char i = 0;

    P4SEL |= BIT4 | BIT5;

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;

    while(1) {
        write_uart_string(wel);
        write_uart_byte('A');
        write_uart_uint(4000);

        write_uart_byte('\r');
        write_uart_byte('\n');
        /*
        i = 0;
        while(wel[i] != '\0') {
            UCA1TXBUF = wel[i];
            while(UCA1STAT & UCBUSY);
            i++;
        }
        UCA1TXBUF = 0x0A;
        while(UCA1STAT & UCBUSY);
        UCA1TXBUF = 0x0D;
        while(UCA1STAT & UCBUSY);
        */
        __delay_cycles(600000);
    }
}

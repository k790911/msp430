#include <msp430.h>
#include <myUart.h>

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P4SEL |= BIT4 | BIT5; // 내부 UART 포트 to PC 세팅, serial

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;

    while(1) {
        __delay_cycles(1000000);

        write_uart_string("hello world");
    }
}

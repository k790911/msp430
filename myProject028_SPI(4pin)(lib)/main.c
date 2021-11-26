#include <msp430.h>
#include <myUart.h>

void myUartInit();

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P3SEL |= BIT0 + BIT1;                     // P3.0, 1 option select
    P3SEL |= BIT2;                            // P3.2 option select
    P2SEL |= BIT7;                          // slave select

    myUartInit();

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 |= UCSYNC + UCMSB;
    UCB0CTL0 |= UCMODE_2;
    UCB0CTL0 |= UCCKPH; // inactive high, capture->change
    UCB0CTL1 &= ~UCSWRST;

    UCB0IE |= UCRXIE;
    __bis_SR_register(GIE);
}

#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
    unsigned char ch;
    ch = UCB0RXBUF;
    unsigned char tmp[8] = {0};
    int i;

    if (ch == 0xFF) {
        P4OUT ^= BIT7;
    }

    write_uart_string("data: ");

    for (i = 0; i < 8; i++) {
        tmp[i] = ch & 0x80;
        if (tmp[i] == 0x80) {
            write_uart_string("1");
        }
        else if(tmp[i] == 0x00) {
            write_uart_string("0");
        }
        else {
            write_uart_string("x");
        }
        ch <<= 1;
    }

    write_uart_byte('\r');
    write_uart_byte('\n');

    P1OUT ^= BIT0;

    UCB0IFG = 0x00;
}

void myUartInit() {
    P4SEL |= BIT4 | BIT5; // 내부 UART 포트 to PC 세팅, serial

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;
}

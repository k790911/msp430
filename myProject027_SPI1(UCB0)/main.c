#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P2DIR |= BIT0;
    P2OUT |= BIT0;

    P3SEL |= BIT0 + BIT1;                     // P3.0,1 option select
    P3SEL |= BIT2;                            // P3.2 option select

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 |= UCMST + UCSYNC + UCCKPL;    // 3-pin, 8-bit SPI master, Clock polarity high, MSB
    UCB0CTL1 |= UCSSEL_1;                     // ACLK
    UCB0BR0 = 3;                              // /2
    UCB0BR1 = 0;                              //
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    P2OUT &= ~BIT0;
    __delay_cycles(5);
    P2OUT |= BIT0;

    while(1) {

        //while (UCB0IFG & UCTXIFG);       // USCI_A0 TX buffer ready?
        P1OUT |= BIT0;
        UCB0TXBUF = 'A';
        while(UCB0STAT & UCBUSY);
        __delay_cycles(2000000);
        P1OUT &= ~BIT0;

        P4OUT |= BIT7;
        UCB0TXBUF = 'B';
        while(UCB0STAT & UCBUSY);
        __delay_cycles(2000000);
        P4OUT &= ~BIT7;

        P1OUT |= BIT0;
        P4OUT |= BIT7;
        UCB0TXBUF = 'C';
        while(UCB0STAT & UCBUSY);
        __delay_cycles(2000000);
        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;
    }
}

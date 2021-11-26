#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P3SEL |= BIT3 + BIT4;                     // P3.3,4 option select
    P2SEL |= BIT7;                            // P2.7 option select

    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 |= UCMST + UCSYNC + UCCKPL;    // 3-pin, 8-bit SPI master, Clock polarity high, MSB
    UCA0CTL1 |= UCSSEL_1;                     // ACLK
    UCA0BR0 = 3;                              // /2
    UCA0BR1 = 0;                              //
    UCA0MCTL = 0;                             // No modulation
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    while(1) {

        //while (!(UCA0IFG & UCTXIFG));       // USCI_A0 TX buffer ready?
        P1OUT |= BIT0;
        UCA0TXBUF = 'A';
        while(UCA0STAT & UCBUSY);
        __delay_cycles(2000000);
        P1OUT &= ~BIT0;

        P4OUT |= BIT7;
        UCA0TXBUF = 'B';
        while(UCA0STAT & UCBUSY);
        __delay_cycles(2000000);
        P4OUT &= ~BIT7;

        P1OUT |= BIT0;
        P4OUT |= BIT7;
        UCA0TXBUF = 'C';
        while(UCA0STAT & UCBUSY);
        __delay_cycles(2000000);
        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;
    }
}

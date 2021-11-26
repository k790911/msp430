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
    UCA0CTL0 |= UCSYNC + UCCKPL;      // 3-pin, 8-bit SPI slave, Clock polarity high, MSB
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

    __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, enable interrupts
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    unsigned char ch;
    ch = UCA0RXBUF;
    if (ch == 'A') {
        P1OUT |= BIT0;
        __delay_cycles(500000);
        P1OUT &= ~BIT0;
    }
    else if (ch == 'B') {
        P4OUT |= BIT7;
        __delay_cycles(500000);
        P4OUT &= ~BIT7;
    }
    else {
        P1OUT |= BIT0;
        P4OUT |= BIT7;
        __delay_cycles(500000);
        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;
    }
    UCA0IFG = 0x00;
}

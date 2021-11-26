#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P3SEL |= BIT0 + BIT1;                     // P3.0,1 option select
    P3SEL |= BIT2;                            // P3.2 option select

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 |= UCSYNC + UCCKPL;      // 3-pin, 8-bit SPI slave, Clock polarity high, MSB
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    UCB0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

    __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, enable interrupts
}

#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
    unsigned char ch;
    ch = UCB0RXBUF;
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
    UCB0IFG = 0x00;
}

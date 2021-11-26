#include <msp430.h>

#define CSON(); P2OUT &= ~BIT7;
#define CSOFF(); P2OUT |= BIT7;

void main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P3SEL |= BIT0 + BIT1;                     // P3.0, 1 option select
    P3SEL |= BIT2;                            // P3.2 option select

    P2DIR |= BIT7;                          // slave select
    CSOFF();

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 |= UCSYNC + UCMSB + UCMST;
    //UCB0CTL0 |= UCMODE_2; // master useless
    UCB0CTL0 |= UCCKPH; // inactive high, capture->change
    UCB0CTL1 |= UCSSEL_1;
    UCB0BR0 = 3;
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;

    UCB0IE |= UCTXIE;
    __bis_SR_register(GIE);

    while(1) {

        CSON();

        while (UCB0IFG & UCTXIFG);  // USCI_A0 TX buffer ready
        UCB0TXBUF = 0x11;
        //while(UCB0STAT & UCBUSY);

        P1OUT |= BIT0;
        __delay_cycles(1000000);

        CSOFF();

        P1OUT &= ~BIT0;
        __delay_cycles(1000000);

        CSON();

        while (UCB0IFG & UCTXIFG);
        UCB0TXBUF = 0x88;

        P4OUT |= BIT7;
        __delay_cycles(1000000);

        CSOFF();

        P4OUT &= ~BIT7;
        __delay_cycles(1000000);
    }
}
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{

    UCB0IFG = 0x00;
}

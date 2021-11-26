#include <msp430.h> 

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR &= ~BIT1; // right
    P1OUT |= BIT1; // pull up resistor
    P1REN |= BIT1; // pull up enable

    P1IE |= BIT1;
    P1IES |= BIT1;
    P1IFG &= ~BIT1;

    P2DIR &= ~BIT1; // left
    P2OUT |= BIT1; // pull up resistor
    P2REN |= BIT1; // pull up enable

    P2IE |= BIT1;
    P2IES |= BIT1;
    P2IFG &= ~BIT1;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P3SEL |= BIT3 | BIT4;
    // UART setting
    UCA0CTL1 |= UCSWRST;
    UCA0CTL1 |= UCSSEL_1;
    UCA0BR0 = 3;
    UCA0BR1 = 0x00;
    UCA0MCTL = 0x06;
    UCA0CTL0 = 0x00;
    UCA0CTL1 &= ~UCSWRST;
/*
    while(1) {
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;
        UCA0TXBUF = 'A';
        while(UCA0STAT & UCBUSY);

        __delay_cycles(1000000);

        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;
        UCA0TXBUF = 'B';
        while(UCA0STAT & UCBUSY);

        __delay_cycles(1000000);

        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;
        UCA0TXBUF = 'C';
        while(UCA0STAT & UCBUSY);

        __delay_cycles(1000000);

        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;__delay_cycles(300000);
        P1OUT |= BIT0;__delay_cycles(300000); P1OUT &= ~BIT0;
        UCA0TXBUF = 'D';
        while(UCA0STAT & UCBUSY);

        __delay_cycles(1000000);

    }
    */
    __bis_SR_register(GIE);

    while(1);
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_isr(void) {

    P4OUT ^= BIT7;

    UCA0TXBUF = 'B';
    while(UCA0STAT & UCBUSY);

    P1IFG &= ~BIT1;
}

#pragma vector=PORT2_VECTOR
__interrupt void port2_isr(void) {

    P1OUT ^= BIT0;

    UCA0TXBUF = 'A';
    while(UCA0STAT & UCBUSY);

    P2IFG &= ~BIT1;
}

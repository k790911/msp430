#include <msp430.h> 

// myProject009_serial1

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = BIT0; P1OUT &= ~BIT0;
	P4DIR = BIT7; P4OUT &= ~BIT7;

	P3SEL |= BIT3 | BIT4;
	// UART setting
	UCA0CTL1 |= UCSWRST;
	UCA0CTL1 |= UCSSEL_1;
	UCA0BR0 = 3;
	UCA0BR1 = 0x00;
	UCA0MCTL = 0x06;
	UCA0CTL0 = 0x00;
	UCA0CTL1 &= ~UCSWRST;

	while(1) {

	    UCA0TXBUF = 'A';
	    while(UCA0STAT & UCBUSY);

        P1OUT |= BIT0;
        P4OUT &= ~BIT7;

	    __delay_cycles(800000);

	    UCA0TXBUF = 'B';
	    while(UCA0STAT & UCBUSY);

	    P1OUT &= ~BIT0;
	    P4OUT |= BIT7;

	    __delay_cycles(800000);
	}
}

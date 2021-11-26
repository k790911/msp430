#include <msp430.h> 

// myProject009_serial2

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

	UCA0IE |= UCRXIE;
	__bis_SR_register(GIE);

	while(1);
}
#pragma vector=USCI_A0_VECTOR
__interrupt void serial_ISR(void) {
    __disable_interrupt();
    char a = UCA0RXBUF;

    if (a == 'A') {
        P1OUT |= BIT0;
        __delay_cycles(500000);
        P1OUT &= ~BIT0;
    }
    else if (a == 'B') {
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
    __enable_interrupt();
}

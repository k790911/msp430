#include <msp430.h> 


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT2 | BIT3 | BIT4;
	P1OUT &= ~(BIT2 | BIT3 | BIT4);

	while(1) {
	    P1OUT |= BIT2;
	    __delay_cycles(1000000);
	    P1OUT &= ~BIT2;

        __delay_cycles(1000000);

        P1OUT |= BIT3;
        __delay_cycles(1000000);
        P1OUT &= ~BIT3;

        __delay_cycles(1000000);

        P1OUT |= BIT4;
        __delay_cycles(1000000);
        P1OUT &= ~BIT4;

        __delay_cycles(1000000);

	}
}

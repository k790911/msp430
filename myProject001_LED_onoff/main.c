#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = BIT0;
	P4DIR = BIT7;

	P1OUT &= ~BIT0;
	P4OUT &= ~BIT7;

	while(1){
	    P1OUT |= BIT0;
	    P4OUT |= BIT7;
	    __delay_cycles(800000);

	    P1OUT &= ~BIT0;
	    P4OUT &= ~BIT7;
	    __delay_cycles(3200000);
	}
}

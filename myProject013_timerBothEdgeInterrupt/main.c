#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	P1DIR &= ~BIT2;
	P1SEL |= BIT2;
	P1IE |= BIT2;

	TA0CTL |= TASSEL_2 + MC_2; // SMCLK 1Mhz, continuous mode
	TA0CCTL1 |= CM_3 + SCS + CCIS_0 + CAP + CCIE; // csc: synchronous capture

	__bis_SR_register(GIE);

	while(1) {

	}
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_ISR(void) {
    P1OUT ^= BIT0;
    TA0CCTL1 &= ~CCIFG;
}

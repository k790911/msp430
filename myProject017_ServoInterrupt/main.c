#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// TA0.3
	P1DIR |= BIT4;
	P1SEL |= BIT4;

	//switch setting
	P1DIR &= ~BIT1; // input
    P1OUT |= BIT1; // pull up r
    P1REN |= BIT1;
    P1IE |= BIT1;
    P1IES &= ~BIT1; // ¶¿ ¶§ on
    P1IFG &= ~BIT1;

	P2DIR &= ~BIT1;
	P2OUT |= BIT1;
	P2REN |= BIT1;
	P2IE |= BIT1;
	P2IES |= BIT1; // ´©¸¦ ¶§ on
	P2IFG &= ~BIT1;

	TA0CTL |= TASSEL_2 | MC_1;

	TA0CCR0 = 20000;
	TA0CCTL3 = OUTMOD_6;
	TA0CCR3 = 1500;

	__bis_SR_register(GIE);

	while(1) {

	    __delay_cycles(500000);

	    TA0CCR3 = 1500;
	}
}
#pragma vector=PORT1_VECTOR
__interrupt void port_1(void) {
    __disable_interrupt();
    TA0CCR3 = 500;

    __delay_cycles(100000);

    P1IFG &= ~BIT1;
    __enable_interrupt();
}

#pragma vector=PORT2_VECTOR
__interrupt void port_2(void) {
    __disable_interrupt();
    TA0CCR3 = 2500;

    __delay_cycles(100000);

    P2IFG &= ~BIT1;
    __enable_interrupt();
}

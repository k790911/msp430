#include <msp430.h> 

void myPWMInit();

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT2 | BIT3 | BIT4;
	P1OUT &= ~(BIT2 | BIT3); // IC input for digital up/down set

	P1SEL |= BIT4; // IC enable, PWM
	myPWMInit();
	volatile unsigned int i = 0;

	while(1) {

	    P1OUT |= BIT2;
	    P1OUT &= ~BIT3;

	    for (i = 0; i <= 1000; i++) {
	        TA0CCR3 = i;
	        __delay_cycles(10000);
	    }
	    for (i = 999; i > 0; i--) {
            TA0CCR3 = i;
            __delay_cycles(10000);
	    }

	    P1OUT &= ~BIT2;
	    P1OUT |= BIT3;

	    for (i = 0; i <= 1000; i++) {
	        TA0CCR3 = i;
	        __delay_cycles(10000);
	    }
	    for (i = 999; i > 0; i--) {
	        TA0CCR3 = i;
	        __delay_cycles(10000);
	    }

	}
}

void myPWMInit() {
    TA0CTL = TASSEL_2 + MC_1;
    TA0CCR0 = 1000;
    TA0CCTL3 = OUTMOD_6;
    TA0CCR3 = 0;
}

#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P3DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
	P3OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);

	while(1) {

        P3OUT |= BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5; // 0
        P3OUT &= ~(BIT6 + BIT7);
        __delay_cycles(1000000);

	    P3OUT |= BIT1 | BIT2; // 1
	    P3OUT &= ~(BIT0 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
	    __delay_cycles(1000000);

	    P3OUT |= BIT0 | BIT1 | BIT3 | BIT4 | BIT6; // 2
        P3OUT &= ~(BIT2 + BIT5 + BIT7);
        __delay_cycles(1000000);

        P3OUT |= BIT0 | BIT1 | BIT2 | BIT3 | BIT6; // 3
        P3OUT &= ~(BIT4 + BIT5 + BIT7);
        __delay_cycles(1000000);

        P3OUT |= BIT1 | BIT2 | BIT5 | BIT6; // 4
        P3OUT &= ~(BIT0 + BIT3 + BIT4 + BIT7);
        __delay_cycles(1000000);

        P3OUT |= BIT0 | BIT2 | BIT3 | BIT5 | BIT6; // 5
        P3OUT &= ~(BIT1 + BIT4 + BIT7);
        __delay_cycles(1000000);

        P3OUT |= BIT0 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6; // 6
        P3OUT &= ~BIT1;
        __delay_cycles(1000000);

        P3OUT |= BIT0 | BIT1 | BIT2 | BIT5; // 7
        P3OUT &= ~(BIT3 + BIT4 + BIT6 + BIT7);
        __delay_cycles(1000000);

        P3OUT |= BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6; // 8
        P3OUT &= ~BIT7;
        __delay_cycles(1000000);

        P3OUT |= BIT0 | BIT1 | BIT2 | BIT3 | BIT5 | BIT6; // 9
        P3OUT &= ~BIT4;
        __delay_cycles(1000000);

        P3OUT |= BIT7; // dot
        P3OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
        __delay_cycles(1000000);
	}
}

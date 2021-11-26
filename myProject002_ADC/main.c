#include <msp430.h> 

unsigned int data = 0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    int i = 0;

	P1DIR |= BIT0;
	P4DIR |= BIT7;

	P1OUT &= ~BIT0;
	P4OUT &= ~BIT7;

    for (i = 0; i < 3; i++) {

        P1OUT |= BIT0;
        P4OUT |= BIT7;

        __delay_cycles(300000);

        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;

        __delay_cycles(300000);
    }

	P6SEL |= BIT0; // P6.0 핀을 ADC 입력으로 설정함
	ADC12CTL0 = ADC12SHT02 + ADC12ON;
	ADC12CTL1 = ADC12SHP;
	ADC12MCTL0 = ADC12INCH_0;
	ADC12CTL0 |= ADC12ENC;

	while(1) {
	    P4OUT |= BIT7;

	    ADC12CTL0 |= ADC12SC;
	    while(!(ADC12IFG & BIT0));
	    data = ADC12MEM0;

	    if (data == 4095) {
	        for (i = 0; i < 6; i++) {
	            P1OUT |= BIT0;
	            __delay_cycles(300000);
	            P1OUT &= ~BIT0;
                __delay_cycles(300000);
            }
	    }
	    else if (data > 4000) {
	        for (i = 0; i < 5; i++) {
	            P1OUT |= BIT0;
	            __delay_cycles(300000);
	            P1OUT &= ~BIT0;
	            __delay_cycles(300000);
	        }
	    }
	    else if (data > 3000) {
            for (i = 0; i < 4; i++) {
                P1OUT |= BIT0;
                __delay_cycles(300000);
                P1OUT &= ~BIT0;
                __delay_cycles(300000);
            }
	    }
	    else if (data > 2000) {
	        for (i = 0; i < 3; i++) {
	            P1OUT |= BIT0;
	            __delay_cycles(300000);
	            P1OUT &= ~BIT0;
	            __delay_cycles(300000);
	        }
	    }
	    else if (data > 1000) {
            for (i = 0; i < 2; i++) {
                P1OUT |= BIT0;
                __delay_cycles(300000);
                P1OUT &= ~BIT0;
                __delay_cycles(300000);
            }
        }
	    else if (data <= 1000 && data >= 0){
	        for (i = 0; i < 1; i++) {
	            P1OUT |= BIT0;
	            __delay_cycles(300000);
	            P1OUT &= ~BIT0;
	            __delay_cycles(300000);
	        }
	    }
	    else {
            P1OUT &= ~BIT0;
        }

        P4OUT &= ~BIT7;
        __delay_cycles(300000);

	}
}

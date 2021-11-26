#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// TA2.1
	P2DIR |= BIT4;
	P2SEL |= BIT4;

	TA2CTL = TASSEL_2 + MC_1; // select smclk(1Mhz), up mode

	TA2CCR0 = 20000;
	TA2CCTL1 = OUTMOD_6; // PWM toggle/set
	TA2CCR1 = 0;

	while(1) {
	    /* 1500을 중심으로 500, 2500. -90도 90도를 왔다갔다함*/
        TA2CCR1 = 1500;  // 20000 중에 7.5%(1.5ms) duty cycle (0도)
        __delay_cycles(2000000);
	    TA2CCR1 = 1000; // 20000(20ms) 중에 5%(1ms) duty cycle (-90도), 우90
	    __delay_cycles(2000000);
        TA2CCR1 = 1500;  // 20000 중에 7.5%(1.5ms) duty cycle (0도)
        __delay_cycles(2000000);
        TA2CCR1 = 2000;  // 20000 중에 10%(2ms) duty cycle (90도), 좌90
        __delay_cycles(2000000);
        TA2CCR1 = 1500;  // 20000 중에 7.5%(1.5ms) duty cycle (0도)
        __delay_cycles(2500000);


	}
}

#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P2DIR |= (BIT5 | BIT4);
	P2SEL |= (BIT5 | BIT4);

	TA2CTL = TASSEL_2 + MC_1; // SMCLK : 1 MHz / Up mode CCR0
	TA2CCR0 = 1000; // Ŭ���� �� ������ �پ. (1�� 1Mhz ���̸� õ���� ��)
	TA2CCTL2 = OUTMOD_6; // PWM toggle/set
	TA2CCR2 = 100;
    TA2CCTL1 = OUTMOD_6; // PWM toggle/set
    TA2CCR1 = 900;

    volatile int i = 0;

    while(1) {
        for (i = 0; i <= 1000; i += 100){
            TA2CCR2 = i;
            TA2CCR1 = i;
            __delay_cycles(80000);
        }
        for (i = 900; i >= 100; i -= 100){
            TA2CCR2 = i;
            TA2CCR1 = i;
            __delay_cycles(80000);
        }

    }
}

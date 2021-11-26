#include <msp430.h> 
#include <myUart.h>

void myADC12Init();
void myPWMInit();
void mySerialInit();

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	volatile unsigned int i;

	int A0data = 0;
	int A1data = 0;

	P4SEL |= BIT4 | BIT5; // serial com. setting
	mySerialInit();

	P6SEL |= BIT0 | BIT1; // ADC12 setting
	myADC12Init();
	
	P1DIR |= BIT4 | BIT5; // PWM setting
	P1SEL |= BIT4 | BIT5;
	P2DIR |= BIT4 | BIT5;
	P2SEL |= BIT4 | BIT5;
	myPWMInit();

	while(1) {
	    for (i=0; i<2; i++) {
	        ADC12CTL0 |= ADC12SC;
            while(!(ADC12IFG & 0x0003));
	    }
	    A0data = ADC12MEM0; // 0 ~ 4095
	    A1data = ADC12MEM1;

	    TA0CCR4 = A0data;
	    TA0CCR3 = 4095 - A0data;

	    write_uart_uint(A0data);

	    write_uart_byte(',');

	    TA2CCR2 = A1data;
	    TA2CCR1 = 4095 - A1data;

	    write_uart_uint(A1data);

        write_uart_byte('\r');
        write_uart_byte('\n');

        __delay_cycles(200000);
	}
}

void myADC12Init() {
    ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1;
    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS;
    ADC12CTL0 |= ADC12ENC;
}

void myPWMInit() {
    TA0CTL = TASSEL_2 + MC_1;
    TA0CCR0 = 4095;
    TA0CCTL4 = OUTMOD_6;
    TA0CCR4 = 0;
    TA0CCTL3 = OUTMOD_6;
    TA0CCR3 = 0;

    TA2CTL = TASSEL_2 + MC_1;
    TA2CCR0 = 4095;
    TA2CCTL2 = OUTMOD_6;
    TA2CCR2 = 0;
    TA2CCTL1 = OUTMOD_6;
    TA2CCR1 = 0;
}

void mySerialInit() {
    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0;
    UCA1CTL1 &= ~UCSWRST;
}

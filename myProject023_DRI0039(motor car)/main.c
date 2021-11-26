#include <msp430.h> 

void myPWMInit();

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT4 | BIT5; // wheels PWM/speed
    P3DIR |= BIT5 | BIT6; // wheels direction

    P3OUT &= ~(BIT5 | BIT6);

    P1SEL |= BIT4; // left wheels
    P1SEL |= BIT5; // right wheels

    myPWMInit();

    volatile unsigned int i = 0;

    while(1) {

        P3OUT &= ~BIT5;
        P3OUT &= ~BIT6;

        for (i = 500; i <= 800; i++) {
            TA0CCR3 = i;
            TA0CCR4 = i;
            __delay_cycles(10000);
        }
        for (i = 800; i > 500; i--) {
            TA0CCR3 = i;
            TA0CCR4 = i;
            __delay_cycles(10000);
        }

        P3OUT |= BIT5;
        P3OUT |= BIT6;

        for (i = 500; i <= 800; i++) {
            TA0CCR3 = i;
            TA0CCR4 = i;
            __delay_cycles(10000);
        }
        for (i = 800; i > 500; i--) {
            TA0CCR3 = i;
            TA0CCR4 = i;
            __delay_cycles(10000);
        }

    }
}

void myPWMInit() {
    TA0CTL = TASSEL_2 + MC_1;
    TA0CCR0 = 1000;

    TA0CCTL3 = OUTMOD_6;
    TA0CCR3 = 0;

    TA0CCTL4 = OUTMOD_6;
    TA0CCR4 = 0;
}

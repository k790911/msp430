#include <msp430.h> 

void onOff1(unsigned int data);
void onOff2(unsigned int data);

unsigned int data[2] = {0};

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P2DIR |= BIT5;

    P1OUT &= ~BIT0;
    P2OUT &= ~BIT5;

    P6SEL |= BIT0 + BIT1;

    ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1;

    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS;

    ADC12CTL0 |= ADC12ENC;
    int i;

    while(1) {
        P2OUT |= BIT5;
        for (i=0; i<2; i++) {
            ADC12CTL0 |= ADC12SC;
            while(!(ADC12IFG & 0x0003));
            if (i == 0) {
                data[i] = ADC12MEM0;
            }
            else if (i == 1) {
                data[i] = ADC12MEM1;
            }

        }

        onOff1(data[0]);

        __delay_cycles(600000);

        onOff1(data[1]);

        P2OUT &= ~BIT5;
        __delay_cycles(600000);

    }
}

void onOff1(unsigned int data) {
    int i;
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
}

void onOff2(unsigned int data) {
    int i;
    if (data == 4095) {
        for (i = 0; i < 6; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else if (data > 4000) {
        for (i = 0; i < 5; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else if (data > 3000) {
        for (i = 0; i < 4; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else if (data > 2000) {
        for (i = 0; i < 3; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else if (data > 1000) {
        for (i = 0; i < 2; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else if (data <= 1000 && data >= 0){
        for (i = 0; i < 1; i++) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
            __delay_cycles(300000);
        }
    }
    else {
        P4OUT &= ~BIT7;
    }
}

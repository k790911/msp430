#include <msp430.h> 
#include <stdio.h>

volatile unsigned int time_last = 0;
volatile unsigned int i = 0;
char wel[10] = "";

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// trig, echo pin set
	P2DIR |= BIT4; // trig, output, set 1
	P2DIR &= ~BIT5; // echo, input, set 0
	P2IE = 0;
	P2IE |= BIT5;
	P2IES |= BIT5;
	P2IFG &= ~BIT5;
	
	// serial to PC set
    P4SEL |= 0x30;

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;

	// led set & off
	P1DIR |= BIT0; P1OUT &= ~BIT0;
	P4DIR |= BIT7; P4OUT &= ~BIT7;

	__bis_SR_register(GIE);

	while(1) {

	    if (time_last == 0) {

	        P2OUT |= BIT4;
	        __delay_cycles(10);
	        P2OUT &= ~BIT4;

	    }

	    time_last++;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void port2_ISR(void) {
    // trig 신호의 down 시그널에서도 인터럽트가 발생하는 것으로 보임(P2IE |= BIT5 했는데도,,)
    // 해당 엣지는 time_last 가 0 이므로 강제 배재 하였고, 원인분석 필요함
    if (time_last != 0) {

        if (time_last <=500) {
            P1OUT |= BIT0;
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P1OUT &= ~BIT0;
            P4OUT &= ~BIT7;
        }
        else if (time_last <=2000) {
            P4OUT |= BIT7;
            __delay_cycles(300000);
            P4OUT &= ~BIT7;
        }
        else if (time_last <=3000) {
            P1OUT |= BIT0;
            __delay_cycles(300000);
            P1OUT &= ~BIT0;
        }
        else {
        }

        /* 아래는 시리얼 데이터 출력용
        sprintf(wel, "%d", time_last);

        i = 0;
        while(wel[i] != '\0') {
            UCA1TXBUF = wel[i]; while(UCA1STAT & UCBUSY);
            i++;
        }
        UCA1TXBUF = 0x0A; while(UCA1STAT & UCBUSY);
        UCA1TXBUF = 0x0D; while(UCA1STAT & UCBUSY);
        */
        time_last = 0;

    }
    P2IFG = 0x00;
}

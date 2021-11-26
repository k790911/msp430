#include <msp430.h> 
#include <myUart.h>

unsigned int startTime = 0;
unsigned int endTime = 0;
unsigned int totalTime = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P1DIR |= BIT3;
    P1OUT &= ~BIT3;

    P1DIR &= ~BIT2;
    P1SEL |= BIT2;
    P1IE |= BIT2;

    TA0CTL |= TASSEL_2 + MC_2; // SMCLK 1Mhz, continuous mode
    TA0CCTL1 |= CM_3 + SCS + CCIS_0 + CAP + CCIE; // csc: synchronous capture


    P4SEL |= 0x30; // 내부 UART 포트 to PC 세팅, serial

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;


    __bis_SR_register(GIE);

    while(1) {
        TA0CTL |= TACLR; // 타이머 초기화
        P1OUT |= BIT3;
        __delay_cycles(10);
        P1OUT &= ~BIT3;

        __delay_cycles(100000);

        if (totalTime >= 8500) {
            P4OUT |= BIT7;
        }
        else if (totalTime <= 10) {
            P1OUT |= BIT0;
        }
        else {
            P1OUT &= ~BIT0;
            P4OUT &= ~BIT7;
        }
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_ISR(void) {
    __disable_interrupt();

    if (TA0CCTL1 & CCI) {
        startTime = TA0CCR1;
    }
    else {
        endTime = TA0CCR1;
        totalTime = endTime - startTime;
        startTime = 0;
        endTime = 0;

        if (totalTime < 8500 && totalTime > 10) {
            write_uart_uint(totalTime);
            write_uart_byte('\r');
            write_uart_byte('\n');
        }

    }

    TA0CCTL1 &= ~CCIFG;
    __enable_interrupt();
}

#include <msp430.h> 
int cnt = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    //TASSEL_2 : timer A clock source - SMCLK (여기서는 1MHz)
    // MC_1 : Up mode
    // TACLR : timer clear, reset to 0
    TA0CTL = TASSEL_2 + MC_1 + TACLR;
    TA0CCTL0 = CCIE; // interrupt enable
    TA0CCR0 = 1000; // 클럭을 이 단위로 뛰어감. (1초 1Mhz 번이면 천번이 됨)

    __bis_SR_register(GIE);

    while(1){

    }
}

#pragma vector=TIMER0_A0_VECTOR;
__interrupt void TIMER0_A0_ISR(void){
    cnt++;
    if (cnt >= 1000) {
        P1OUT ^= BIT0;
        cnt = 0;
    }
}

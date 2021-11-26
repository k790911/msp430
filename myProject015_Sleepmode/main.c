#include <msp430.h> 


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    // 버튼 설정
    P2OUT |= BIT1; //풀업
    P2REN |= BIT1;

    // 인터럽트 설정
    P2IE |= BIT1;
    P2IES |= BIT1; // 엣지 실렉트
    P2IFG &= ~BIT1; // 버튼 플래그 초기화

    // LED설정
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;



    while(1) {

        P4OUT ^= BIT7;
        __delay_cycles(500000);

        __bis_SR_register(GIE + LPM0_bits);
    }

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    __bic_SR_register_on_exit(LPM0_bits);
    P1OUT ^= BIT0;
    P2IFG &= ~BIT1;
}

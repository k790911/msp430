#include <msp430.h> 

// PxIE 0: disable, 1: enable
// PxIES 0: rising edge trigger, 1: falling edge trigger
// PxIFG : 인터럽트 발생 시 1로 전환됨, 처리 시 0으로 수동 전환 해야함

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// 버튼 설정
	P1OUT |= BIT1; //풀업
	P1REN |= BIT1;

	// led 설정
	P2DIR |= BIT5;
	P4DIR |= BIT7;

	P2OUT &= ~BIT5;
	P4OUT &= ~BIT7;

	// 인터럽트 설정
	P1IE |= BIT1;
	P1IES &= ~BIT1; // 엣지 실렉트
	P1IFG &= ~BIT1; // 버튼 플래그 초기화

	__bis_SR_register(GIE); // 글롤벌 인터럽트 인에이블

	while(1) {
	    P2OUT ^= BIT5;
	    __delay_cycles(1000000);
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    P4OUT ^= BIT7;
    P1IFG &= ~BIT1;
}

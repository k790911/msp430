#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    P1DIR |= BIT0; // 포트1 출력모드
    P4DIR |= BIT7;

    P1OUT &= ~BIT0; // 포트1(LED) 끔
    P4OUT &= ~BIT7;

    P2DIR &= ~BIT1; // 포트2.1 입력모드
    P1DIR &= ~BIT1;

    P2OUT |= BIT1; // 포트 2.1 (입력모드에서) 풀업저항 사용(MSP430f5529 보드 설계가 풀업으로 되어 있음)
    P1OUT |= BIT1;

    P2REN |= BIT1; // 포트 2.1 풀업저항 인에이블
    P1REN |= BIT1;

    while(1) {
        if ((P2IN & BIT1) == 0) {
            P1OUT |= BIT0;
        }else if ((P1IN & BIT1) == 0) {
            P4OUT |= BIT7;
        }else {
            P1OUT &= ~BIT0;
            P4OUT &= ~BIT7;
        }

    }
}

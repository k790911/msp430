#include <msp430.h> 

// PxIE 0: disable, 1: enable
// PxIES 0: rising edge trigger, 1: falling edge trigger
// PxIFG : ���ͷ�Ʈ �߻� �� 1�� ��ȯ��, ó�� �� 0���� ���� ��ȯ �ؾ���

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// ��ư ����
	P1OUT |= BIT1; //Ǯ��
	P1REN |= BIT1;

	// led ����
	P2DIR |= BIT5;
	P4DIR |= BIT7;

	P2OUT &= ~BIT5;
	P4OUT &= ~BIT7;

	// ���ͷ�Ʈ ����
	P1IE |= BIT1;
	P1IES &= ~BIT1; // ���� �Ƿ�Ʈ
	P1IFG &= ~BIT1; // ��ư �÷��� �ʱ�ȭ

	__bis_SR_register(GIE); // �۷ѹ� ���ͷ�Ʈ �ο��̺�

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

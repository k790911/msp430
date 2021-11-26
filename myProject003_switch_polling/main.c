#include <msp430.h> 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    P1DIR |= BIT0; // ��Ʈ1 ��¸��
    P4DIR |= BIT7;

    P1OUT &= ~BIT0; // ��Ʈ1(LED) ��
    P4OUT &= ~BIT7;

    P2DIR &= ~BIT1; // ��Ʈ2.1 �Է¸��
    P1DIR &= ~BIT1;

    P2OUT |= BIT1; // ��Ʈ 2.1 (�Է¸�忡��) Ǯ������ ���(MSP430f5529 ���� ���谡 Ǯ������ �Ǿ� ����)
    P1OUT |= BIT1;

    P2REN |= BIT1; // ��Ʈ 2.1 Ǯ������ �ο��̺�
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

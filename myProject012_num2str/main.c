#include <msp430.h> 
#include <stdio.h>

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	volatile char wel[10] = {};
    volatile char i = 0;
	int num1 = 123;
	
	// serial to PC set
    P4SEL |= 0x30;

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;

    sprintf(wel, "%d", num1);

    while(1) {
        i = 0;
        while(wel[i] != '\0') {
            UCA1TXBUF = wel[i];
            while(UCA1STAT & UCBUSY);
            i++;
        }
        UCA1TXBUF = 0x0A;
        while(UCA1STAT & UCBUSY);
        UCA1TXBUF = 0x0D;
        while(UCA1STAT & UCBUSY);
        __delay_cycles(600000);
    }
}

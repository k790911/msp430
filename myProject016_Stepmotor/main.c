#include <msp430.h> 

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT2 | BIT3 | BIT4 | BIT5;
    P1OUT &= ~(BIT2 | BIT3 | BIT4 | BIT5);

    unsigned int port[8] = {0x04, 0x0C, 0x08, 0x18, 0x10, 0x30, 0x20, 0x24};
    volatile int i = 0, j = 0, k = 0;

    while(1) {

        for (k = 0; k < 520; k++) { // step motor 1 turn forward
            for (i=0; i<8; i++) {
                P1OUT |= port[i];
                __delay_cycles(1000);

                P1OUT &= ~(BIT2 | BIT3 | BIT4 | BIT5);
            }
        }
        for (k = 0; k < 260; k++) { // step motor half turn backward
            for (i=7; i>=0; i--) {
                P1OUT |= port[i];
                __delay_cycles(1000);

                P1OUT &= ~(BIT2 | BIT3 | BIT4 | BIT5);
            }
        }
    }
}

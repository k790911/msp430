#include <msp430.h> 

#define SER BIT2    // port1
#define SRCLK BIT3  // port1
#define RCLK BIT4   // port1
#define SRCLRb BIT5 // port1

#define COM1 BIT0   // port3
#define COM2 BIT1   // port3
#define COM3 BIT2   // port3
#define COM4 BIT3   // port3

void serPulse(void);
void srclkPulse(void);
void rclkPulse(void);
void clearScr(void);

void displayNum(unsigned int cnt);

unsigned int num;
unsigned int i, j, k, l;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P2DIR &= ~(BIT2 | BIT3);

	P2IE |= BIT2 | BIT3;
	P2IES |= BIT2 | BIT3;
	P2IFG &= ~(BIT2 | BIT3);

	P1DIR |= SER | SRCLK | RCLK | SRCLRb;
	P1OUT |= ~(SER | SRCLK | RCLK | SRCLRb);
	P1OUT |= SRCLRb;

	P3DIR |= COM1 | COM2 | COM3 | COM4;
	P3OUT &= ~(COM1 | COM2 | COM3 | COM4);

	P2DIR &= ~BIT1; // reset button
	P2OUT |= BIT1; // pull up
	P2REN |= BIT1;

    P2IE |= BIT1;
    P2IES |= BIT1;
    P2IFG &= ~BIT1;

	__bis_SR_register(GIE);

	num = 0000;

	while(1) {

	    l = num % 10;
	    k = (num % 100) / 10;
	    j = (num % 1000) / 100;
	    i = num / 1000;

	    displayNum(l);  // 일의 자리
	    P3OUT &= ~COM4;
        P3OUT |= COM1 | COM2 | COM3;

        __delay_cycles(5000);
        clearScr();

        displayNum(k); // 십의 자리
        P3OUT &= ~COM3;
        P3OUT |= COM1 | COM2 | COM4;
        __delay_cycles(5000);
        clearScr();

        displayNum(j); // 백의 자리
        P3OUT &= ~COM2;
        P3OUT |= COM1 | COM3 | COM4;
        __delay_cycles(5000);
        clearScr();

        displayNum(i); // 천의 자리
        P3OUT &= ~COM1;
        P3OUT |= COM2 | COM3 | COM4;
        __delay_cycles(5000);
        clearScr();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void port2_isr(void) {
    switch(__even_in_range(P2IV, P2IV_P2IFG1)) {
    case 0x04 :
        num = 0;
        break;

    case 0x06 :
        if (num > 0) {
            num--;
        }
        else {
            num = 0;
        }

        break;
    case 0x08 :
        if (num < 9999) {
            num++;
        }
        else {
            num = 9999;
        }
        break;
    default:
        break;
    }
    P2IFG &= ~(BIT1 | BIT2 | BIT3);
}

void serPulse() {
    P1OUT |= SER;
    srclkPulse();
    P1OUT &= ~SER;
}
void srclkPulse() {
    P1OUT |= SRCLK;
    P1OUT &= ~SRCLK;
}
void rclkPulse() {
    P1OUT |= RCLK;
    P1OUT &= ~RCLK;
}

void clearScr(void) {
    P3OUT |= COM1 | COM2 | COM3 | COM4;
}

void displayNum(unsigned int cnt) {

    switch(cnt) {
    case 0 :
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        break;
    case 1 :
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        break;
    case 2 :
        srclkPulse();
        serPulse();
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        serPulse();
        serPulse();
        break;
    case 3 :
        srclkPulse();
        serPulse();
        srclkPulse();
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        break;
    case 4 :
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        break;
    case 5 :
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        serPulse();
        break;
    case 6 :
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        srclkPulse();
        serPulse();
        break;
    case 7 :
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        break;
    case 8 :
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        break;
    case 9 :
        srclkPulse();
        serPulse();
        serPulse();
        srclkPulse();
        serPulse();
        serPulse();
        serPulse();
        serPulse();
        break;
    case 10 :
        serPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
        srclkPulse();
    break;
    default:
    break;
    }
    rclkPulse();
}

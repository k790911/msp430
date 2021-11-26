#include <msp430.h> 

#define SERIAL BIT2
#define SRCLK BIT3
#define RCLK BIT4
#define SRCLEARbar BIT5

void serialBit(void);
void clkBit(void);
void latchPulse(void);
void displayNum(unsigned int num);

unsigned int cnt = 0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR &= ~BIT1;	P1OUT |= BIT1; P1REN |= BIT1;
	P1IE |= BIT1; P1IES |= BIT1; P1IFG &= ~BIT1; // 버튼 플래그 초기화

	P4DIR |= BIT7;
	P4OUT &= ~BIT7;

    P1DIR |= (SRCLK + SERIAL + RCLK + SRCLEARbar);
    P1OUT &= ~(SRCLK + SERIAL + RCLK);
    P1OUT |= SRCLEARbar;

    __bis_SR_register(GIE);

    P1OUT &= ~SRCLEARbar;
    __delay_cycles(10);
    P1OUT |= SRCLEARbar;

    while(1){
        P4OUT ^= BIT7;
        __delay_cycles(1000000);
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void) {

    P1OUT &= ~SRCLEARbar;
    __delay_cycles(10);
    P1OUT |= SRCLEARbar;

    volatile unsigned int a;

    for(a=0; a<11; a++) {
        displayNum(a);
        latchPulse();
        __delay_cycles(500000);
    }

    P1IFG &= ~BIT1; // 버튼 플래그 초기화
}
void displayNum(unsigned int cnt) {

    switch(cnt) {
    case 0 :
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        break;
    case 1 :
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        break;
    case 2 :
        clkBit();
        serialBit();
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        serialBit();
        serialBit();
        break;
    case 3 :
        clkBit();
        serialBit();
        clkBit();
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        break;
    case 4 :
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        break;
    case 5 :
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        serialBit();
        break;
    case 6 :
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        clkBit();
        serialBit();
        break;
    case 7 :
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        break;
    case 8 :
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        break;
    case 9 :
        clkBit();
        serialBit();
        serialBit();
        clkBit();
        serialBit();
        serialBit();
        serialBit();
        serialBit();
        break;
    case 10 :
        serialBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
        clkBit();
    break;
    default:
    break;
    }
}
void serialBit(void) {

    P1OUT |= SERIAL;
    P1OUT |= SRCLK;
    P1OUT &= ~SRCLK;
    P1OUT &= ~SERIAL;
}
void clkBit(void) {

    P1OUT |= SRCLK;
    P1OUT &= ~SRCLK;
}
void latchPulse(void) {

    P1OUT |= RCLK;
    P1OUT &= ~RCLK;
}

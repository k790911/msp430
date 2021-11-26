#include <msp430.h>
#include <myUart.h>

void my2ADCInit();
void myPWMInit();
void myUartInit();
void sendUart(unsigned int a, unsigned int b);

unsigned int data[2] = {0};

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	volatile unsigned int i;

	myPWMInit();
    my2ADCInit();
    //myUartInit();

    while(1) {
        for (i=0; i<2; i++) {
            ADC12CTL0 |= ADC12SC;
            while(!(ADC12IFG & 0x0003));
        }
        data[0] = ADC12MEM0;
        data[1] = ADC12MEM1;

        data[0] = (data[0] >> 1) + 500;
        data[1] = (data[1] >> 1) + 500;

        //sendUart(data[0], data[1]);

        TA2CCR2 = data[0];
        TA2CCR1 = data[1];

        data[0] = 0;
        data[1] = 0;
        __delay_cycles(100000);
    }
}

void my2ADCInit() {

    P6SEL |= BIT0 + BIT1; // ADC pin setting

    ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1;
    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS;
    ADC12CTL0 |= ADC12ENC;
}

void myPWMInit() {

    P2DIR |= (BIT5 | BIT4); // PWM direction
    P2SEL |= (BIT5 | BIT4); // PWM special pin

    TA2CTL = TASSEL_2 + MC_1; // SMCLK : 1 MHz / Up mode CCR0
    TA2CCR0 = 20000; // 클럭을 이 단위로 뛰어감. 서보모터 초당 간격으로 계산

    /* 20000을 기준으로 1500을 중심으로 500 ~ 2500. -90 ~ 90도를 왔다갔다함*/
    TA2CCTL2 = OUTMOD_6; // PWM toggle/set
    TA2CCR2 = 1500;
    TA2CCTL1 = OUTMOD_6; // PWM toggle/set
    TA2CCR1 = 1500;
}

void myUartInit() {
    P4SEL |= BIT4 | BIT5; // 내부 UART 포트 to PC 세팅, serial

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 |= UCSSEL_1;
    UCA1BR0 = 3;
    UCA1BR1 = 0x00;
    UCA1MCTL = 0x06;
    UCA1CTL0 = 0x00;
    UCA1CTL1 &= ~UCSWRST;
}

void sendUart(unsigned int a, unsigned int b) {
    write_uart_uint(a);
    write_uart_byte(' ');
    write_uart_uint(b);
    write_uart_byte('\r');
    write_uart_byte('\n');
}

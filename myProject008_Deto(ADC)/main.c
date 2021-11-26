#include <msp430.h> 

unsigned int data[2] = {0};
unsigned int timeCnt = 0;
unsigned int yellTrg = 0;
unsigned int time1 = 0;
unsigned int timePast = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    int i = 0;

    // LED OUT 핀 설정
    P1DIR = BIT2 + BIT3 + BIT4; // 2번 초록, 3번 노랑, 4번 적색 LED
    P1OUT &= ~(BIT2 + BIT3 + BIT4);

    // 특수핀 설정(ADC)
    P6DIR &= ~(BIT0 + BIT1); // P6.0 1차센서, P6.1 2차센서
    P6SEL |= BIT0 + BIT1;

    ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1; // 포트 옮길때(1/3) 시작피트 넣음 ADC12CSTARTADDx

    // 0번핀은 0번 채널에 물림
    ADC12MCTL0 = ADC12INCH_0; // 포트 옮길떄(2/3) 채널도 핀번호에 맞추어 바꿈
    // 1번 핀은 1번 채널에 물림, 연속 ADC의 마지막 설정
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS; // 포트 옮길떄(3/3) 채널도 핀번호에 맞추어 바꿈
    // ADC 인에이블
    ADC12CTL0 |= ADC12ENC;

    while(1){
        for (i=0; i<2; i++) {
            ADC12CTL0 |= ADC12SC;
            while(!(ADC12IFG & 0x0003));
            if (i == 0) {
                data[i] = ADC12MEM0;
            }
            else if (i == 1) {
                data[i] = ADC12MEM1;
            }
        }

        if (yellTrg == 0) {
            if (data[0] >= 2000) {
                P1OUT |= BIT3; // 노랑 LED on
                yellTrg = 1;
                time1 = timeCnt;
            }
        }
        else if (yellTrg == 1) {
            timePast = timeCnt - time1;

            if (data[1] >= 2000 && timePast <= 5) {
                for (i=0; i<5; i++) {
                    P1OUT ^= BIT4;
                    __delay_cycles(400000);
                }
                yellTrg = 0;
                time1 = 0;
                P1OUT &= ~(BIT2 + BIT3 + BIT4);
            }
            else if (data[1] >= 2000 && timePast > 5) {
                for (i=0; i<5; i++) {
                    P1OUT ^= BIT2;
                    __delay_cycles(400000);
                }
                yellTrg = 0;
                time1 = 0;
                P1OUT &= ~(BIT2 + BIT3 + BIT4);
            }

        }
        else {

        }

        timeCnt++;
        __delay_cycles(600000);

    }
}


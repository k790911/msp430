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

    // LED OUT �� ����
    P1DIR = BIT2 + BIT3 + BIT4; // 2�� �ʷ�, 3�� ���, 4�� ���� LED
    P1OUT &= ~(BIT2 + BIT3 + BIT4);

    // Ư���� ����(ADC)
    P6DIR &= ~(BIT0 + BIT1); // P6.0 1������, P6.1 2������
    P6SEL |= BIT0 + BIT1;

    ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1; // ��Ʈ �ű涧(1/3) ������Ʈ ���� ADC12CSTARTADDx

    // 0������ 0�� ä�ο� ����
    ADC12MCTL0 = ADC12INCH_0; // ��Ʈ �ű拚(2/3) ä�ε� �ɹ�ȣ�� ���߾� �ٲ�
    // 1�� ���� 1�� ä�ο� ����, ���� ADC�� ������ ����
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS; // ��Ʈ �ű拚(3/3) ä�ε� �ɹ�ȣ�� ���߾� �ٲ�
    // ADC �ο��̺�
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
                P1OUT |= BIT3; // ��� LED on
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


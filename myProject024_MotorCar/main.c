#include <msp430.h> 

void myPinInit();
void myServoInit();
void myPWMInit();
void myURFInit();

void startAction();
void measureDist();

void moveForward();
void moveBackward();
void stopMoving();

void turnRight();
void turnLeft();

void faceFront();
void faceLeft();
void faceRight();

void runInto();

unsigned int startTime = 0;
unsigned int endTime = 0;
unsigned int totalTime = 0;
unsigned int data[3] = {0};

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    myPinInit();
    myServoInit();
    myPWMInit();
    myURFInit();

    __bis_SR_register(GIE);

    startAction();

    while(1) {

        measureDist();          // 정면 거리측정

        data[0] = totalTime;
        totalTime = 0;

        if (data[0] >= 1500) {
            moveForward();
        }
        else {
            runInto();
        }
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;

        __delay_cycles(50000);
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_ISR(void) {

    if (TA0CCTL1 & CCI) {
        startTime = TA0CCR1;

    }
    else {
        endTime = TA0CCR1;
        totalTime = endTime - startTime;
        startTime = 0;
        endTime = 0;
    }

    TA0CCTL1 &= ~CCIFG;
}

#pragma vector=PORT2_VECTOR
__interrupt void port2_ISR(void) {

    switch(__even_in_range(P2IV, P2IV_P2IFG6)) {

    case 0x08 : //left
        moveBackward();
        __delay_cycles(500000);

        stopMoving();
        __delay_cycles(500000);

        turnRight();
        break;

    case 0x0E : // right
        moveBackward();
        __delay_cycles(500000);

        stopMoving();
        __delay_cycles(500000);

        turnLeft();
        break;

    default:
        break;
    }
    P2IFG &= ~(BIT3 | BIT6);
}

void myPinInit() {

    /* PWM, for servo setting */
    P2DIR |= BIT0;
    P2SEL |= BIT0;

    /* PWM, Direction pin setting */
    P2DIR |= BIT4 | BIT5; // wheels PWM/speed
    P3DIR |= BIT5 | BIT6; // wheels direction

    P3OUT &= ~(BIT5 | BIT6); // p5 right, p6 left

    P2SEL |= BIT4; // left wheels
    P2SEL |= BIT5; // right wheels

    /* URF timer pin setting */
    P1DIR &= ~BIT2; // echo pin
    P1SEL |= BIT2;
    P1IE |= BIT2;

    P1DIR |= BIT3; // trig pin
    P1OUT &= ~BIT3;

    /* run into something on the left/right front */
    P2DIR &= ~BIT3; // left interrupt input
    P2DIR &= ~BIT6; // right interrupt inupt
    P2IE |= (BIT3 | BIT6);
    P2IES |= (BIT3 | BIT6); // interrupt on falling edge from 1 to 0
    P2IFG &= ~(BIT3 | BIT6);
}

void myServoInit() {

    TA1CTL = TASSEL_2 + MC_1; // select smclk(1Mhz), up mode
    TA1CCR0 = 20000;

    TA1CCTL1 = OUTMOD_6; // PWM toggle/set
    TA1CCR1 = 1500; // 0도 정면을 향함
}

void myPWMInit() { // pwm for motor speed control

    TA2CTL = TASSEL_2 + MC_1;
    TA2CCR0 = 1000;

    TA2CCTL1 = OUTMOD_6;
    TA2CCR1 = 0;

    TA2CCTL2 = OUTMOD_6;
    TA2CCR2 = 0;
}

void myURFInit() {

    TA0CTL |= TASSEL_2 + MC_2; // SMCLK 1Mhz, continuous mode
    TA0CCTL1 |= CM_3 + SCS + CCIS_0 + CAP + CCIE; // csc: synchronous capture
}
void startAction() {

    faceFront();
    __delay_cycles(500000);

    faceRight();
    __delay_cycles(500000);

    faceLeft();
    __delay_cycles(500000);

    faceFront();
    __delay_cycles(500000);
}

void measureDist() {

    TA0CTL |= TACLR; // 타이머 초기화

    P1OUT |= BIT3;
    __delay_cycles(10);
    P1OUT &= ~BIT3;

    __delay_cycles(100000);
}

void moveForward() {

    P3OUT &= ~BIT5; // right wheel forward
    P3OUT &= ~BIT6; // left wheel forward

    TA2CCR1 = 500; // right speed
    TA2CCR2 = 300; // left speed, for left-right balance
}

void moveBackward() {

    P3OUT |= BIT5; // right wheel backward
    P3OUT |= BIT6; // left wheel backward

    TA2CCR1 = 300; // left speed
    TA2CCR2 = 300; // right speed
}

void stopMoving() {

    TA2CCR1 = 0;
    TA2CCR2 = 0;
}

void turnRight() {

    P3OUT |= BIT5; // right wheel forward
    P3OUT &= ~BIT6; // left wheel backward
    TA2CCR1 = 600; // left speed 50%
    TA2CCR2 = 600; // right speed 50%
    __delay_cycles(800000); // ? degrees?
    TA2CCR1 = 0; // left speed 0%
    TA2CCR2 = 0; // right speed 0%
}

void turnLeft() {

    P3OUT &= ~BIT5; // right wheel backward
    P3OUT |= BIT6; // left wheel forward
    TA2CCR1 = 600; // left speed 50%
    TA2CCR2 = 600; // right speed 50%
    __delay_cycles(800000); // ? degrees?
    TA2CCR1 = 0; // left speed 0%
    TA2CCR2 = 0; // right speed 0%
}

void faceFront() {
    TA1CCR1 = 1500;  // 서보 정면, 1500 정면, 500 우측 90도, 2500 좌측 90도
    __delay_cycles(1000000);
}

void faceLeft() {
    TA1CCR1 = 2200;  // 서보 좌측
    __delay_cycles(500000);
}

void faceRight() {
    TA1CCR1 = 800; // 서보 우측
    __delay_cycles(500000);
}

void runInto() {

    moveBackward();
    __delay_cycles(500000);

    stopMoving();
    __delay_cycles(500000);

    faceRight();        // 우측 보기
    measureDist();      // 우측 거리측정

    data[1] = totalTime;
    totalTime = 0;

    faceLeft();         // 좌측 보기
    measureDist();      // 좌측 거리측정
    data[2] = totalTime;
    totalTime = 0;

    faceFront();        // 정면 보기

    if (data[1] >= data[2]) {
        turnRight();
    }
    else {
        turnLeft();
    }
}

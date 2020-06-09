#include "MotorDriver.h"

/* SCHEMATIC
 * ____________
 *|             |
 *|        4.2 -|-> LEFT_MOTOR_FORWARD
 *|        4.3 -|-> LEFT_MOTOR_REVERSE
 *|        4.4 -|-> RIGHT_MOTOR_FORWARD
 *|        4.5 -|-> RIGHT_MOTOR_REVERSE
 *|             |
 *|____________ |
 */

void MotorDriver_init(void) {
    P4->SEL0 &= ~(BIT2 + BIT3 + BIT4 + BIT5);
    P4->SEL1 &= ~(BIT2 + BIT3 + BIT4 + BIT5);
    P4->DIR |= (BIT2 + BIT3 + BIT4 + BIT5);
}

void setMotion(uint16_t btSignal) {
    switch(btSignal) {
    case STOP:
        stopMotion();
        break;
    case FORWARD:
        goFoward();
        break;
    case REVERSE:
        goReverse();
        break;
    case RIGHT:
        goRight();
        break;
    case LEFT:
        goLeft();
        break;
    default:
        break;
    }
}

void goFoward(void) {
    P4->OUT &= ~(BIT3 + BIT5); //set all reverse pins to 0
    P4->OUT |= (BIT2 + BIT4); //set all forward pins to 1
}

void goReverse(void) {
    P4->OUT &= ~(BIT2 + BIT4); //set all forward pins to 0
    P4->OUT |= (BIT3 + BIT5); //set all reverse pins to 1
}

//left motor forward, right motor reverse
void goRight(void) {

    //set left motor reverse and right motor forward to 0
    P4->OUT &= ~(BIT3 + BIT4);

    //set left motor forward and right motor reverse to 1
    P4->OUT |= (BIT2 + BIT5);
}

void goLeft(void) {

    //set left motor forward and right motor reverse to 0
    P4->OUT &= ~(BIT2 + BIT5);

    //set left motor reverse and right motor forwards to 1
    P4->OUT |= (BIT3 + BIT4);
}

void stopMotion(void) {
    //set all motor pins to 0
    P4->OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5);
}

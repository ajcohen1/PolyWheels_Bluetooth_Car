/*
 * MotorDriver.h
 *
 *  Created on: May 30, 2020
 *      Author: ajcoh
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include <stdint.h>
#include "msp.h"

#define STOP 0xFF
#define FORWARD 0xAA
#define REVERSE 0xBB
#define LEFT 0xAB
#define RIGHT 0xBA

void MotorDriver_init(void);
void setMotion(uint16_t btSignal);
void goFoward(void);
void goReverse(void);
void goRight(void);
void goLeft(void);
void stopMotion(void);

#endif /* MOTORDRIVER_H_ */

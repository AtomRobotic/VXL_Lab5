/*
 * timer.h
 *
 *  Created on: Dec 8, 2024
 *      Author: ADMIN
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

void setTimer1(int duration);
void setTimer2(int duration);
unsigned char isTimer1_flag();
unsigned char isTimer2_flag();
void timerRun();

#endif /* INC_TIMER_H_ */

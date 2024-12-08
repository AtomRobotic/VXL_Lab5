/*
 * timer.h
 *
 *  Created on: Dec 8, 2024
 *      Author: ADMIN
 */

int timer1_flag = 0;
int timer1_counter = 0;

int timer2_flag = 0;
int timer2_counter = 0;

int TIMER_CYCLE = 10;

void setTimer1(int duration) {
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer2(int duration) {
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}

unsigned char isTimer1_flag(){
	return timer1_flag == 1;
}

unsigned char isTimer2_flag(){
	return timer2_flag == 1;
}

void timerRun() {
	if (timer1_counter > 0) {
		timer1_counter--;
		if(timer1_counter == 0) timer1_flag = 1;
	}
	if (timer2_counter > 0) {
		timer2_counter--;
		if(timer2_counter == 0) timer2_flag = 1;
	}
}



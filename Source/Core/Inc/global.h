/*
 * global.h
 *
 *  Created on: Dec 8, 2024
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "uart.h"
#include "timer.h"

#define MAX_BUFFER_SIZE 30
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t command_flag;

extern uint16_t ADC_Value;
extern char str[4];

#endif /* INC_GLOBAL_H_ */

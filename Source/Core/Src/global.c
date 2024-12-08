/*
 * global.c
 *
 *  Created on: Dec 8, 2024
 *      Author: ADMIN
 */

#include "global.h"

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE] = "!ADC=";
uint8_t index_buffer = 5;
uint8_t buffer_flag = 0;
uint8_t command_flag = 0;

uint16_t ADC_Value = 0;
char str[4] = "0000";

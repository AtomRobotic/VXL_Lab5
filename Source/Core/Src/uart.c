/*
 * uart.c
 *
 *  Created on: Dec 8, 2024
 *      Author: ADMIN
 */

#include "uart.h"
#include "main.h"
#include "stdio.h"
#include "string.h"

enum State {
	WAIT_COMMAND, SEND_DATA, RESEND_DATA
};
enum State VMState = WAIT_COMMAND;

#define INIT	0
#define START	1
#define END		2

uint8_t ReceiveState = INIT;
uint8_t ReceiveState_flag = 0;

#define INIT_RECEIVE		0
#define WAIT_HEADER			1
#define RECEIVE_DATA		2
#define RECEIVE_DATA_RST_2  3
#define RECEIVE_DATA_RST_3  4
#define END_DATA_RST 		5
#define RECEIVE_DATA_OK_2 	6
#define END_DATA_OK 		7
uint8_t statusReceive = WAIT_HEADER;

void command_parser_fsm(void) {
	switch (statusReceive) {
	case WAIT_HEADER:
		if (temp == '!') {
			statusReceive = RECEIVE_DATA;
		}
		break;
	case RECEIVE_DATA:
		if (temp == 'R')
			statusReceive = RECEIVE_DATA_RST_2;
		else if (temp == 'O')
			statusReceive = RECEIVE_DATA_OK_2;
		else
			statusReceive = WAIT_HEADER;
		break;
	case RECEIVE_DATA_RST_2:
		if (temp == 'S')
			statusReceive = RECEIVE_DATA_RST_3;
		else
			statusReceive = WAIT_HEADER;
		break;
	case RECEIVE_DATA_RST_3:
		if (temp == 'T')
			statusReceive = END_DATA_RST;
		else
			statusReceive = WAIT_HEADER;
		break;
	case RECEIVE_DATA_OK_2:
		if (temp == 'K')
			statusReceive = END_DATA_OK;
		else
			statusReceive = WAIT_HEADER;
		break;
	case END_DATA_RST:
		if (temp == '#') {
			statusReceive = WAIT_HEADER;
			command_flag = 1;
		} else
			statusReceive = WAIT_HEADER;
		break;
	case END_DATA_OK:
		if (temp == '#') {
			statusReceive = WAIT_HEADER;
			command_flag = 0;
		} else
			statusReceive = WAIT_HEADER;
		break;
	default:
		statusReceive = INIT_RECEIVE;
		break;
	}
}

void uart_communication_fsm(void){
	switch(VMState){
	case WAIT_COMMAND:
		if(command_flag){
			HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			ADC_Value = HAL_ADC_GetValue(&hadc1);
			sprintf(str, "%hu", ADC_Value);
			VMState = SEND_DATA;
		}
		break;
	case SEND_DATA:
		HAL_UART_Transmit(&huart2, buffer, 5, 100);
		HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen(str), 100);
		HAL_UART_Transmit(&huart2, (uint8_t*) "#\r\n", 3, 100);
		if(command_flag){
			setTimer1(1000);
			VMState = RESEND_DATA;
		}
		break;
	case RESEND_DATA:
		if(isTimer1_flag()){
			HAL_UART_Transmit(&huart2, buffer, 5, 100);
			HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen(str), 100);
			HAL_UART_Transmit(&huart2, (uint8_t*) "#\r\n", 3, 100);
			setTimer1(1000);
		}
		if(!command_flag){
			VMState = WAIT_COMMAND;
			setTimer1(100);
		}
		break;
	default:
		VMState = WAIT_COMMAND;
	}

}

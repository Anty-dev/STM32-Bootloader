/*
 * update.h
 *
 *  Created on: Sep 6, 2026
 *      Author: alama
 */

#ifndef INC_UPDATE_H_
#define INC_UPDATE_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {

	uint32_t exp_crc;
	uint32_t size;
	uint8_t buffer[512];
	uint8_t sec_start; // probably should hard code the sector erase indexes
	uint8_t sec_end;

}UART_Packet;

uint8_t updateApp(UART_Packet *pac);
void updateReady(UART_Packet *pac);

#endif /* INC_UPDATE_H_ */

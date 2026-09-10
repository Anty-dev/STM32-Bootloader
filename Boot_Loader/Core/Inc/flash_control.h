/*
 * flash_control.h
 *
 *  Created on: Sep 6, 2026
 *      Author: alama
 */

#ifndef INC_FLASH_CONTROL_H_
#define INC_FLASH_CONTROL_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define BANK_A 0x08008000U // active
#define BANK_B 0x08040000U
//#define FLASH_END 0x0807FFFFU call the version from stm32f446xx.h

extern volatile uint32_t bankFlag; // chnage this as its stored in ram and not non volatile memory hence it wont survive a reset

typedef struct {

	uint8_t id;
	uint32_t start_addr;
	uint32_t size;
	uint8_t start_sec;
	uint8_t end_sec;

}FlashPartition;

uint8_t valid_address(uint32_t addr, uint32_t size);
uint8_t valid_sector(uint8_t sec);
uint32_t switchBanks(void);

#endif /* INC_FLASH_CONTROL_H_ */

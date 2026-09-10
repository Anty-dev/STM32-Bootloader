/*
 * flash_control.c
 *
 *  Created on: Sep 6, 2026
 *      Author: alama
 *
 * This file controls where the flash is written and handles switching of banks A and B
 * It has a fucntion to see if its a valid sector and a valid address along with switching between the two banks
 */

#include "flash_control.h"

uint32_t volatile bankFlag = 0;
/*
 * Sectors 0-1 are reserved for the bootloader
 * Sectors 2-5 are for the active app (bank A)
 * Sectors 6-7 are the backup (bank B)
 */

uint8_t valid_sector(uint8_t sec) {

	if ((sec < 2) || (sec > 5)) {
		return 0;
	}
	return 1;
}

uint8_t valid_address(uint32_t addr, uint32_t size) {
	uint32_t end = addr + (4 * size); // in words

	if ((BANK_A < addr) && (addr < FLASH_END)) {
		if (end < FLASH_END) {
			return 1;
		}
	}
	return 0;
}

uint32_t switchBanks(void) {
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_DBP;

	// fix this when its not 3am probably will need an addtional register where it toggles it relative to the banks and maybe another reigster that tracks if a update occurs in the app
	if (RTC->BKP0R == 0) {
		return BANK_A;
	}
	return BANK_B;
}

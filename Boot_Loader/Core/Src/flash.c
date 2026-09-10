/*
 * flash.c
 *
 *  Created on: Aug 27, 2026
 *      Author: alama
 */

#include "flash.h"
#include "flash_control.h"

int isFlashLocked = 1;

void unlockFlash(void) {

	if (((FLASH->CR >> 31) & 1U) == 1U) {
		FLASH->KEYR = KEY1;
		FLASH->KEYR = KEY2;
		isFlashLocked = 0;
	}
	// otherwise flash is already unlocked
}

void lockFlash(void) {
	FLASH->CR = FLASH_CR_LOCK;
	isFlashLocked = 1;
}


void eraseFlash(uint8_t sector) {
	if (valid_sector(sector)) {

	// Note: must unlock flash control register before modifying it
	while (FLASH->SR & FLASH_SR_BSY){ }

	FLASH->CR |= FLASH_CR_SER;
	FLASH->CR &= ~(FLASH_CR_SNB);
	FLASH->CR |= (sector << FLASH_CR_SNB_Pos);

	FLASH->CR |= FLASH_CR_STRT;

	while (FLASH->SR & FLASH_SR_BSY){ }
	FLASH->CR &= ~(FLASH_CR_SER);
	}// end of if
	}

// inclusive of jth sector
void eraseSectors(uint8_t i, uint8_t j) {

	while (FLASH->SR & FLASH_SR_BSY){
		}
		FLASH->CR |= FLASH_CR_SER;

		while (i <= j) {
		FLASH->CR &= ~(FLASH_CR_SNB);
		FLASH->CR |= (i << FLASH_CR_SNB_Pos);

		FLASH->CR |= FLASH_CR_STRT;

		while (FLASH->SR & FLASH_SR_BSY){ }
		i++;
	}
		FLASH->CR &= ~(FLASH_CR_SER);
}

//leave length out for now
void writeFlash(uint32_t address, uint32_t data) {

	while (FLASH->SR & FLASH_SR_BSY){ }
	FLASH->CR |= FLASH_CR_PG;

	FLASH->CR &= ~(FLASH_CR_PSIZE);
	FLASH->CR |= (0x02 << FLASH_CR_PSIZE_Pos);

	*(volatile uint32_t*)address = data;

	while (FLASH->SR & FLASH_SR_BSY){ }
	FLASH->CR &= ~(FLASH_CR_PG);
}

void testFlash(uint8_t i, uint8_t j, uint32_t address, uint32_t data) {

	__disable_irq();
	unlockFlash();
	eraseFlash(i);

	writeFlash(address, data);
	lockFlash();
	__enable_irq();
}

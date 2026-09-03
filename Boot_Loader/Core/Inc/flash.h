/*
 * flash.h
 *
 *  Created on: Aug 27, 2026
 *      Author: alama
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define KEY1 0x45670123
#define KEY2 0xCDEF89AB
#define OPTKEY1 0x08192A3B
#define OPTKEY2 0x4C5D6E7F

extern int isFlashLocked;

void unlockFlash(void);
void lockFlash(void);
void eraseFlash(uint8_t sector);
void eraseSectors(uint8_t i, uint8_t j);
void writeFlash(uint32_t address, uint32_t data);
void testFlash(uint8_t i, uint8_t j, uint32_t address, uint32_t data);

#endif /* INC_FLASH_H_ */

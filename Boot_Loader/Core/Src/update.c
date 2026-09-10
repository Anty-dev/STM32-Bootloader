/*
 * update.c
 *
 *  Created on: Sep 6, 2026
 *      Author: alama
 */
#include "update.h"
#include "flash.h"
#include "flash_control.h"
#include "crc32.h"


uint8_t updateApp(UART_Packet *pac) {
	RTC->BKP1R = 0;
	// change the bank (write to inactive one)
	switchBank();
	uint32_t addr = activeBank();

	// delete sectors
		if (addr == BANK_A) {
			eraseSectors(2, 5);
		}else {
			eraseSectors(6, 7);
		}

		// figure out how uart adds info into our buffer probably interrupt based to not to block the cpu

	// parse the header from the data (first 4 is size, second 4 is crc)



	// write the data from uart to actual flash


	//verify, if it passes then switch to the other flash bank
	if (crc32((uint8_t*) addr, pac->size) != pac->exp_crc) {
		switchBank();
		// update is corrupted do some telemetry or something
	}
}

void updateReady(UART_Packet *pac) {
uint32_t start = HAL_GetTick();
uint8_t update = 0;
RCC->APB1ENR |= RCC_APB1ENR_PWREN;
PWR->CR |= PWR_CR_DBP;

while ((HAL_GetTick() - start) < 5000) {
	if (USART2->SR & USART_SR_RXNE) {
		update = 1;
	}
}
if (RTC->BKP1R == 1) {
	update = 1;
}
if (update == 1) {
	updateApp(pac);
}
}

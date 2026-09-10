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

	// parse the header from the data (first 4 is size, second 4 is crc)
	for (int i = 0; i < 4;i++) {
		//pac->size |= HAL_UART_Receive();
	}

	// delete sectors (evenutally loop this)
	eraseFlash(2);
	eraseFlash(3);
	eraseFlash(4);
	eraseFlash(5);

	// write the data from uart to actual flash
	for (int i = 0; i < pac->size; i++) {
		writeFlash(addr, (uint32_t)pac->buffer[i]);
	}

	//verify, if it passes then switch to the other flash bank
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

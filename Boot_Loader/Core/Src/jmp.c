/*
 * jmp.c
 *
 *  Created on: Aug 26, 2026
 *      Author: alama
 */

#include "jmp.h"


/*
 * This function is responsible for jumping from the bootloader to the main program. It intializes the sp
 * and changes the pc in order to jump to a whole new memory location and begin execution
 */
void jumpToApp(uint32_t addr) {

	__disable_irq();


	// if used any interrupts in the bootloader reset all the registers here


	uint32_t sp = *(volatile uint32_t*)addr;
	uint32_t pc = *(volatile uint32_t*)(addr + 4);

	void (*start)(void) = (void (*)(void))pc;

	__set_MSP(sp);
	start();

}


/*
 * ring_buff.h
 *
 *  Created on: Sep 10, 2026
 *      Author: alama
 */

#ifndef INC_RING_BUFF_H_
#define INC_RING_BUFF_H_

#include "stm32f4xx.h"
#include <stdint.h>

void pop(uint8_t *p);
void push(uint8_t *p);

#endif /* INC_RING_BUFF_H_ */

/*
 * crc32.c
 *
 *  Created on: Sep 3, 2026
 *      Author: alama
 */

#include "crc32.h"


uint32_t crc32(uint8_t *data, size_t i) {

	uint32_t crc = 0xFFFFFFFF;
	while(i--) {
		uint8_t byte = *(data++);
		crc ^= byte;

		for (int j = 0; j <= 7; j++) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else {
				crc >>= 1;
			}
		}
	}
	return crc ^ 0xFFFFFFFF;
}



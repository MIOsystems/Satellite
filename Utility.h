/*
 * Utility.h
 *
 *  Created on: 30 Jan 2021
 *      Author: Patrick
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#define CPU_SPEED 144000000

void delay(uint32_t cycles);
void delay_ms(uint32_t ms);
void delay_sec(uint32_t sec);


// SPI
typedef enum {
	SPI_RX,
	SPI_TX
} SPI_TRANSFER_MODES;

void flush_SPI_buffer(const SPI_MASTER_t *handle, SPI_TRANSFER_MODES mode);

#endif /* UTILITY_H_ */

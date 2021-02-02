/*
 * Utility.c
 *
 *  Created on: 30 Jan 2021
 *      Author: Patrick
 */
#include <stdint.h>
#include <DAVE.h>

#include <Utility.h>

void delay(uint32_t cycles) {
	for(uint32_t i = 0; i < cycles; i++) {
		__NOP();
	}
}

void delay_ms(uint32_t ms) {
	uint32_t cycles = (CPU_SPEED / 1000) * ms;
	delay(cycles);
}

void delay_sec(uint32_t sec) {
	uint32_t ms = sec / 1000;
	delay_ms(ms);
}

void flush_SPI_buffer(const SPI_MASTER_t *handle, SPI_TRANSFER_MODES mode) {
	switch(mode) {
		case SPI_RX:
			XMC_USIC_CH_RXFIFO_Flush(handle->channel);
			break;
		case SPI_TX:
			XMC_USIC_CH_TXFIFO_Flush(handle->channel);

	}

}

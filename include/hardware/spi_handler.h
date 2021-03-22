#ifndef SPI_HANDLER_H_
#define SPI_HANDLER_H_

#include <DAVE.h>

#include <include/util/error.h>


typedef enum {
	SPI_SLAVE_BMI085A_CS,
	SPI_SLAVE_BMI085G_CS
} SPI_SLAVES;

typedef enum 
{
	SPI_MASTER_UNDEFINED,
	SPI_MASTER_BMI
} SPI_HANDLERS;

typedef enum 
{
	SPI_RX,
	SPI_TX,
	SPI_BOTH
} SPI_CHANNELS;

/**
 * Will set the pin of the specified chip select to high
 * @param chip_id which chip you want to select, see enum
 */
void spi_select_chip(const SPI_SLAVES chip_id);
void spi_unselect_chip(const SPI_SLAVES chip_id);
void spi_flush(SPI_MASTER_t* handle, const SPI_CHANNELS channel);
void spi_wait(SPI_MASTER_t* handle, const SPI_CHANNELS channel);

#endif

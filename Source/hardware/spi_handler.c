#include <include/hardware/spi_handler.h>
#include <DAVE.h>


void spi_select_chip(const SPI_SLAVES chip_id)
{
	switch(chip_id)
	{
		case SPI_SLAVE_BMI085A_CS:
			DIGITAL_IO_SetOutputLow(&CS_A);
			break;
		case SPI_SLAVE_BMI085G_CS:
			DIGITAL_IO_SetOutputLow(&CS_G);
			break;
			
	}
}

void spi_unselect_chip(const SPI_SLAVES chip_id)
{
	switch(chip_id)
	{
		case SPI_SLAVE_BMI085A_CS:
			DIGITAL_IO_SetOutputHigh(&CS_A);
			break;
		case SPI_SLAVE_BMI085G_CS:
			DIGITAL_IO_SetOutputHigh(&CS_G);
			break;
			
	}
}

void spi_flush(SPI_MASTER_t* handle, const SPI_CHANNELS channel)
{
	switch(channel)
	{
		case SPI_RX:
			XMC_USIC_CH_RXFIFO_Flush(handle->channel);
			while(!SPI_MASTER_IsRxFIFOEmpty(handle)) 
			{
				SPI_MASTER_GetReceivedWord(handle);
			}
		case SPI_TX:
			XMC_USIC_CH_TXFIFO_Flush(handle->channel);

		case SPI_BOTH:
			XMC_USIC_CH_RXFIFO_Flush(handle->channel);
			XMC_USIC_CH_TXFIFO_Flush(handle->channel);
			while(!SPI_MASTER_IsRxFIFOEmpty(handle))
			{
				SPI_MASTER_GetReceivedWord(handle);
			}
	}
}

void spi_wait(SPI_MASTER_t* handle, const SPI_CHANNELS channel)
{
	switch(channel)
	{
		case SPI_RX:
			while(handle->runtime->rx_busy);
			break;
		case SPI_TX:
			while(handle->runtime->tx_busy);
			break;
		case SPI_BOTH:
			while(handle->runtime->rx_busy || handle->runtime->tx_busy);
			break;
	}
}

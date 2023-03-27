#include <include/hardware/fram.h>

fram_err_t fram_enable_write()
{
	//======== Build command buffer ========
	uint8_t commandByte = OPCODE_WREN;

	//======== Build receive buffer ========
	uint8_t readByte = 0;

	//======== Write data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM); 																	// Set slave select pin low for start of transfer/read
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transfer(&FRAM_SPI_MASTER_0, &commandByte, &readByte, 1); 	// Transfer command and write data to FRAM
	while(FRAM_SPI_MASTER_0.runtime->rx_busy || FRAM_SPI_MASTER_0.runtime->tx_busy); 					// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																// Set slave select pin high for end of transfer/read

	delayMs(2);																							// Small delay to make sure slave select pin is high

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

fram_err_t fram_disable_write()
{
	//======== Build command buffer ========
	uint8_t commandByte = OPCODE_WRDI;

	//======== Build receive buffer ========
	uint8_t readByte = 0;

	//======== Write data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM); 																	// Set slave select pin low for start of transfer/read
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transmit(&FRAM_SPI_MASTER_0, &commandByte, 1);				// Transfer command and write data to FRAM
	while(FRAM_SPI_MASTER_0.runtime->tx_busy); 															// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																// Set slave select pin high for end of transfer/read

	delayMs(2);																							// Small delay to make sure slave select pin is high

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

fram_err_t fram_read_status_register(uint8_t* value)
{
	//======== Build command buffer ========
	uint8_t commandByte = OPCODE_RDSR;

	uint8_t test[2] = { 0, 0 };

	//======== Write data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM); 																	// Set slave select pin low for start of transfer/read
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transfer(&FRAM_SPI_MASTER_0, &commandByte, &test, 2); 		// Transfer command and write data to FRAM
	while(FRAM_SPI_MASTER_0.runtime->rx_busy || FRAM_SPI_MASTER_0.runtime->tx_busy); 					// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																// Set slave select pin high for end of transfer/read

	delayMs(2);																							// Small delay to make sure slave select pin is high

	*value = test[1];

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

fram_err_t fram_write_status_register(uint8_t value)
{
	//======== Build command buffer ========
	uint8_t commandBytes[2] = { OPCODE_RDSR, value };
	uint8_t readBytes[2] = { 0, 0 };

	//======== Write data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM);
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transfer(&FRAM_SPI_MASTER_0, &commandBytes, &readBytes, 2); 	// Transfer command and write data to FRAM
	while(FRAM_SPI_MASTER_0.runtime->rx_busy || FRAM_SPI_MASTER_0.runtime->tx_busy); 						// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																	// Set slave select pin high for end of transfer/read

	delayMs(2);																								// Small delay to make sure slave select pin is high

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

fram_err_t fram_read_data(uint16_t offset, void* data, uint16_t size)
{
	if(offset + size > LAST_MEM_ADDRESS)
		return FRAM_ERR_NOT_ENOUGH_SPACE;

	//======== Build command buffer ========
	unsigned char* commandBytes = (unsigned char*)malloc(3 + size);
	commandBytes[0] = OPCODE_READ;
	commandBytes[1] = (uint8_t)(offset >> 1);
	commandBytes[2] = (uint8_t)offset;
	memcpy(commandBytes + 3, data, size);

	//======== Build receive buffer ========
	unsigned char* readBytes = (unsigned char*)malloc(3 + size);

	//======== Read data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM); 																				// Set slave select pin low for start of transfer/read
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transfer(&FRAM_SPI_MASTER_0, commandBytes, readBytes, (3 + size)); 		// Transfer command and read data form FRAM
	while(FRAM_SPI_MASTER_0.runtime->rx_busy || FRAM_SPI_MASTER_0.runtime->tx_busy); 								// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																			// Set slave select pin high for end of transfer/read

	delayMs(2);																										// Small delay to make sure slave select pin is high

	memcpy(data, readBytes + 3, size);

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

fram_err_t fram_write_data(uint16_t offset, void* data, uint16_t size)
{
	if(offset + size > LAST_MEM_ADDRESS)
		return FRAM_ERR_NOT_ENOUGH_SPACE;

	//======== Build command buffer ========
	unsigned char* commandBytes = (unsigned char*)malloc(3 + size);
	commandBytes[0] = OPCODE_WRITE;
	commandBytes[1] = (uint8_t)(offset >> 1);
	commandBytes[2] = (uint8_t)offset;
	memcpy(commandBytes + 3, data, size);

	//======== Build receive buffer ========
	unsigned char* readBytes = (unsigned char*)malloc(3 + size);

	//======== Write data ========
	DIGITAL_IO_SetOutputLow(&CS_FRAM); 																					// Set slave select pin low for start of transfer/read
	SPI_MASTER_STATUS_t status = SPI_MASTER_Transfer(&FRAM_SPI_MASTER_0, commandBytes, readBytes, (3 + size)); 			// Transfer command and write data to FRAM
	while(FRAM_SPI_MASTER_0.runtime->rx_busy || FRAM_SPI_MASTER_0.runtime->tx_busy); 									// Wait for read operation to finish
	DIGITAL_IO_SetOutputHigh(&CS_FRAM); 																				// Set slave select pin high for end of transfer/read

	delayMs(2);																											// Small delay to make sure slave select pin is high

	//======== Check status ========
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return FRAM_ERR_WRITE_FAILURE;
	}

	return FRAM_ERR_OK;
}

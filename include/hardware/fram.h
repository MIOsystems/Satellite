/*
 * fram.h
 *
 *  Created on: 27 Mar 2023
 *      Author: Kenley Strik
 */

#ifndef FRAM_H_
#define FRAM_H_

#define OPCODE_WREN 		0x06	// Set write enable latch
#define OPCODE_WRDI 		0x04	// Write disable
#define OPCODE_RDSR 		0x05	// Read status register
#define OPCODE_WRSR 		0x01	// Write status register
#define OPCODE_READ 		0x03	// Read memory data
#define OPCODE_WRITE 		0x02	// Write memory data

#define LAST_MEM_ADDRESS 	0x1FFF	// Last memory address location

#include <DAVE.h>

#include <include/util/delay.h>

typedef enum
{
	FRAM_ERR_OK = 0,
	FRAM_ERR_NOT_ENOUGH_SPACE = 1,
	FRAM_ERR_READ_FAILURE = 2,
	FRAM_ERR_WRITE_FAILURE = 3
} fram_err_t;

fram_err_t fram_enable_write();
fram_err_t fram_disable_write();

fram_err_t fram_read_status_register(uint8_t* value);
fram_err_t fram_write_status_register(uint8_t value);

fram_err_t fram_read_data(uint16_t offset, void* data, uint16_t size);
fram_err_t fram_write_data(uint16_t offset, void* data, uint16_t size);

#endif

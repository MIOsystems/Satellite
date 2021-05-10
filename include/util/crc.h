/*
 * crc.h
 *
 *  Created on: 6 May 2021
 *      Author: Patrick
 */

#ifndef CRC_H_
#define CRC_H_

#include <include/util/types.h>

#define TABLE_CRC_SIZE 256

typedef struct
{
	u16 crc_table[TABLE_CRC_SIZE];
	u16 initial_val;
	u16 poly;
	u16 checksum;
} CRC_t;

void crc16_init(CRC_t* crc, u16 initial, u16 poly);
void crc16_get(CRC_t* crc, u8 *bytes, u32 len);

#endif /* CRC_H_ */

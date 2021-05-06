/*
 * crc.h
 *
 *  Created on: 6 May 2021
 *      Author: Patrick
 */

#ifndef CRC_H_
#define CRC_H_

#include <include/util/types.h>

typedef struct
{
	u8 checksum0;
	u8 checksum1;
	u8 checksum2;
	u8 checksum3;
} CRC_t;

void crc16_init(CRC_t* crc);
void crc16_update(CRC_t* crc, u8 data);
void crc16_done(CRC_t* crc);
void crc16_get(CRC_t* crc);

#endif /* CRC_H_ */

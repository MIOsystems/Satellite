/*
 * crc.c
 *
 *  Created on: 6 May 2021
 *      Author: Patrick
 */

#include <include/util/crc.h>


void crc16Init(CRC_t* crc, u16 initial, u16 poly)
{

	crc->initial_val = initial;
	crc->poly = poly;
	crc->checksum = crc->initial_val;
	u16 temp;
	u16 a;

	for(i32 i = 0; i < TABLE_CRC_SIZE; i++)
	{
		temp = 0;
		a = i << 8;
		for(i32 j = 0; j < 8; j++)
		{
			if(((temp ^ a) & 0x8000) != 0)
			{
				temp = (u16) (((temp << 1)) ^ crc->poly);
			}
			else
			{
				temp <<= (u16) (1);
			}
			a <<= 1;
		}
		crc->crc_table[i] = temp;
	}
}

void crc16Get(CRC_t* crc, u8 *bytes, u32 len)
{

	for(u32 i = 0; i < len; i++)
	{
		crc->checksum = (u16) ((crc->checksum << 8) ^ crc->crc_table[( (crc->checksum >> 8) ^ (0xff & bytes[i]))]);
	}
}

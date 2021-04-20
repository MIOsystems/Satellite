/*
 * validate_model.h
 *
 *  Created on: 20 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_MODEL_H_
#define VALIDATE_MODEL_H_

#include <stdbool.h>

typedef struct
{
	u8 dip_1;
	u8 dip_2;
	u8 dip_3;
	u8 dip_4;
} validate_dip_t;

typedef struct
{
	bool d_out_1;
	bool d_out_2;
	bool d_out_3;
	bool d_out_4;
} validate_dig_out_t;

typedef struct
{
	u16 a_in_1;
	u16 a_in_2;
	u16 a_in_3;
} validate_a_in_t;

typedef struct
{
	validate_dip_t dip;
	validate_dig_out_t dout;
	validate_a_in_t ain;
	bool relay;
} validate_packet_t;


#endif /* VALIDATE_MODEL_H_ */

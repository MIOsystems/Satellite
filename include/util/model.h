/*
 * model.h
 *
 *  Created on: 23 Mar 2021
 *  Author: Patrick
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <include/util/types.h>
#include <DAVE.h>

typedef struct
{
	u8 reg_addr;
	u8 instr;
} RegOperation_t;

typedef struct
{
	u8 msb;
	u8 lsb;
} BitNumbering_t;


#endif /* MODEL_H_ */

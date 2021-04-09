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
} reg_operation_t;

typedef struct
{
	u8 pin;
	XMC_GPIO_PORT_t* gpio;
} port_t;

#endif /* MODEL_H_ */

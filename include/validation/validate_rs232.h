/*
 * validate_rs232.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_RS232_H_
#define VALIDATE_RS232_H_

#include <DAVE.h>
#include <include/util/types.h>

typedef enum
{
	RS232_DATA_ACTION_1,
	RS232_DATA_ACTION_2
} RS232_ACTIONS_e;

void validate_rs232_update();

#endif /* VALIDATE_RS232_H_ */

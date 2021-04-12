/*
 * validate_rs422.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_RS422_H_
#define VALIDATE_RS422_H_

#include <DAVE.h>
#include <include/util/types.h>

typedef enum
{
	RS422_DATA_ACTION_1,
	RS422_DATA_ACTION_2,
} RS422_ACTIONS_e;

void validate_rs422_update();

#endif /* VALIDATE_RS422_H_ */

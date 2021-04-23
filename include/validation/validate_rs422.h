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
#include <include/satellite.h>

#define MAX_BUFF_RECV		32
#define MAX_BUFF_TX			512

void validate_rs422_init();
void validate_rs422_update();
void validate_rs422_send();

#endif /* VALIDATE_RS422_H_ */

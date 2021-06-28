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

#define MAX_CHAR_RECV		32
#define MAX_CHAR_SEND		512

void validate_rs232_init();
void validate_rs232_update();
void validate_rs232_send();

#endif /* VALIDATE_RS232_H_ */

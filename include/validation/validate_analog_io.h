/*
 * validate_analog_io.h
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_ANALOG_IO_H_
#define VALIDATE_ANALOG_IO_H_

#include <DAVE.h>
#include <include/util/types.h>

volatile u16 ai1;
volatile u16 ai2;
volatile u16 ai3;

void validate_a_io_init();

#endif /* VALIDATE_ANALOG_IO_H_ */

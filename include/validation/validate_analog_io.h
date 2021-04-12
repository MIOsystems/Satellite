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

void validate_a_io_update();
void validate_a_io_feedback(u8 pin, u32 input);

#endif /* VALIDATE_ANALOG_IO_H_ */

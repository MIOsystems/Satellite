/*
 * validate_analog_io.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_analog_io.h>

const ANALOG_IO_t AI1 = {
		  .config_ptr = NULL,
		  .state  = ANALOG_IO_STATE_NOT_INITIALIZED,
		  .port = XMC_GPIO_PORT14,
		  .pin = 2
	};

const ANALOG_IO_t AI2 = {
		  .config_ptr = NULL,
		  .state  = ANALOG_IO_STATE_NOT_INITIALIZED,
		  .port = XMC_GPIO_PORT14,
		  .pin = 3
	};

const ANALOG_IO_t AI3 = {
		  .config_ptr = NULL,
		  .state  = ANALOG_IO_STATE_NOT_INITIALIZED,
		  .port = XMC_GPIO_PORT14,
		  .pin = 12
	};

void validate_a_io_update()
{
	u32 input = 0;
	input = ANALOG_IO_GetInput(&AI1);
	validate_a_io_feedback(AI1.pin);
	input = ANALOG_IO_GetInput(&AI2);
	validate_a_io_feedback(AI2.pin);
	input = ANALOG_IO_GetInput(&AI3);
	validate_a_io_feedback(AI3.pin);

}

void validate_a_io_feedback(u8 pin)
{

}

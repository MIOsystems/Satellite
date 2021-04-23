/*
 * validate_sensor_out.c
 *
 *  Created on: 22 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_sensor_out.h>


void validate_sensor_out_init()
{
	DIGITAL_IO_SetOutputLow(&SENS1_HI);
	DIGITAL_IO_SetOutputLow(&SENS1_LOW);
}

void validate_sensor_out_update(validate_sout_t* data)
{
	DIGITAL_IO_SetOutputLow(&SENS1_HI);
	DIGITAL_IO_SetOutputHigh(&SENS1_LOW);
}

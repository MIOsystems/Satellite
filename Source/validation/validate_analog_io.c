/*
 * validate_analog_io.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_analog_io.h>


void validate_a_io_init()
{
	ADC_MEASUREMENT_StartConversion(&AI1);
}

void validate_analog_io_handler(void)
{
	u16 input = 0;

	input = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A_handle); // result from 0 to 4096
	input = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_B_handle); // result from 0 to 4096
	input = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_C_handle); // result from 0 to 4096
}

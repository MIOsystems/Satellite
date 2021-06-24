/*
 * validate_analog_io.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_analog_io.h>
#include <include/satellite.h>

void validate_a_io_init()
{
	ADC_MEASUREMENT_StartConversion(&AI);
	ai1 = 0;
	ai2 = 0;
	ai3 = 0;
}

#ifdef RUN_HW_VALIDATION
void analog_handler(void)
{

	ai1 = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A_handle); // result from 0 to 4096
	ai2 = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_B_handle); // result from 0 to 4096
	ai3 = (u16) ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_C_handle); // result from 0 to 4096

}
#endif

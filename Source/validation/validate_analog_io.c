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
void validate_a_io_update()
{
//	u16 input = 0;
//	input = ADC_MEASUREMENT_ADV_GetResult(&AI1);
//	input = ANALOG_IO_GetInput(&AI1);
//	input = ANALOG_IO_GetInput(&AI2);
//	input = ANALOG_IO_GetInput(&AI3);
}

void validate_a_io_feedback(u8 pin, u32 input)
{

}

void Adc_Measurement_Handler(void)
{
	u16 input = 0;

	input = (u16) ADC_MEASUREMENT_GetResult(&AI1.array); // result from 0 to 4096

	ADC_MEASUREMENT_StartConversion(&AI1);
}

/*
 * validate_digital_out.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_digital_out.h>

volatile i32 timer;

void validate_digital_out_init()
{
	timer = 0;
}

void validate_digital_out_update()
{
	if(timer >= 0 && timer < 500)
	{
		DIGITAL_IO_SetOutputLow(&DO2);
		DIGITAL_IO_SetOutputLow(&DO3);
		DIGITAL_IO_SetOutputLow(&DO4);
		DIGITAL_IO_SetOutputHigh(&DO1);
	}
	else if(timer >= 500 && timer < 1000)
	{
		DIGITAL_IO_SetOutputLow(&DO1);
		DIGITAL_IO_SetOutputHigh(&DO2);
	}
	else if(timer >= 1000 && timer < 1500)
	{
		DIGITAL_IO_SetOutputLow(&DO2);
		DIGITAL_IO_SetOutputHigh(&DO3);
	}
	else if(timer >= 1500 && timer < 2000)
	{
		DIGITAL_IO_SetOutputLow(&DO3);
		DIGITAL_IO_SetOutputHigh(&DO4);

	}
	else if(timer >= 2000)
	{
		timer = 0;
		return;
	}
	timer++;
}

/*
 * validate_digital_out.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <stdbool.h>
#include <include/validation/validate_digital_out.h>

volatile i32 timer;

void validate_digital_out_init()
{
	timer = 0;
}

void validate_digital_out_update(validate_dig_out_t *d_out)
{
	if(timer >= 0 && timer < 500)
	{
		d_out->d_out_1 = true;
		d_out->d_out_2 = false;
		d_out->d_out_3 = false;
		d_out->d_out_4 = false;
		DIGITAL_IO_SetOutputHigh(&DO1);
		DIGITAL_IO_SetOutputLow(&DO2);
		DIGITAL_IO_SetOutputLow(&DO3);
		DIGITAL_IO_SetOutputLow(&DO4);

	}
	else if(timer >= 500 && timer < 1000)
	{
		d_out->d_out_1 = false;
		d_out->d_out_2 = true;
		DIGITAL_IO_SetOutputLow(&DO1);
		DIGITAL_IO_SetOutputHigh(&DO2);
	}
	else if(timer >= 1000 && timer < 1500)
	{
		d_out->d_out_2 = false;
		d_out->d_out_3 = true;
		DIGITAL_IO_SetOutputLow(&DO2);
		DIGITAL_IO_SetOutputHigh(&DO3);
	}
	else if(timer >= 1500 && timer < 2000)
	{
		d_out->d_out_3 = false;
		d_out->d_out_4 = true;
		DIGITAL_IO_SetOutputLow(&DO3);
		DIGITAL_IO_SetOutputHigh(&DO4);

	}
	else if(timer >= 2000)
	{
		d_out->d_out_1 = false;
		d_out->d_out_2 = false;
		d_out->d_out_3 = false;
		d_out->d_out_4 = false;
		timer = 0;
		return;
	}
	timer++;
}

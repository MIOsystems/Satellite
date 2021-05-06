/*
 * validatie_relay.c
 *
 *  Created on: 19 Apr 2021
 *      Author: Patrick
 */
#include <include/validation/validate_relay.h>

volatile u16 counter_relay;

const u16 start_index = 2500;
const u16 end_index = 5000;
void validate_relay_init()
{
	counter_relay = 0;
}
void validate_relay_update(bool *state)
{
	if(counter_relay >= start_index && counter_relay <= end_index)
	{
		DIGITAL_IO_SetOutputHigh(&RELAY);
		*state = true;
		if(counter_relay == end_index)
		{
			counter_relay = 0;
		}
		counter_relay++;
		return;
	}
	*state = false;
	DIGITAL_IO_SetOutputLow(&RELAY);
	counter_relay++;
}

/*
 * validatie_relay.c
 *
 *  Created on: 19 Apr 2021
 *      Author: Patrick
 */
#include <include/validation/validate_relay.h>

volatile u16 counter;
void validate_relay_init()
{
	counter = 0;
}
void validate_relay_update()
{
	if(counter == 2000)
	{
		DIGITAL_IO_SetOutputHigh(&RELAY);
		counter = 0;
		return;
	}
	counter++;
	DIGITAL_IO_SetOutputLow(&RELAY);

}

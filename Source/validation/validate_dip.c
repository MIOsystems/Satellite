/*
 * validate_dip.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_dip.h>

void validate_dip_update(validate_dip_t *dip) {
	u32 input = 0;
	input = DIGITAL_IO_GetInput(&DIP_ADD0);
	dip->dip_1 = input;
	validate_dip_led_cycle(0, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD1);
	dip->dip_2 = input;
	validate_dip_led_cycle(1, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD2);
	dip->dip_3 = input;
	validate_dip_led_cycle(2, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD3);
	validate_dip_led_cycle(3, input);
	dip->dip_4 = input;
}

void validate_dip_led_cycle(const u8 dip_nr, const u32 val)
{
	switch(dip_nr)
	{
		case 0:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_YELLOW);
			break;
		case 1:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_BLUE);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_BLUE);
			break;
		case 2:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_RED);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_RED);
			break;
		case 3:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_GREEN);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_GREEN);
			break;
	}
}

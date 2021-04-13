/*
 * validate_dip.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_dip.h>

const DIGITAL_IO_t DIP_ADD0 = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 10,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DIP_ADD1 = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 11,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DIP_ADD2 = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 12,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DIP_ADD3 = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 0,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

void validate_dip_update() {
	u32 input = 0;
	input = DIGITAL_IO_GetInput(&DIP_ADD0);
	validate_dip_led_cycle(0, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD1);
	validate_dip_led_cycle(1, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD2);
	validate_dip_led_cycle(2, input);
	input = DIGITAL_IO_GetInput(&DIP_ADD3);
	validate_dip_led_cycle(3, input);
}

void validate_dip_led_cycle(const u8 dip_nr, const u32 val)
{
	switch(dip_nr)
	{
		case 0:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_0);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_0);
			break;
		case 1:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_1);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_1);
			break;
		case 2:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_2);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_2);
			break;
		case 3:
			if(val == 1)
			{
				DIGITAL_IO_SetOutputHigh(&LED_3);
				break;
			}
			DIGITAL_IO_SetOutputLow(&LED_3);
			break;
	}
}

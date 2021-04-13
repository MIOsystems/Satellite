/*
 * validate_digital_out.c
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_digital_out.h>

const DIGITAL_IO_t DO1_O = {
		.gpio_port = XMC_GPIO_PORT1,
		.gpio_pin = 6,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DO2_O = {
		.gpio_port = XMC_GPIO_PORT1,
		.gpio_pin = 7,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DO3_O = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 3,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

const DIGITAL_IO_t DO4_O = {
		.gpio_port = XMC_GPIO_PORT3,
		.gpio_pin = 2,
		.gpio_config = {
				.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
				.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
		},
		.hwctrl = XMC_GPIO_HWCTRL_DISABLED
	};

void validate_digital_out_update()
{
	DIGITAL_IO_SetOutputHigh(&DO1_O);
	DIGITAL_IO_SetOutputHigh(&DO2_O);
	DIGITAL_IO_SetOutputHigh(&DO3_O);
	DIGITAL_IO_SetOutputHigh(&DO4_O);
}

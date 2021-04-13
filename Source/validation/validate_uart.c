/*
 * validate_uart.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_uart.h>

void validate_uart_update()
{
	u8 data = 0;
	u8 status = UART_Receive(&UART_2, &data, 1);

	if(status != UART_STATUS_SUCCESS)
		return;

	// TODO HANDLER UART
}

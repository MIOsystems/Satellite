/*
 * validatiuon_rs232.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_rs232.h>

void validate_rs232_update()
{
	u8 data = 0;
	u8 status = UART_Receive(&RS232_UART1, &data, 1);

	if(status != UART_STATUS_SUCCESS)
		return;

	switch(data)
	{
		case RS232_DATA_ACTION_1:
			break;

		case RS232_DATA_ACTION_2:
			break;
	}
}

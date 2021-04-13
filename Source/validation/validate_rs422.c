/*
 * validate_rs422.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_rs422.h>

void validate_rs422_update()
{

	u8 data = 0;
	u8 status = UART_Receive(&RS422_UART_0, &data, 1);

	if(status != UART_STATUS_SUCCESS)
		return;

	switch(data)
	{
		case RS422_DATA_ACTION_1:
			break;

		case RS422_DATA_ACTION_2:
			break;
	}
}

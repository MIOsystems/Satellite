/*
 * validate_rs422.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_rs422.h>


bool rs422_tx_allowed;
char recv_buff[MAX_BUFF_RECV];
char tx_buff[MAX_BUFF_TX];
u8 counter;

void validate_rs422_init()
{
	// Device Enable
	DIGITAL_IO_SetOutputHigh(&DE_422);

	DIGITAL_IO_SetOutputLow(&RE_422);
	rs422_tx_allowed = false;
	counter = 0;
	strcpy(tx_buff, "Satellite received on the RS422 the following: ");
}

void validate_rs422_update()
{
	u8 data = 0;
	u8 status = UART_Receive(&RS422_UART_0, &data, 1);

	if(status != UART_STATUS_SUCCESS)
		return;

	if(counter < (MAX_BUFF_RECV - 1))
	{
		recv_buff[counter] = data;
		if(data == 0xd)
		{
			rs422_tx_allowed = true;
			counter = 0;
			return;
		}
		counter++;
	}
	else
	{
		recv_buff[counter] = '\0';
		rs422_tx_allowed = true;
		counter = 0;
		return;
	}

}

void validate_rs422_send()
{
	if(rs422_tx_allowed)
	{
		strcat(tx_buff, recv_buff);
		u8 i = 0;
		u8 status = 0;
		while(tx_buff[i] != '\0')
		{
			status = UART_Transmit(&RS422_UART_0, (u8 *) &tx_buff[i], 1);
			i++;
		}

		rs422_tx_allowed = false;
		memset(tx_buff, '\0', sizeof(char) * MAX_BUFF_TX);
		strcpy(tx_buff, "Satellite received on the RS422 the following: ");
	}
}

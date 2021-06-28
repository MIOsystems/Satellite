/*
 * validate_uart.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_uart.h>
#include <stdbool.h>
#include <stdlib.h>

bool tx_allowed;
char recv_buff[MAX_CHAR_RECV];
char tx_buff[MAX_CHAR_SEND];
u8 counter;

void validate_uart_init()
{
	tx_allowed = false;
	counter = 0;

	strcpy(tx_buff, "Satellite received on the UART the following: ");
}

void validate_uart_update()
{
	u8 data = 0;
	u8 status = UART_Receive(&UART_2, &data, 1);

	if (status != UART_STATUS_SUCCESS)
		return;

	if (counter < (MAX_CHAR_RECV - 1))
	{
		recv_buff[counter] = data;
		if (data == 0xd)
		{
			tx_allowed = true;
			counter = 0;
			return;
		}
		counter++;
	}
	else
	{
		recv_buff[counter] = '\0';
		tx_allowed = true;
		counter = 0;
		return;
	}
}

void validate_uart_send()
{
	if(tx_allowed)
	{
		strcat(tx_buff, recv_buff);
		u8 i = 0;
		while(tx_buff[i] != '\0')
		{
			UART_Transmit(&UART_2, (u8 *) &tx_buff[i], 1);
			i++;
		}

		tx_allowed = false;
		memset(tx_buff, '\0', sizeof(char) * MAX_CHAR_SEND);
		strcpy(tx_buff, "Satellite received on the UART the following: ");
	}
}

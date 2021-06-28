/*
 * validatiuon_rs232.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/validation/validate_rs232.h>
#include <stdbool.h>
#include <stdlib.h>

bool answer;
char recv_buff[MAX_CHAR_RECV];
char tx_buff[MAX_CHAR_SEND];
u8 counter;

void validate_rs232_init()
{
	answer = false;
	counter = 0;

	strcpy(tx_buff, "Satellite received on the RS232 the following: ");
}

void validate_rs232_update()
{
	u8 data = 0;
	u8 status = UART_Receive(&RS232_UART1, &data, 1);
	if(status != UART_STATUS_SUCCESS)
		return;

	if(counter < (MAX_CHAR_RECV - 1))
	{
		recv_buff[counter] = data;
		if(data == 0xd)
		{
			answer = true;
			counter = 0;
			return;
		}
		counter++;
	}
	else
	{
		recv_buff[counter] = '\0';
		answer = true;
		counter = 0;
		return;
	}
}

void validate_rs232_send()
{
	if(answer)
	{
		strcat(tx_buff, recv_buff);
		u8 i = 0;
		while(tx_buff[i] != '\0')
		{
			UART_Transmit(&RS232_UART1, (u8 *) &tx_buff[i], 1);
			i++;
		}

		answer = false;
		memset(tx_buff, '\0', sizeof(char) * MAX_CHAR_SEND);
		strcpy(tx_buff, "Satellite received on the RS232 the following: ");
	}
}

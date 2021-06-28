/*
 * sf30.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <include/sensor/altimeter/SF30/sf30.h>
#include <stdbool.h>


u8 rx_data[1];
bool high_byte_flag = true;
uint16_t distance_raw = 0;
bool rx_ready;

void sf30_init(AltimeterData_t* data)
{
	rx_data[0] = 0;
	rx_data[1] = 0;
	data->bitNumber.lsb = 0;
	data->bitNumber.msb = 0;
	data->recvCounter = 0;
	data->altimeterAvg = 0;
	data->altimeterCurValue = 0;
	data->altimeterSum = 0;
}

void sf30_update(AltimeterData_t* data)
{
	if (rx_ready == true)
	{
		data->recvCounter++;
		data->bitNumber.msb = rx_data[0];
		data->bitNumber.lsb = rx_data[1];

		data->altimeterCurValue = distance_raw;
		data->altimeterSum += data->altimeterCurValue;
		data->altimeterAvg = data->altimeterSum / data->recvCounter;



		rx_ready = false;
	}
}

void sf30_reset(AltimeterData_t* data)
{
	data->bitNumber.msb = 0;
	data->bitNumber.lsb = 0;
	data->recvCounter = 0;
	data->altimeterAvg = 0;
	data->altimeterCurValue = 0;
	data->altimeterSum = 0;
}

void sf30_rx_handle()
{
	if (rx_ready == false)
	{
		u8 status = 0;

		status = UART_Receive(&RS422_UART_0, rx_data, 1);

		if (status != UART_STATUS_SUCCESS)
		{
			return;
		}
		if((rx_data[0] & (1 << 7)) == 128)    //If high byte_bit is set
		{
			distance_raw = (rx_data[0] & 0x7F) * 128;
			high_byte_flag = true;
		}
		else if(high_byte_flag)
		{
			distance_raw += (rx_data[0] & 0x7F);
			high_byte_flag = false;
			rx_ready = true;

//			if(distance_raw != 16000)
//			{
//
//
//			}
		}

	}
}

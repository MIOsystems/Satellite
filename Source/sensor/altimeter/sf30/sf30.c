/*
 * sf30.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <include/sensor/altimeter/SF30/sf30.h>
#include <stdbool.h>

u8 rx_data[2];
bool rx_ready;

void sf30_init(AltimeterData_t* data)
{
	rx_data[0] = 0;
	rx_data[1] = 0;
	data->bitNumber.lsb = 0;
	data->bitNumber.msb = 0;
	data->recv_counter = 0;
	data->altimeter_avg = 0;
	data->altimeter_cur_val = 0;
	data->altimeter_sum = 0;
}

void sf30_update(AltimeterData_t* data)
{
	if(rx_ready == true)
	{
		// resetting it
		if(data->recv_counter == 1000)
		{
			data->bitNumber.msb = 0;
			data->bitNumber.lsb = 0;
			data->recv_counter = 0;
			data->altimeter_avg = 0;
			data->altimeter_cur_val = 0;
			data->altimeter_sum = 0;
		}
		if(data->recv_counter == 999)
		{
			data->recv_counter++;
			data->bitNumber.msb = rx_data[0];
			data->bitNumber.lsb= rx_data[1];
			data->altimeter_cur_val = ((data->bitNumber.msb & 0x7F) * 128) + (data->bitNumber.lsb & 0x7F);
			data->altimeter_sum += data->altimeter_cur_val;
			data->altimeter_avg = data->altimeter_sum / data->recv_counter;
		} else {
			data->recv_counter++;

			data->bitNumber.msb = rx_data[0];
			data->bitNumber.lsb = rx_data[1];
			data->altimeter_cur_val = ((data->bitNumber.msb & 0x7F) * 128) + (data->bitNumber.lsb & 0x7F);
			data->altimeter_sum += data->altimeter_cur_val;
			data->altimeter_avg = data->altimeter_sum / data->recv_counter;
		}
		rx_ready = false;
	}
}

void sf30_rx_handle()
{
	if(rx_ready == false)
	{
		u8 status = 0;

		status = UART_Receive(&RS422_UART_0, rx_data, 2);

		if(status != UART_STATUS_SUCCESS)
		{
			return;
		}
		if((rx_data[0] & (1 << 7)) == 128)
		{
			rx_ready = true;
		}

	}


}

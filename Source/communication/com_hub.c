/*
 * com_hub.c
 *
 *  Created on: 29 Apr 2021
 *      Author: Patrick
 */

#include <stdbool.h>

#include <include/communication/com_hub.h>
#include <include/satellite.h>
#include <include/hardware/digital_output.h>
#include <include/util/crc.h>

volatile u8 rx_buff[HUB_BUFFER_SIZE];
volatile u8 tx_buff[HUB_BUFFER_SIZE];
volatile u8 recv_buff[HUB_BUFFER_SIZE];
volatile bool recv_new_data;
volatile u32 frame_counter;
volatile u16 recv_dlc;
volatile u16 recv_len;
volatile u16 recv_crc;
volatile u8 recv_flags;

CRC_t checksum;

u8 com_hub_init()
{

	DIGITAL_IO_SetOutputHigh(&DE_422);

	DIGITAL_IO_SetOutputLow(&RE_422);

//	// check if it is indeed low
//	u32 can_switch_val = DIGITAL_IO_GetInput(&CAN_MOD_SWITCH);
//	if(can_switch_val != DIGITAL_OUTPUT_HIGH)
//	{
//		return COM_HUB_STATUS_MOD_SWITCH_HIGH;
//	}

	com_hub_clear_buffer();
	recv_new_data = false;
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	return COM_HUB_STATUS_SUCCESS;
}


void com_hub_recv()
{
	u8 rx_data = 0;
	UART_STATUS_t status = UART_Receive(&RS422_UART_0, &rx_data , 1);

	if(status != UART_STATUS_SUCCESS)
	{
		DIGITAL_IO_SetOutputHigh(&LED_2);
		return;
	}

	DIGITAL_IO_SetOutputLow(&LED_2);

	switch(frame_counter)
	{
		default:
			frame_counter = 0;
			break;

		case CAN_FRAME_START0:
			if(rx_data == CAM_FRAME_START1_OPCODE)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter++;
				break;
			}
			com_hub_reset();
			break;

		case CAN_FRAME_START1:
			if(rx_data == CAN_FRAME_START2_OPCODE)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter++;
				break;
			}
			com_hub_reset();
			break;
		case CAN_FRAME_DEST:
			if(rx_data == CAN_ADDRESS_SATELLITE || rx_data == CAN_ADDRESS_BROADCAST)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter++;
				// TODO ADD CHECKSUM CALCULATIONS
				break;
			}
			com_hub_reset();
			break;
		case CAN_FRAME_SRC:
			rx_buff[frame_counter] = rx_data;
			// TODO CHECKSUM
			frame_counter++;
			break;
		case CAN_FRAME_FLAGS:

			if(rx_data & 0xf0) // if true bad frame
			{
				com_hub_reset();
				break;
			}

			// TODO CHECKSUM
			rx_buff[frame_counter] = rx_data;
			frame_counter++;
			break;
		case CAN_FRAME_DLC_MSB:
			rx_buff[frame_counter] = rx_data;
			recv_dlc = rx_data << 8;
			frame_counter++;
			// TODO CHECKSUM
			break;
		case CAN_FRAME_DLC_LSB:
			recv_dlc |= rx_data;
			recv_len = 0;
			rx_buff[frame_counter] = rx_data;
			frame_counter++;
			break;
		case CAN_FRAME_PAYLOAD:
			if(recv_new_data)
			{
				com_hub_reset();
				break;
			}
			recv_buff[recv_len++] = rx_data;

			if(recv_len == recv_dlc)
			{
				frame_counter++;
				break;
			}
			if(recv_len == HUB_BUFFER_SIZE)
			{
				com_hub_reset();
				break;
			}
			break;

		case CAN_FRAME_CRC_MSB:
			recv_crc = rx_data << 8;
			rx_buff[frame_counter] = rx_data;
			frame_counter++;
			break;

		case CAN_FRAME_CRC_LSB:
			rx_buff[frame_counter] = rx_data;
			recv_crc |= rx_data;
			recv_new_data = true;
			frame_counter = 0;
			break;
	}
}

void com_hub_recv_handle()
{
	if(recv_new_data)
	{
		// Command
		if(!recv_flags)
		{

		}
		// Request
		else
		{

		}
		com_hub_reset();
	}
}

u8 com_hub_send(void* payload, u16 len)
{
	if(len <= 0)
		return COM_HUB_STATUS_INVALID_PAYLOAD;

	return 0;
}

void com_hub_clear_buffer()
{
	for(size_t i = 0; i < HUB_BUFFER_SIZE; i++)
	{
		rx_buff[i] = 0;
		tx_buff[i] = 0;
	}
}

void com_hub_reset()
{
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	recv_new_data = false;
}

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



// Stores whole message for crc
u8 rx_buff[HUB_BUFFER_SIZE];
u8 tx_buff[HUB_BUFFER_SIZE];
volatile u8 recv_payload_buff[HUB_BUFFER_SIZE];
volatile bool recv_new_data;
volatile u32 frame_counter;
volatile u16 recv_dlc;
volatile u16 recv_len;
volatile u16 recv_crc;
volatile u8 recv_flags;
volatile u8 recv_src;

CRC_t crc;

u8 com_hub_init()
{

	DIGITAL_IO_SetOutputHigh(&CAN_MOD_SWITCH);

	com_hub_clear_buffer();
	recv_new_data = false;
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	crc16_init(&crc, 0x1d0f, 0x1021);
	return COM_HUB_STATUS_SUCCESS;
}


void com_hub_recv()
{
	u8 rx_data = 0;
	UART_STATUS_t status = UART_Receive(&HUB_UART_3, &rx_data , 1);

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
			if(rx_data == CAN_FRAME_START1_OPCODE)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter = CAN_FRAME_START1;
				break;
			}
			com_hub_reset();
			break;

		case CAN_FRAME_START1:
			if(rx_data == CAN_FRAME_START2_OPCODE)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter = CAN_FRAME_DEST;
				break;
			}
			com_hub_reset();
			break;
		case CAN_FRAME_DEST:
			if(rx_data == CAN_ADDRESS_SATELLITE || rx_data == CAN_ADDRESS_BROADCAST)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter = CAN_FRAME_SRC;

				break;
			}
			com_hub_reset();
			break;
		case CAN_FRAME_SRC:
			recv_src = rx_data;
			rx_buff[frame_counter] = rx_data;
			frame_counter = CAN_FRAME_FLAGS;
			break;
		case CAN_FRAME_FLAGS:

			recv_flags = rx_data;
			rx_buff[frame_counter] = rx_data;
			if(rx_data & 0xf0) // if true bad frame
			{
				com_hub_reset();
				break;
			}
			frame_counter = CAN_FRAME_DLC_MSB;
			break;
		case CAN_FRAME_DLC_MSB:
			recv_dlc = rx_data << 8;
			rx_buff[frame_counter] = rx_data;
			frame_counter = CAN_FRAME_DLC_LSB;
			break;
		case CAN_FRAME_DLC_LSB:
			recv_dlc |= rx_data;
			rx_buff[frame_counter] = rx_data;
			recv_len = 0;
			frame_counter = CAN_FRAME_PAYLOAD;
			break;
		case CAN_FRAME_PAYLOAD:
			if(recv_new_data)
			{
				DIGITAL_IO_SetOutputHigh(&LED_0);
				com_hub_reset();

				break;
			}
			rx_buff[frame_counter + recv_len] = rx_data;
			recv_payload_buff[recv_len++] = rx_data;

			if(recv_len == recv_dlc)
			{
				frame_counter = CAN_FRAME_CRC_MSB;
				break;
			}
			if(recv_len == HUB_BUFFER_SIZE)
			{
				DIGITAL_IO_SetOutputHigh(&LED_1);
				com_hub_reset();
				break;
			}
			break;

		case CAN_FRAME_CRC_MSB:
			recv_crc = rx_data << 8;
			rx_buff[frame_counter + recv_len] = rx_data;
			frame_counter = CAN_FRAME_CRC_LSB;
			break;

		case CAN_FRAME_CRC_LSB:
			rx_buff[frame_counter + recv_len] = rx_data;
			recv_crc |= rx_data;
			u32 crc_len = (frame_counter + recv_len - 2);
			crc16_get(&crc, rx_buff, crc_len);
			u16 calc_crc = crc.checksum;
			if(calc_crc  != recv_crc)
			{
				DIGITAL_IO_SetOutputHigh(&LED_2);
				com_hub_reset();
			}
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
		else
		{
			if(recv_len == 1)
			{
				const u8 req = recv_payload_buff[0];
				ComHubStatus_e status = COM_HUB_STATUS_SUCCESS;
				switch(req)
				{
					case CAN_REQ_EXISTENCE:
						com_hub_send("!", 1);
						com_hub_reset();
						break;
					case CAN_REQ_MEASUREMENTS:
						com_hub_create_packet();
						com_hub_send(&measurementPayload, sizeof(measurementPayload));
						com_hub_reset();
						break;
					case CAN_REQ_GNSS_DATA:
						com_hub_send(&gps_packet, sizeof(gps_packet));
						com_hub_reset();
						break;
					case CAN_REQ_EVENTS:

						com_hub_reset();
						break;
					case CAN_REQ_STATUS:
						com_hub_reset();
						break;
				}

			}
		}
		com_hub_reset();
		com_hub_clear_buffer();
	}
}

u8 com_hub_send(void* payload, u16 len)
{

	if(len <= 0)
	{
		return COM_HUB_STATUS_INVALID_PAYLOAD;
	}
	UART_STATUS_t status = UART_STATUS_SUCCESS;
	tx_buff[0] = CAN_FRAME_START1_OPCODE;
	tx_buff[1] = CAN_FRAME_START2_OPCODE;
	tx_buff[2] = CAN_ADDRESS_SATELLITE;
	tx_buff[3] = CAN_ADDRESS_MASTER;
	tx_buff[4] = CAN_REGUEST_FLAG;
	tx_buff[5] = len >> 8;
	tx_buff[6] = len;

	memcpy(&tx_buff[7], payload, len);

	crc16_get(&crc, tx_buff, len + 7);
	u16 crc_result = crc.checksum;
	tx_buff[7 + len] = crc_result >> 8;
	tx_buff[7 + (len + 1)] = crc_result;



	status = UART_Transmit(&HUB_UART_3, tx_buff, sizeof(tx_buff));


	return status;
}

void com_hub_clear_buffer()
{
	for(size_t i = 0; i < HUB_BUFFER_SIZE; i++)
	{
		rx_buff[i] = 0;
		tx_buff[i] = 0;
		recv_payload_buff[i] = 0;
	}
}

void com_hub_reset()
{
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	recv_new_data = false;
	crc16_init(&crc, 0x1d0f, 0x1021);
}

void com_hub_create_packet()
{
#ifdef ENABLE_ALTIMETER
	measurementPayload.altimeterVal = altimeter_data.altimeter_cur_val;
#else
	measurementPayload.altimeterVal = 0;
#endif

#ifdef ENABLE_PROXIMITY_SWITCH
	measurementPayload.proximityDistance = prox_switch.distance;
#else
	measurementPayload.proximityDistance = 0;
#endif
}
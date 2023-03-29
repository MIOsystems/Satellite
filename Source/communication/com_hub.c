/*
 * com_hub.c
 *
 *  Created on: 29 Apr 2021
 *      Author: Patrick
 */

#include <stdbool.h>

#include <include/communication/com_hub.h>

#ifdef HUB_CONNECTED

//#include <include/satellite.h>
#include <include/hardware/digital_output.h>

//MeasurementPayloadPacket_t measurementsPayloadPackets[2];


// Stores whole message for crc
u8 rx_buff[HUB_PAYLOAD_BUFFER_SIZE];
u8 tx_buff[HUB_PAYLOAD_BUFFER_SIZE];
volatile u8 recv_payload_buff[HUB_PAYLOAD_BUFFER_SIZE];
volatile bool recv_new_data;
volatile u32 frame_counter;
volatile u16 recv_dlc;
volatile u16 recv_len;
volatile u16 recv_crc;
volatile u8 recv_flags;
volatile u8 recv_src;

CRC_t crc;

u8 comHubInit()
{
	// Setting this high to use the UART
	DIGITAL_IO_SetOutputHigh(&CAN_MOD_SWITCH);
	comHubClearBuffer();
	recv_new_data = false;
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	crc16Init(&crc, 0x1d0f, 0x1021);
	return COM_HUB_STATUS_SUCCESS;
}


void comHubRecv()
{
	u8 rx_data = 0;
	UART_STATUS_t status = UART_Receive(&RS422_UART_0, &rx_data , 1);

	if(status != UART_STATUS_SUCCESS)
	{
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		return;
	}

	DIGITAL_IO_SetOutputLow(&LED_RED);


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
			comHubReset();
			break;

		case CAN_FRAME_START1:
			if(rx_data == CAN_FRAME_START2_OPCODE)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter = CAN_FRAME_DEST;
				break;
			}
			comHubReset();
			break;
		case CAN_FRAME_DEST:
			if(rx_data == CAN_ADDRESS_SATELLITE || rx_data == CAN_ADDRESS_BROADCAST)
			{
				rx_buff[frame_counter] = rx_data;
				frame_counter = CAN_FRAME_SRC;

				break;
			}
			comHubReset();
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
				comHubReset();
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
				DIGITAL_IO_SetOutputHigh(&LED_RED);
				comHubReset();

				break;
			}
			rx_buff[frame_counter + recv_len] = rx_data;
			recv_payload_buff[recv_len++] = rx_data;

			if(recv_len == recv_dlc)
			{
				frame_counter = CAN_FRAME_CRC_MSB;
				break;
			}
			if(recv_len == HUB_PAYLOAD_BUFFER_SIZE)
			{
				DIGITAL_IO_SetOutputHigh(&LED_RED);
				comHubReset();
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
			crc16Get(&crc, rx_buff, crc_len);
			u16 calc_crc = crc.checksum;
			if(calc_crc  != recv_crc)
			{
				DIGITAL_IO_SetOutputHigh(&LED_RED);
				comHubReset();
			}
			recv_new_data = true;
			frame_counter = 0;
			break;
	}
}

void comHubRecvHandle()
{
	if(recv_new_data)
	{
		// Command
		if(!recv_flags)
		{
			const u8 req = recv_payload_buff[0];
			comHubCreateRespondCommandoPacket();
			switch(req)
			{
				case 0:
					comHubCreateRespondCommandoPacket();
					comHubSend();
					comHubReset();
					break;
				default:
					break;
			}
		}
		else
		{
			if(recv_len == 1)
			{
				const u8 req = recv_payload_buff[0];
				switch(req)
				{
					case CAN_REQ_EXISTENCE:
						comHubCreateExistencePacket();
						comHubSend();
						comHubReset();
						break;
					case CAN_REQ_MEASUREMENTS:
						comHubCreateMeasurePacket();
						comHubSend();
						comHubReset();
						break;
					case CAN_REQ_GNSS_DATA:
						comHubCreateGPSPacket();
						comHubSend();
						comHubReset();
						break;
					case CAN_REQ_EVENTS:

						comHubReset();
						break;
					case CAN_REQ_STATUS:
						comHubReset();
						break;
				}

			}
		}
		comHubReset();
		comHubClearBuffer();
	}
}

u8 comHubSend(void)
{
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	UART_STATUS_t status = UART_STATUS_SUCCESS;

	for(uint8_t i = 0; i < HUB_PAYLOAD_BUFFER_SIZE; i++)
	{
		status = UART_Transmit(&RS422_UART_0, &tx_buff[i], sizeof(i));
	}

	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	return status;
}

void comHubClearBuffer()
{
	for(size_t i = 0; i < HUB_PAYLOAD_BUFFER_SIZE; i++)
	{
		rx_buff[i] = 0;
		tx_buff[i] = 0;
		recv_payload_buff[i] = 0;
	}
}

void comHubReset()
{
	frame_counter = CAN_FRAME_START0;
	recv_dlc = 0;
	recv_len = 0;
	recv_crc = 0;
	recv_new_data = false;
	crc16Init(&crc, 0x1d0f, 0x1021);
}

void comHubCreateMeasurePacket()
{

	tx_buff[CAN_FRAME_START0] = CAN_FRAME_START1_OPCODE;
	tx_buff[CAN_FRAME_START1] = CAN_FRAME_START2_OPCODE;

	tx_buff[CAN_FRAME_DEST] = CAN_ADDRESS_MASTER;
	tx_buff[CAN_FRAME_SRC] = CAN_ADDRESS_SATELLITE;
	tx_buff[CAN_FRAME_FLAGS] = FLAG_REQUEST;




	MeasurementPayloadPacket_t measurementsPayloadPackets[2];
#ifdef ENABLE_ALTIMETER
	canMeasurementsMessage.altimeterVal = altimeter_data.altimeter_cur_val;
#else
	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].id = RM_SENSOR_INDUCTOR;
	const u16 val = 4095;
	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].size = sizeof(val);
	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].value = val;
#endif
#ifdef ENABLE_PROXIMITY_SWITCH
	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].id = RM_SENSOR_INDUCTOR;

	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].size = sizeof(prox_switch.distance);
	measurementsPayloadPackets[RM_SENSOR_INDUCTOR].value = prox_switch.distance;
#else
	measurementsPayloadPackets[RM_SENSOR_ALTIMETER].id = RM_SENSOR_ALTIMETER;
	const u16 altimeterVal = 975;
	measurementsPayloadPackets[RM_SENSOR_ALTIMETER].size = sizeof(altimeterVal);
	measurementsPayloadPackets[RM_SENSOR_ALTIMETER].value = altimeterVal;
#endif

	const u32 size = sizeof(measurementsPayloadPackets);
	tx_buff[CAN_FRAME_DLC_MSB] = size >> 8;
	tx_buff[CAN_FRAME_DLC_LSB] = size;

	// Adding the packets
	const u16 index = CAN_FRAME_PAYLOAD + sizeof(measurementsPayloadPackets[RM_SENSOR_ALTIMETER]);
	memcpy(&tx_buff[CAN_FRAME_PAYLOAD], &measurementsPayloadPackets[RM_SENSOR_INDUCTOR], sizeof(measurementsPayloadPackets[RM_SENSOR_INDUCTOR]));
	memcpy(&tx_buff[index], &measurementsPayloadPackets[RM_SENSOR_ALTIMETER], sizeof(measurementsPayloadPackets[RM_SENSOR_INDUCTOR]));
	crc16Get(&crc, tx_buff, 9 + size);
	u16 crc_result = crc.checksum;
	tx_buff[index] = crc_result >> 8;
	tx_buff[index + 1] = crc_result;
}

void comHubCreateExistencePacket()
{
	tx_buff[CAN_FRAME_START0] = CAN_FRAME_START1_OPCODE;
	tx_buff[CAN_FRAME_START1] = CAN_FRAME_START2_OPCODE;
	tx_buff[CAN_FRAME_DEST] = CAN_ADDRESS_MASTER;
	tx_buff[CAN_FRAME_SRC] = CAN_ADDRESS_SATELLITE;
	tx_buff[CAN_FRAME_FLAGS] = FLAG_REQUEST;

	tx_buff[CAN_FRAME_PAYLOAD] = '!';
	const size_t size = sizeof(char);
	tx_buff[CAN_FRAME_DLC_MSB] = size >> 8;
	tx_buff[CAN_FRAME_DLC_LSB] = size;
	crc16Get(&crc, tx_buff, 9 + size);
	u16 crc_result = crc.checksum;
	tx_buff[CAN_FRAME_PAYLOAD + 1] = crc_result >> 8;
	tx_buff[CAN_FRAME_PAYLOAD + 2] = crc_result;
}

void comHubCreateGPSPacket()
{
	tx_buff[CAN_FRAME_START0] = CAN_FRAME_START1_OPCODE;
	tx_buff[CAN_FRAME_START1] = CAN_FRAME_START2_OPCODE;
	tx_buff[CAN_FRAME_DEST] = CAN_ADDRESS_MASTER;
	tx_buff[CAN_FRAME_SRC] = CAN_ADDRESS_SATELLITE;
	tx_buff[CAN_FRAME_FLAGS] = FLAG_COMMAND;

	memcpy(&tx_buff[CAN_FRAME_PAYLOAD], &gpsPacket, sizeof(gpsPacket));
	const size_t size = sizeof(gpsPacket);
	tx_buff[CAN_FRAME_DLC_MSB] = size >> 8;
	tx_buff[CAN_FRAME_DLC_LSB] = size;
	crc16Get(&crc, tx_buff, 9 + size);
	u16 crc_result = crc.checksum;
	tx_buff[CAN_FRAME_PAYLOAD + size + 1] = crc_result >> 8;
	tx_buff[CAN_FRAME_PAYLOAD + size + 2] = crc_result;
}

void comHubCreateRespondCommandoPacket()
{
	tx_buff[CAN_FRAME_START0] = CAN_FRAME_START1_OPCODE;
	tx_buff[CAN_FRAME_START1] = CAN_FRAME_START2_OPCODE;
	tx_buff[CAN_FRAME_DEST] = CAN_ADDRESS_MASTER;
	tx_buff[CAN_FRAME_SRC] = CAN_ADDRESS_SATELLITE;
	tx_buff[CAN_FRAME_FLAGS] = FLAG_COMMAND;

	const size_t size = sizeof(u8);
	tx_buff[CAN_FRAME_DLC_MSB] = size >> 8;
	tx_buff[CAN_FRAME_DLC_LSB] = size;
	tx_buff[CAN_FRAME_PAYLOAD] = 0; // TODO CHANGE THIS
	crc16Get(&crc, tx_buff, 9 + size);
	u16 crc_result = crc.checksum;
	tx_buff[CAN_FRAME_PAYLOAD + size + 1] = crc_result >> 8;
	tx_buff[CAN_FRAME_PAYLOAD + size + 2] = crc_result;
}

#endif

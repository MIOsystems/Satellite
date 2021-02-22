/*
 * GNSS.cpp
 *
 *  Created on: 22 Feb 2021
 *      Author: Patrick
 */

#include <string.h>

#include <Header/GNSS.h>

GNSS::GNSS()
{
	this->gnss_data = new GNSSData();
	this->gnss_frame = new GNSSFrame();
	this->raw_data = 0;
	this->frame_counter = 0;
}

u8 GNSS::init()
{

}

u8 GNSS::poll()
{
	u8 status = 0;
	u16 frame_length = 0;
	u16 checksum_rx = 0;

	status = UART_Receive(&UART_1, &this->raw_data, 1);
	// Wait if uart channels are still busy
	if(&UART_1.runtime->rx_busy || &UART_1.runtime->tx_busy)
	{
		while (&UART_1.runtime->rx_busy || &UART_1.runtime->tx_busy)
		{

		}
	}

	if(status != UART_STATUS_SUCCESS)
	{
		return status;
	}

	switch (this->frame_counter)
	{
		// If its not in one of these switches we can assume it is is the start
		default:
			this->frame_counter = UBX_FRAME_HEADER_1;
		case UBX_FRAME_HEADER_1:
			validate(this->raw_data, GNSS_GPS_SYNC_1, UBX_FRAME_HEADER_1);
			break;
		case UBX_FRAME_HEADER_2:
			validate(this->raw_data, GNSS_GPS_SYNC_2, UBX_FRAME_CLASS);
			break;
		case UBX_FRAME_CLASS:
			this->gnss_frame = new GNSSFrame();
			gnss_frame->setClassDef(this->raw_data);
			gnss_frame->updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_ID;
			break;

		case UBX_FRAME_ID:
			this->gnss_frame->setId(this->raw_data);
			this->gnss_frame->updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_DLC1;
			break;
		case UBX_FRAME_DLC1:
			this->gnss_frame->setLength(this->raw_data);
			this->gnss_frame->updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_DLC0;
			break;
		case UBX_FRAME_DLC0:
			frame_length = this->gnss_frame->getLength();
			frame_length |= this->raw_data << 8;
			this->gnss_frame->setLength(frame_length);
			this->gnss_frame->updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_PAYLOAD;
			break;

		case UBX_FRAME_PAYLOAD:
			this->gnss_frame->payload[this->gps_payload_index++] = raw_data;
			this->gnss_frame->updateCheckSum(this->raw_data);
			if(gps_payload_index == this->gnss_frame->getLength()) //DLC reached
			{
				this->frame_counter = UBX_FRAME_CK_A;
				break;
			}

			if(gps_payload_index == GNSS_GPS_BUFF_S) //buffer overflow
			{

				this->frame_counter = UBX_FRAME_HEADER_1;
				break;
			}

			break;

		case UBX_FRAME_CK_A:
			this->gnss_frame->getChecksum();
			this->gnss_frame->setChecksumRx(this->raw_data);
			this->frame_counter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:
			checksum_rx = this->gnss_frame->getChecksumRx();
			checksum_rx |= this->raw_data << 8;
			this->gnss_frame->setChecksumRx(checksum_rx);

			if(this->gnss_frame->getChecksumRx()
					!= this->gnss_frame->getChecksumCalc())
			{
				this->frame_counter = UBX_FRAME_HEADER_1;
				break;
			}

			this->rx_ready = true;
			this->frame_counter = UBX_FRAME_HEADER_1;
			break;
	}
}

u8 GNSS::select(u8 chip)
{

}

u8 GNSS::write(u8 addr, u8 data)
{

}

const char* GNSS::to_string()
{

}

void GNSS::convert_payload()
{
	memcpy(&this->gnss_data->epoch,				&this->gnss_frame->payload[0],	4);
	memcpy(&this->gnss_data->fix,				&this->gnss_frame->payload[20],	1);
	memcpy(&this->gnss_data->num_sat,			&this->gnss_frame->payload[23],	1);
	memcpy(&this->gnss_data->lon,				&this->gnss_frame->payload[24],	4);
	memcpy(&this->gnss_data->lat,				&this->gnss_frame->payload[28],	4);
	memcpy(&this->gnss_data->height_ellipsoid,	&this->gnss_frame->payload[32],	4);
	memcpy(&this->gnss_data->height_msl,		&this->gnss_frame->payload[36],	4);
	memcpy(&this->gnss_data->hor_acc,			&this->gnss_frame->payload[40],	4);
	memcpy(&this->gnss_data->ver_acc,			&this->gnss_frame->payload[44],	4);
	memcpy(&this->gnss_data->speed,				&this->gnss_frame->payload[60],	4);
	memcpy(&this->gnss_data->heading,			&this->gnss_frame->payload[64],	4);
	memcpy(&this->gnss_data->speed_acc,			&this->gnss_frame->payload[68],	4);
	memcpy(&this->gnss_data->head_acc,			&this->gnss_frame->payload[72],	4);
}

void GNSS::validate(u8 _data, u8 _expected_data, u8 _fallback)
{
	if(_data == _expected_data)
	{
		this->frame_counter = _expected_data;
	}else
	{
		this->frame_counter = _fallback;
	}
}

void GNSS::rx_handler()
{
	if(this->rx_ready)
	{
		const u16 msg_type = (u16) (this->gnss_frame->getClassDef() << 8)
				| this->gnss_frame->getId();
		if(msg_type == 0x0107)
		{

		}
		this->rx_ready = false;
	}
}

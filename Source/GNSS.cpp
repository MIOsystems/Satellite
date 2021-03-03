/*
 * GNSS.cpp
 *
 *  Created on: 22 Feb 2021
 *      Author: Patrick
 */
#include <DAVE.h>
#include <string.h>

#include <Header/GNSS.h>
#include <Header/ComUDP.h>


GNSS::GNSS()
{
	this->gnss_data = GNSSData();
	this->gnss_frame = GNSSFrame();
	this->raw_data = 0;
	this->frame_counter = 0;
}

u8 GNSS::init()
{
	return 0;
}

u8 GNSS::poll()
{
	u8 status = 0;
	u16 frame_length = 0;
	u16 checksum_rx = 0;

	status = UART_Receive(&RS232_UART1, &this->raw_data, 1);
	// Wait if uart channels are still busy
	if(status != UART_STATUS_SUCCESS)
	{
		return status;
	}

	switch (this->frame_counter)
	{
		// If its not in one of these switches reset it
		default:
			this->frame_counter = UBX_FRAME_HEADER_1;
			break;

		case UBX_FRAME_HEADER_1:
			if(this->raw_data == GNSS_GPS_SYNC_1)
			{
				this->frame_counter = UBX_FRAME_HEADER_2;
				break;
			} 
			this->frame_counter = UBX_FRAME_HEADER_1;
			break;

		case UBX_FRAME_HEADER_2:
			if(this->raw_data == GNSS_GPS_SYNC_2)
			{
				this->frame_counter = UBX_FRAME_CLASS;
			} else {
				this->frame_counter = UBX_FRAME_HEADER_1;
			}
			break;

		case UBX_FRAME_CLASS:
			gnss_frame = GNSSFrame();
			gnss_frame.setClassDef(this->raw_data);
			gnss_frame.updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_ID;
			break;

		case UBX_FRAME_ID:
			gnss_frame.setId(this->raw_data);
			gnss_frame.updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_DLC1;
			break;

		case UBX_FRAME_DLC1:
			gnss_frame.setLength(this->raw_data);
			gnss_frame.updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_DLC0;
			break;
		case UBX_FRAME_DLC0:
			frame_length = 	gnss_frame.getLength();
			frame_length |= this->raw_data << 8;

			gnss_frame.setLength(frame_length);
			gnss_frame.updateCheckSum(this->raw_data);
			this->frame_counter = UBX_FRAME_PAYLOAD;
			break;

		case UBX_FRAME_PAYLOAD:
			gnss_frame.payload[this->gps_payload_index++] = raw_data;
			gnss_frame.updateCheckSum(this->raw_data);
			if(gps_payload_index == gnss_frame.getLength()) //DLC reached
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
			gnss_frame.getChecksum();
			gnss_frame.setChecksumRx(this->raw_data);
			this->frame_counter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:
			checksum_rx = gnss_frame.getChecksumRx();
			checksum_rx |= this->raw_data << 8;
			gnss_frame.setChecksumRx(checksum_rx);

			if(checksum_rx != gnss_frame.getChecksumCalc())
			{
				this->frame_counter = UBX_FRAME_HEADER_1;
				break;
			}
			this->rx_ready = true;
			this->frame_counter = UBX_FRAME_HEADER_1;
			break;
	}
	return 0;
}

u8 GNSS::select(u8 chip)
{
	return -1;
}

u8 GNSS::write(u8 addr, u8 data)
{
	return -1;
}

char* GNSS::to_string()
{
	return '\0';
}

void GNSS::convert_payload()
{
	memcpy(&gnss_data.epoch,			&gnss_frame.payload[0],		4);
	memcpy(&gnss_data.fix,				&gnss_frame.payload[20],	1);
	memcpy(&gnss_data.num_sat,			&gnss_frame.payload[23],	1);
	memcpy(&gnss_data.lon,				&gnss_frame.payload[24],	4);
	memcpy(&gnss_data.lat,				&gnss_frame.payload[28],	4);
	memcpy(&gnss_data.height_ellipsoid,	&gnss_frame.payload[32],	4);
	memcpy(&gnss_data.height_msl,		&gnss_frame.payload[36],	4);
	memcpy(&gnss_data.hor_acc,			&gnss_frame.payload[40],	4);
	memcpy(&gnss_data.ver_acc,			&gnss_frame.payload[44],	4);
	memcpy(&gnss_data.speed,			&gnss_frame.payload[60],	4);
	memcpy(&gnss_data.heading,			&gnss_frame.payload[64],	4);
	memcpy(&gnss_data.speed_acc,		&gnss_frame.payload[68],	4);
	memcpy(&gnss_data.head_acc,			&gnss_frame.payload[72],	4);
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

u8 GNSS::rx_handler(GNSSData &data)
{
	if(this->rx_ready)
	{
		const u16 msg_type = (u16) (gnss_frame.getClassDef() << 8) | gnss_frame.getId();
		switch(msg_type)
		{
			default:
				break;
			case 0x0107:
				convert_payload();
				data = this->gnss_data;
				this->rx_ready = true;
				return GNSS_SUCCESS;
		}
		this->rx_ready = false;
	}
	return GNSS_NO_PAYLOAD;
}

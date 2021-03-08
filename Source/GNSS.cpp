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
	this->gps_frame = GNSSFrame();
	this->gps_data = 0;
	this->gps_frame_counter = 0;
}

u8 GNSS::init()
{
	return 0;
}

void GNSS::poll()
{
	u8 status = 0;

	status = UART_Receive(&RS232_UART1, &this->gps_data, 1);
	// Wait if uart channels are still busy
	if(status != UART_STATUS_SUCCESS)
	{
		return;
	}


	if(gps_receive_ready) //Received data has not been readout. So pass receveiving more stuff
	{
		return;
	}



	switch (gps_frame_counter)
	{
		default:
			gps_frame_counter = UBX_FRAME_SYNC1;
			break;

		case UBX_FRAME_SYNC1:

			if (gps_data == GPS_SYNC1)
				gps_frame_counter = UBX_FRAME_SYNC2;
			else
				gps_frame_counter = UBX_FRAME_SYNC1;

			break;

		case UBX_FRAME_SYNC2:

			if (gps_data == GPS_SYNC2)
				gps_frame_counter = UBX_FRAME_CLASS;
			else
				gps_frame_counter = UBX_FRAME_SYNC1;

			break;

		case UBX_FRAME_CLASS:

			gps_frame_reset();
			gps_frame.class_def = gps_data;
			update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_ID;

			break;

		case UBX_FRAME_ID:

			gps_frame.id = gps_data;
			update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_DLC1;
			break;

		case UBX_FRAME_DLC1:

			gps_frame.length = gps_data;
			update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_DLC0;
			break;

		case UBX_FRAME_DLC0:

			gps_frame.length |= gps_data << 8;
			update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_PAYLOAD;
			break;

		case UBX_FRAME_PAYLOAD:

			gps_frame.payload[gps_payload_index++] = gps_data;
			update_checksum(gps_data);

			if (gps_payload_index == gps_frame.length) //DLC reached
			{

				gps_frame_counter = UBX_FRAME_CK_A;
				break;
			}

			if (gps_payload_index == 92) //buffer overflow
			{

				gps_frame_counter = UBX_FRAME_SYNC1;
				break;
			}

			break;

		case UBX_FRAME_CK_A:

			gps_get_checksum();
			gps_frame.checksum_rx = gps_data;
			gps_frame_counter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:

			gps_frame.checksum_rx |= gps_data << 8;

			if (gps_frame.checksum_rx != gps_frame.checksum_calc)
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
				break;
			}

			gps_receive_ready = true;
			gps_frame_counter = UBX_FRAME_SYNC1;
			break;
	}
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
	memcpy(&gnss_data.epoch,			&gps_frame.payload[0],		4);
	memcpy(&gnss_data.fix,				&gps_frame.payload[20],	1);
	memcpy(&gnss_data.num_sat,			&gps_frame.payload[23],	1);
	memcpy(&gnss_data.lon,				&gps_frame.payload[24],	4);
	memcpy(&gnss_data.lat,				&gps_frame.payload[28],	4);
	memcpy(&gnss_data.height_ellipsoid,	&gps_frame.payload[32],	4);
	memcpy(&gnss_data.height_msl,		&gps_frame.payload[36],	4);
	memcpy(&gnss_data.hor_acc,			&gps_frame.payload[40],	4);
	memcpy(&gnss_data.ver_acc,			&gps_frame.payload[44],	4);
	memcpy(&gnss_data.speed,			&gps_frame.payload[60],	4);
	memcpy(&gnss_data.heading,			&gps_frame.payload[64],	4);
	memcpy(&gnss_data.speed_acc,		&gps_frame.payload[68],	4);
	memcpy(&gnss_data.head_acc,			&gps_frame.payload[72],	4);


}

void GNSS::validate(u8 _data, u8 _expected_data, u8 _fallback)
{
	if(_data == _expected_data)
	{
		this->gps_frame_counter = _expected_data;
	}else
	{
		this->gps_frame_counter = _fallback;
	}
}

u8 GNSS::rx_handler(GNSSData &data)
{
	if(gps_receive_ready)
	{
		const u16 msg_type = (u16) (gps_frame.class_def << 8) | gps_frame.id;
		switch(msg_type)
		{
			default:
				break;
			case 0x0107:
				convert_payload();
				data = this->gnss_data;
				gps_receive_ready = true;
				return GNSS_SUCCESS;
		}
		gps_receive_ready = false;
	}
	return GNSS_NO_PAYLOAD;
}

void GNSS::update_checksum(uint8_t data) {
	gps_frame.ck_a = gps_frame.ck_a + data;
	gps_frame.ck_b = gps_frame.ck_b + gps_frame.ck_a;
}

void GNSS::gps_get_checksum()
{
	gps_frame.checksum_calc = gps_frame.ck_a;
	gps_frame.checksum_calc |= gps_frame.ck_b << 8;
}

void GNSS::gps_frame_reset()
{
	gps_frame = GNSSFrame();
	gps_payload_index = 0;
}

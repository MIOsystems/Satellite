#include <DAVE.h>
#include <include/app/application.h>
#include <include/sensor/gps/gnss.h>
#include <include/util/types.h>
#include <string.h>

u32 rxPayloadBuff[100];
volatile u8 gnss_test_counter = 0;

void gnss_init()
{
	UbxFrame_t raw_data =
	{
		.class = 0,
		.id = 0,
		.length = 0,
		.checksum_rx = 0,
		.checksum_calc = 0,
		.ck_a = 0,
		.ck_b = 0,
		.payload = { 0 }
	};

	GPSValues_t converted_values = {
		.lon = 0,
		.lat = 0,
		.height_ellipsoid = 0,
		.height_msl = 0,
		.hor_acc = 0,
		.ver_acc = 0,
		.speed = 0,
		.heading = 0,
		.speed_acc = 0,
		.head_acc = 0,
		.epoch = 0,
		.fix = 0,
		.num_sat = 0,
	};

	gps_frame = raw_data;
	gps_packet = converted_values;
}

void gnss_poll()
{
	u8 status = 0;
	u8 gps_data = 0;
	status = UART_Receive(&RS232_UART1, &gps_data, 1);
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
			{
				rxPayloadBuff[gps_frame_counter ] = gps_data;
				gps_frame_counter = UBX_FRAME_SYNC2;
			}
			else
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
			}
			break;

		case UBX_FRAME_SYNC2:
			if (gps_data == GPS_SYNC2)
			{
				rxPayloadBuff[gps_frame_counter ] = gps_data;
				gps_frame_counter = UBX_FRAME_CLASS;
			}
			else
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
			}
			break;
		case UBX_FRAME_CLASS:
			gnss_frame_reset();
			rxPayloadBuff[gps_frame_counter ] = gps_data;
			gps_frame.class = gps_data;
			gnss_update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_ID;
			break;

		case UBX_FRAME_ID:
			gps_frame.id = gps_data;
			rxPayloadBuff[gps_frame_counter ] = gps_data;
			gnss_update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_DLC1;
			break;

		case UBX_FRAME_DLC1:
			gps_frame.length = gps_data;
			rxPayloadBuff[gps_frame_counter ] = gps_data;
			gnss_update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_DLC0;
			break;

		case UBX_FRAME_DLC0:
			gps_frame.length |= gps_data << 8;
			rxPayloadBuff[gps_frame_counter ] = gps_data;
			gnss_update_checksum(gps_data);
			gps_frame_counter = UBX_FRAME_PAYLOAD;
			break;

		case UBX_FRAME_PAYLOAD:
			gps_frame.payload[gps_payload_index++] = gps_data;
			rxPayloadBuff[gps_frame_counter + gps_payload_index] = gps_data;
			gnss_update_checksum(gps_data);

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
			gnss_get_checksum();
			gps_frame.checksum_rx = gps_data;
			rxPayloadBuff[gps_frame_counter + (gps_payload_index -1)] = gps_data;
			gps_frame_counter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:
			gps_frame.checksum_rx |= gps_data << 8;
			rxPayloadBuff[gps_frame_counter + (gps_payload_index -1)] = gps_data;
			u16 rx = gps_frame.checksum_rx;
			u16 calc = gps_frame.checksum_calc;
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

void gnss_convert(void)
{
	memcpy(&gps_packet.epoch,				&gps_frame.payload[0],	4);
	memcpy(&gps_packet.fix,					&gps_frame.payload[20],	1);
	memcpy(&gps_packet.num_sat,				&gps_frame.payload[23],	1);
	memcpy(&gps_packet.lon,					&gps_frame.payload[24],	4);
	memcpy(&gps_packet.lat,					&gps_frame.payload[28],	4);
	memcpy(&gps_packet.height_ellipsoid,	&gps_frame.payload[32],	4);
	memcpy(&gps_packet.height_msl,			&gps_frame.payload[36],	4);
	memcpy(&gps_packet.hor_acc,				&gps_frame.payload[40],	4);
	memcpy(&gps_packet.ver_acc,				&gps_frame.payload[44],	4);
	memcpy(&gps_packet.speed,				&gps_frame.payload[60],	4);
	memcpy(&gps_packet.heading,				&gps_frame.payload[64],	4);
	memcpy(&gps_packet.speed_acc,			&gps_frame.payload[68],	4);
	memcpy(&gps_packet.head_acc,			&gps_frame.payload[72],	4);
}

u8 gps_rx_handler(void)
{
	if (gps_receive_ready)
	{
		uint16_t message_type = (uint16_t)(gps_frame.class << 8) | gps_frame.id;

		if(message_type == 0x0107)
        {
            gnss_convert();
            gps_frame_reset();
            gps_receive_ready = false;
            return 0;
        }
	}
	return 1;
}

void gnss_frame_reset(void)
{
	gps_payload_index = 0;
	gnss_init();
}

void gnss_update_checksum(u8 data)
{
	gps_frame.ck_a += (u8) data;
	gps_frame.ck_b += (u8) gps_frame.ck_a;
}

void gnss_get_checksum(void)
{
	gps_frame.checksum_calc = gps_frame.ck_a;
	gps_frame.checksum_calc |= gps_frame.ck_b << 8;
}

void gps_frame_reset()
{
	UbxFrame_t raw_data =
	{
		.class = 0,
		.id = 0,
		.length = 0,
		.checksum_rx = 0,
		.checksum_calc = 0,
		.ck_a = 0,
		.ck_b = 0,
		.payload = { 0 }
	};
	gps_frame = raw_data;
}

#include <DAVE.h>
#include <include/app/composer.h>
#include <include/sensor/gps/gnss.h>
#include <include/util/types.h>


void gnss_init()
{
	ubx_frame_t raw_data =
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

	gps_values_t converted_values = {
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

	gps_raw = raw_data;
	gps_packet = converted_values;
}

void gnss_poll()
{
	u8 status = 0;
	u8 gps_data = 0;
	status = UART_Receive(&RS232_UART1, &gps_data, 1);
	if(status != UART_STATUS_SUCCESS)
	{
		return;
	}

	if(gps_ready)
	{
		return;
	}

	switch(gps_frame_counter)
	{
		default:
			gps_frame_counter = UBX_FRAME_SYNC1;
			break;
		case UBX_FRAME_SYNC1:
			if(gps_data == GPS_SYNC1)
			{
				gps_frame_counter = UBX_FRAME_SYNC2;
			}
			else
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
			}
			break;
		case UBX_FRAME_SYNC2:
			if(gps_data == GPS_SYNC2)
			{
				gps_frame_counter = UBX_FRAME_CLASS;
			}
			else
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
			}
			break;
		case UBX_FRAME_CLASS:
			gnss_frame_reset();
			gps_raw.class = gps_data;
			gnss_update_checksum(&gps_data);
			gps_frame_counter = UBX_FRAME_ID;
			break;
		case UBX_FRAME_ID:
			gps_raw.id = gps_data;
			gnss_update_checksum(&gps_data);
			gps_frame_counter = UBX_FRAME_DLC1;
			break;
		case UBX_FRAME_DLC1:
			gps_raw.length = gps_data;
			gnss_update_checksum(&gps_data);
			gps_frame_counter = UBX_FRAME_DLC0;
			break;

		case UBX_FRAME_DLC0:
			gps_raw.length |= gps_data << 8;
			gnss_update_checksum(&gps_data);
			gps_frame_counter = UBX_FRAME_PAYLOAD;
			break;
		case UBX_FRAME_PAYLOAD:
			gps_raw.payload[gps_payload_index++] = gps_data;
			gnss_update_checksum(&gps_data);

			if (gps_payload_index == gps_raw.length)
			{

				gps_frame_counter = UBX_FRAME_CK_A;
				break;
			}
			if (gps_payload_index == PAYLOAD_LENGTH) //buffer overflow
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
				break;
			}
			break;
		case UBX_FRAME_CK_A:
			gnss_get_checksum();
			gps_raw.checksum_rx = gps_data;
			gps_frame_counter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:
			gps_raw.checksum_rx |= gps_data << 8;

			if (gps_raw.checksum_rx != gps_raw.checksum_calc)
			{
				gps_frame_counter = UBX_FRAME_SYNC1;
				break;
			}
			gps_ready = true;
			gps_frame_counter = UBX_FRAME_SYNC1;
			break;
	}
}

void gnss_convert(void)
{

	memcpy(&gps_packet.epoch, 			&gps_raw.payload[0],  4);
	memcpy(&gps_packet.fix,		 		&gps_raw.payload[20], 1);
	memcpy(&gps_packet.num_sat,	 		&gps_raw.payload[23], 1);
	memcpy(&gps_packet.lon, 			&gps_raw.payload[24], 4);
	memcpy(&gps_packet.lat, 			&gps_raw.payload[28], 4);
	memcpy(&gps_packet.height_ellipsoid,&gps_raw.payload[32], 4);
	memcpy(&gps_packet.height_msl, 		&gps_raw.payload[36], 4);
	memcpy(&gps_packet.hor_acc, 		&gps_raw.payload[40], 4);
	memcpy(&gps_packet.ver_acc, 		&gps_raw.payload[44], 4);
	memcpy(&gps_packet.speed, 			&gps_raw.payload[60], 4);
	memcpy(&gps_packet.heading, 		&gps_raw.payload[64], 4);
	memcpy(&gps_packet.speed_acc, 		&gps_raw.payload[68], 4);
	memcpy(&gps_packet.head_acc, 		&gps_raw.payload[72], 4);
	gps_ready = false;
}

u8 gps_rx_handler(void)
{
	if (gps_ready)
	{
		uint16_t message_type = (uint16_t)(gps_raw.class << 8) | gps_raw.id;

		switch (message_type)
		{
		default:
			break;
		case 0x0107:
			gnss_convert();

			return 0;
			break;
		}


	}
	return 1;
}


void gnss_frame_reset(void)
{
	gps_payload_index = 0;
	gnss_init();
}

void gnss_update_checksum(u8 *data)
{
	gps_raw.ck_a = gps_raw.ck_a + *data;
	gps_raw.ck_b = gps_raw.ck_b + gps_raw.ck_a;
}

void gnss_get_checksum(void)
{
	gps_raw.checksum_calc = gps_raw.ck_a;
	gps_raw.checksum_calc |= gps_raw.ck_b << 8;
}

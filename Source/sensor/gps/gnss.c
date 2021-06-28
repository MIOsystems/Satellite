#include <DAVE.h>
#include <include/app/application.h>
#include <include/sensor/gps/gnss.h>
#include <include/util/types.h>
#include <string.h>

u32 rxPayloadBuff[100];
volatile u8 gnss_test_counter = 0;

void gnssInit()
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

	gpsFrame = raw_data;
	gpsPacket = converted_values;
}

void gnssPoll()
{
	u8 status = 0;
	u8 gps_data = 0;
	status = UART_Receive(&RS232_UART1, &gps_data, 1);
	// Wait if uart channels are still busy
	if(status != UART_STATUS_SUCCESS)
	{
		return;
	}


	if(gpsReceive_ready) //Received data has not been readout. So pass receveiving more stuff
	{
		return;
	}



	switch (gpsFrameCounter)
	{
		default:
			gpsFrameCounter = UBX_FRAME_SYNC1;
			break;

		case UBX_FRAME_SYNC1:

			if (gps_data == GPS_SYNC1)
			{
				rxPayloadBuff[gpsFrameCounter ] = gps_data;
				gpsFrameCounter = UBX_FRAME_SYNC2;
			}
			else
			{
				gpsFrameCounter = UBX_FRAME_SYNC1;
			}
			break;

		case UBX_FRAME_SYNC2:
			if (gps_data == GPS_SYNC2)
			{
				rxPayloadBuff[gpsFrameCounter ] = gps_data;
				gpsFrameCounter = UBX_FRAME_CLASS;
			}
			else
			{
				gpsFrameCounter = UBX_FRAME_SYNC1;
			}
			break;
		case UBX_FRAME_CLASS:
			gnssFrameReset();
			rxPayloadBuff[gpsFrameCounter ] = gps_data;
			gpsFrame.class = gps_data;
			gnssUpdateChecksum(gps_data);
			gpsFrameCounter = UBX_FRAME_ID;
			break;

		case UBX_FRAME_ID:
			gpsFrame.id = gps_data;
			rxPayloadBuff[gpsFrameCounter ] = gps_data;
			gnssUpdateChecksum(gps_data);
			gpsFrameCounter = UBX_FRAME_DLC1;
			break;

		case UBX_FRAME_DLC1:
			gpsFrame.length = gps_data;
			rxPayloadBuff[gpsFrameCounter ] = gps_data;
			gnssUpdateChecksum(gps_data);
			gpsFrameCounter = UBX_FRAME_DLC0;
			break;

		case UBX_FRAME_DLC0:
			gpsFrame.length |= gps_data << 8;
			rxPayloadBuff[gpsFrameCounter ] = gps_data;
			gnssUpdateChecksum(gps_data);
			gpsFrameCounter = UBX_FRAME_PAYLOAD;
			break;

		case UBX_FRAME_PAYLOAD:
			gpsFrame.payload[gpsPayloadIndex++] = gps_data;
			rxPayloadBuff[gpsFrameCounter + gpsPayloadIndex] = gps_data;
			gnssUpdateChecksum(gps_data);

			if (gpsPayloadIndex == gpsFrame.length) //DLC reached
			{

				gpsFrameCounter = UBX_FRAME_CK_A;
				break;
			}

			if (gpsPayloadIndex == 92) //buffer overflow
			{

				gpsFrameCounter = UBX_FRAME_SYNC1;
				break;
			}
			break;

		case UBX_FRAME_CK_A:
			gnssGetChecksum();
			gpsFrame.checksum_rx = gps_data;
			rxPayloadBuff[gpsFrameCounter + (gpsPayloadIndex -1)] = gps_data;
			gpsFrameCounter = UBX_FRAME_CK_B;
			break;

		case UBX_FRAME_CK_B:
			gpsFrame.checksum_rx |= gps_data << 8;
			rxPayloadBuff[gpsFrameCounter + (gpsPayloadIndex -1)] = gps_data;
//			if (gpsFrame.checksum_rx != gpsFrame.checksum_calc)
//			{
//				gpsFrameCounter = UBX_FRAME_SYNC1;
//				break;
//			}

			gpsReceive_ready = true;
			gpsFrameCounter = UBX_FRAME_SYNC1;
			break;
	}
}

void gnssConvert(void)
{
	memcpy(&gpsPacket.epoch,				&gpsFrame.payload[0],	4);
	memcpy(&gpsPacket.fix,					&gpsFrame.payload[20],	1);
	memcpy(&gpsPacket.num_sat,				&gpsFrame.payload[23],	1);
	memcpy(&gpsPacket.lon,					&gpsFrame.payload[24],	4);
	memcpy(&gpsPacket.lat,					&gpsFrame.payload[28],	4);
	memcpy(&gpsPacket.height_ellipsoid,	&gpsFrame.payload[32],	4);
	memcpy(&gpsPacket.height_msl,			&gpsFrame.payload[36],	4);
	memcpy(&gpsPacket.hor_acc,				&gpsFrame.payload[40],	4);
	memcpy(&gpsPacket.ver_acc,				&gpsFrame.payload[44],	4);
	memcpy(&gpsPacket.speed,				&gpsFrame.payload[60],	4);
	memcpy(&gpsPacket.heading,				&gpsFrame.payload[64],	4);
	memcpy(&gpsPacket.speed_acc,			&gpsFrame.payload[68],	4);
	memcpy(&gpsPacket.head_acc,			&gpsFrame.payload[72],	4);
}

u8 gpsRecvHandler(void)
{
	if (gpsReceive_ready)
	{
		DIGITAL_IO_SetOutputLow(&LED_GREEN);
		uint16_t message_type = (uint16_t)(gpsFrame.class << 8) | gpsFrame.id;

		if(message_type == 0x0107)
        {
            gnssConvert();
            gnssFrameReset();
            gpsReceive_ready = false;
            return 0;
        }
		DIGITAL_IO_SetOutputHigh(&LED_GREEN);
	}
	return 1;
}

void gnssFrameReset(void)
{
	gpsPayloadIndex = 0;
	gnssInit();
}

void gnssUpdateChecksum(u8 data)
{
	gpsFrame.ck_a = (u8) (gpsFrame.ck_a + data);
	gpsFrame.ck_b += (u8) (gpsFrame.ck_b + gpsFrame.ck_a);
}

void gnssGetChecksum(void)
{
	gpsFrame.checksum_calc = gpsFrame.ck_a;
	gpsFrame.checksum_calc |= gpsFrame.ck_b << 8;
}

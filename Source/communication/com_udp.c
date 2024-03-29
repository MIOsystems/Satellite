#include <include/communication/com_udp.h>
#include <include/util/delay.h>
#include <stdlib.h>

i8 udp_initialize()
{
	//netif_set_link_up(netif_default);
	//netif_set_up(ETH_LWIP_0.xnetif);
	IP_ADDR4(&addr, COM_UDP_IP_1, COM_UDP_IP_2, COM_UDP_IP_3, COM_UDP_IP_4);
	com_ctrl = udp_new();

	err_t status = udp_bind(com_ctrl, IP_ADDR_ANY, COM_UDP_PORT_OUT);
	if(status != ERR_OK)
	{
		return status;
	}
	sys_check_timeouts();
	return status;
}

#ifdef UBLX
/**
 * --------------------------------------------------------------
 * |						GNSS UDP PACKET 					|
 * --------------------------------------------------------------
 * |	char	| prefix[6]			|	6 bytes	|	0	|	6	|
 * |			| STRUCT PADDING	| 	2 bytes	|	6	| 	8	|
 * |	i32  	| lon				|	8 bytes	|	8	|	12	|
 * |	i32  	| lat				|	8 bytes	|	12	|	16	|
 * |	i32  	| height_ellipsoid	|	8 bytes	|	16	|	20	|
 * |	i32  	| height_msl		|	8 bytes	|	20	|	24	|
 * |	i32  	| hor_acc			|	8 bytes	|	24	|	28	|
 * |	i32  	| ver_acc			|	8 bytes	|	28	|	32	|
 * |	i32  	| speed				|	8 bytes	|	32	|	36	|
 * |	i32  	| heading			|	8 bytes	|	36	|	40	|
 * |	i32  	| speed_acc			|	8 bytes	|	40	|	44	|
 * |	i32  	| head_acc			|	8 bytes	|	44	|	48	|
 * |	u32  	| epoch				|	8 bytes	|	48	|	52	|
 * |	u8  	| fix				|	1 bytes	|	52	|	53 	|
 * |	u8  	| num_sat			|	1 bytes	|	53	|	54	|
 * |			| STRUCT PADDING	|	6 bytes	| 	54	| 	56	|
 * --------------------------------------------------------------
 */
i8 udp_send_gps(GPSValues_t data)
{
	i8 status = ERR_OK;
	GnssPacket_t packet = {
		.prefix = "gnss,",
		.lon = data.lon,
		.lat = data.lat,
		.height_ellipsoid = data.height_ellipsoid,
		.height_msl = data.height_msl,
		.hor_acc = data.hor_acc,
		.ver_acc = data.ver_acc,
		.speed = data.speed,
		.heading = data.heading,
		.speed_acc = data.speed_acc,
		.head_acc = data.head_acc,
		.epoch = data.epoch,
		.fix = data.fix,
		.num_sat = data.num_sat,
	};
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}
#endif

#ifdef BMI085
/**
 * --------------------------------------------------------------
 * |					IMU UDP PACKET 							|
 * --------------------------------------------------------------
 * |  char		| prefix			|	5 bytes	|	0	|	5	|
 * |			| STRUCT PADDING	| 	3 bytes	|	5	| 	8	|
 * |  f32		| avg_x				|	4 bytes	|	8	|	12	|
 * |  f32		| max_x				|	4 bytes	|	12	|	16	|
 * |  f32		| min_x				|	4 bytes	|	16	|	20	|
 * |  f32		| avg_y				|	4 bytes	|	20	|	24	|
 * |  f32		| max_y				|	4 bytes	|	24	|	28	|
 * |  f32		| min_y				|	4 bytes	|	28	|	32	|
 * |  f32		| avg_z				|	4 bytes	|	32	|	36	|
 * |  f32		| max_z				|	4 bytes	|	36	|	40	|
 * |  f32		| min_z				|	4 bytes	|	40	|	44	|
 * |  f32		| angle_x			|	4 bytes	|	44	|	48	|
 * |  f32		| angle_y			|	4 bytes	|	48	|	52	|
 * |  f32		| angle_z			|	4 bytes	|	52	|	56	|
 * --------------------------------------------------------------
 */
i8 udp_send_bmi(bmi085x data)
{
	i8 status = ERR_OK;
	InertialMeasurementUnitPacket_t packet = {
	        .prefix = "imu,",
	        .avg_x = data.data.x_stat.avg,
	        .max_x = data.data.x_stat.max,
	        .min_x = data.data.x_stat.min,
	        .avg_y = data.data.y_stat.avg,
	        .max_y = data.data.y_stat.max,
	        .min_y = data.data.y_stat.min,
	        .avg_z = data.data.z_stat.avg,
	        .max_z = data.data.z_stat.max,
	        .min_z = data.data.z_stat.min,
	        .angle_x = data.data.angle.x,
	        .angle_y = data.data.angle.y,
	        .angle_z = data.data.angle.z,
	};
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}


i8 udp_send_debug_bmi(bmi085x data)
{
	i8 status = ERR_OK;
	IMUDebugPacket_t packet = {
			.Ax = data.data.accel_poll_val.x,
			.Ay = data.data.accel_poll_val.y,
			.Az = data.data.accel_poll_val.z,
			.Gx = data.data.gyro_poll_val.x,
			.Gy = data.data.gyro_poll_val.y,
			.Gz = data.data.gyro_poll_val.z,
			.angleX = data.data.angle.x,
			.angleY = data.data.angle.y,
			.angleZ = data.data.angle.z,
	};
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}
#endif

i8 udp_send_proximity(proximity_switch_t data)
{
	i8 status = ERR_OK;
	ProximityPacket_t packet = {
			.prefix = "prox,",
			.data = data,
	};
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}

i8 udp_send_packet(void* data, size_t size, char* prefix)
{
	i8 status = ERR_OK;
	UDPPacket_t packet;
	strcpy(packet.prefix, prefix);
	memcpy(&packet.data , data, size);

	const u16 tx_buff = size + 8;
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, tx_buff, PBUF_RAM);
	buffer->payload = &packet;
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);

	status = (i8) pbuf_free(buffer);
	return status;
}

i8 udp_send_altimeter(AltimeterData_t data)
{
	i8 status = ERR_OK;
	AltimeterPacket_t packet = {
			.prefix = "alti,",
			.distance = data.altimeterAvg,
			.sum = data.altimeterSum,
			.counter = data.recvCounter,
	};
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}

//i8 udp_send_spectrum(cplxf *data, char* specifier)
i8 udp_send_spectrum(kiss_fft_cpx *data, char* specifier)
{
	i8 status = ERR_OK;
	FFTPacket_t packet = { .prefix = { 0 }, .data = { 0 }};

	for(u16 i = 0; i < FFT_N; i++)
	{
		packet.data[i] = data[i].r;
	}
	strcpy(packet.prefix, "FFT");
	strcat(packet.prefix, specifier);
	u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;
	// Sending the packet
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	u8 counter = 0;
	while(status != ERR_OK && counter >= 10)
	{
		status = (i8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
		DIGITAL_IO_SetOutputHigh(&LED_YELLOW);
		counter++;
	}
	if(counter >= 10)
	{
		DIGITAL_IO_SetOutputLow(&LED_YELLOW);
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		delayMs(50);
		DIGITAL_IO_SetOutputLow(&LED_RED);
	}
	DIGITAL_IO_SetOutputLow(&LED_BLUE);
	// Freeing the packet
	status = (i8) pbuf_free(buffer);
	return status;
}

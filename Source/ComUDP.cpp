/*
 * ComUDP.cpp
 *
 *  Created on: 19 Feb 2021
 *      Author: Patrick
 */

#include <DAVE.h>
#include <stdio.h>

#include <Header/ComUDP.h>
#include <Header/Satellite.h>
#include <Header/GNSS.h>

ComUDP::ComUDP()
{

}

i8 ComUDP::init()
{
	netif_set_link_up(netif_default);
	netif_set_up(ETH_LWIP_0.xnetif);
	IP_ADDR4(&addr, COM_UDP_IP_1, COM_UDP_IP_2, COM_UDP_IP_3, COM_UDP_IP_4);
	this->com_ctrl = udp_new();

	err_t status = udp_bind(this->com_ctrl, IP_ADDR_ANY, COM_UDP_PORT_OUT);
	if(status != ERR_OK)
	{
		return status;
	}
	sys_check_timeouts();
	return COM_SUCCESS;
}

i8 ComUDP::send_gnss(GNSSData data) {
	err_t status = ERR_OK;
	gnss_packet packet =
	{
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
	// Create packet to send
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	memcpy(buffer->payload, &packet, size);
	// Sending the packet
	status = udp_sendto(this->com_ctrl, buffer, &this->addr, COM_UDP_PORT_OUT);
	// Freeing the packet
	status = pbuf_free(buffer);
	return status;
}

i8 ComUDP::send_ok()
{
	err_t status = ERR_OK;
	sys_check_timeouts();
	unsigned char data[3] = "OK";
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof(data), PBUF_RAM);
	memcpy(buffer->payload, &data, sizeof(data));
	status = udp_sendto(this->com_ctrl, buffer, &this->addr, COM_UDP_PORT_OUT);
	if(status != ERR_OK){
		pbuf_free(buffer);
		return status;
	}
	// Freeing the packet
	status = pbuf_free(buffer);
	return status;

}

i8 ComUDP::send_bmi(BMI085 data)
{
	err_t status = ERR_OK;

	bmi_packet packet = {
        .prefix = "imu,",
        .avg_x = data.packet.acc_x_stat.avg + 10,
        .max_x = data.packet.acc_x_stat.max,
        .min_x = data.packet.acc_x_stat.min,
        .avg_y = data.packet.acc_y_stat.avg,
        .max_y = data.packet.acc_y_stat.max,
        .min_y = data.packet.acc_y_stat.min,
        .avg_z = data.packet.acc_z_stat.avg,
        .max_z = data.packet.acc_z_stat.max,
        .min_z = data.packet.acc_z_stat.min,
        .angle_x = data.packet.angle[0],
        .angle_y = data.packet.angle[1],
        .angle_z = data.packet.angle[2],
    };

	u16 size = sizeof(packet);
	// Create packet to send
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	memcpy(buffer->payload, &packet, size);
	// Sending the packet
	status = udp_sendto(this->com_ctrl, buffer, &this->addr, COM_UDP_PORT_OUT);
	if(status != ERR_OK){
		pbuf_free(buffer);
		return status;
	}
	// Freeing the packet
	status = pbuf_free(buffer);
	free(packet.prefix);
	return status;
}

i8 ComUDP::close()
{
	udp_remove(this->com_ctrl);
	return COM_SUCCESS;
}

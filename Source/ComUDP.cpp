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
	i8 status = 0;
	u16 size = sizeof(data);
	// Create packet to send
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	memcpy(buffer->payload, &data, size);
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

	// Freeing the packet
	status = pbuf_free(buffer);
	return status;

}

i8 ComUDP::close()
{
	udp_remove(this->com_ctrl);
	return COM_SUCCESS;
}

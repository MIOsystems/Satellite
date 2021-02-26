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

i8 ComUDP::send_gnss(GNSSData gnss) {
	i8 status = 0;
	const char* gnss_str = gnss.to_string();
	u16 size = (u16) strlen(gnss_str);
	// Create packet to send
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	memcpy(buffer->payload, gnss_str, size);
	// Sending the packet
	status = udp_sendto(this->com_ctrl, buffer, &this->addr, COM_UDP_PORT_OUT);

	// Freeing the packet
	status = pbuf_free(buffer);
	free( (char*) gnss_str);
	return status;
}

i8 ComUDP::send(const char *data)
{
	i8 status = 0;
	// Create packet to send
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof(data), PBUF_RAM);
	memcpy(buffer->payload, &data, sizeof(data));
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

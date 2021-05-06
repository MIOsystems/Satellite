/*
 * validate_ethernet.c
 *
 *  Created on: 20 Apr 2021
 *      Author: Patrick
 */

#include <stdlib.h>

#include <include/validation/validate_ethernet.h>
#include <include/satellite.h>



u8 validate_ethernet_init()
{
	netif_set_link_up(netif_default);
	netif_set_up(ETH_LWIP_0.xnetif);
	IP_ADDR4(&addr, COM_UDP_IP_1, COM_UDP_IP_2, COM_UDP_IP_3, COM_UDP_IP_4);
	com_ctrl = udp_new();

	u8 status = (u8) udp_bind(com_ctrl, IP_ADDR_ANY, COM_UDP_PORT_OUT);
	if(status != ERR_OK)
	{
		return status;
	}
	sys_check_timeouts();
	return status;
}

u8 validate_ethernet_update(validate_packet_t packet)
{
	u8 status = ERR_OK;
	const u16 size = sizeof(packet);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &packet;

	status = (u8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	status = pbuf_free(buffer);
	return status;
}

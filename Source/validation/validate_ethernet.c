/*
 * validate_ethernet.c
 *
 *  Created on: 20 Apr 2021
 *      Author: Patrick
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include <include/validation/validate_ethernet.h>
#include <include/satellite.h>

struct packet
{
	u32 dip_1;
	u32 dip_2;
	u32 dip_3;
	u32 dip_4;
	bool d_out_1;
	bool d_out_2;
	bool d_out_3;
	bool d_out_4;
	u16 a_in_1;
	u16 a_in_2;
	u16 a_in_3;
	bool relay;
};


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

u8 validate_ethernet_update(validate_packet_t val_packet)
{
	u8 status = ERR_OK;

	char message[32] = { 0 };

	int a1 = val_packet.ain.a_in_1;
	int a2 = val_packet.ain.a_in_2;
	int a3 = val_packet.ain.a_in_3;

	sprintf(message, "%i,%i,%i,%i,"
			"%i,%i,%i,%i,"
			"%i,%i,%i,"
			"%i",

			val_packet.dip.dip_1, val_packet.dip.dip_2, val_packet.dip.dip_3, val_packet.dip.dip_4,
			val_packet.dout.d_out_1, val_packet.dout.d_out_2, val_packet.dout.d_out_3, val_packet.dout.d_out_4,
			a1,
			a2,
			a3,
			val_packet.relay);

//	struct packet pack = {
//			.dip_1 = val_packet.dip.dip_1,
//			.dip_2 = val_packet.dip.dip_2,
//			.dip_3 = val_packet.dip.dip_3,
//			.dip_4 = val_packet.dip.dip_4,
//			.d_out_1 = val_packet.dout.d_out_1,
//			.d_out_2 = val_packet.dout.d_out_2,
//			.d_out_3 = val_packet.dout.d_out_3,
//			.d_out_4 = val_packet.dout.d_out_4,
//			.a_in_1 = val_packet.ain.a_in_1,
//			.a_in_2 = val_packet.ain.a_in_2,
//			.a_in_3 = val_packet.ain.a_in_3,
//			.relay = val_packet.relay,
//	};
	const u16 size = sizeof(message);
	struct pbuf* buffer = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
	buffer->payload = &message;
	status = (u8) udp_sendto(com_ctrl, buffer, &addr, COM_UDP_PORT_OUT);
	status = pbuf_free(buffer);
	return status;
}

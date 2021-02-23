/*
 * ComUDP.h
 *
 *  Created on: 19 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_COMUDP_H_
#define HEADER_COMUDP_H_

#include <DAVE.h>

#include <Header/Types.h>
#include <Header/Sensor.h>
#include <Header/GNSS.h>

class ComUDP
{
	private:
		ip_addr_t addr;
		struct udp_pcb *com_ctrl;
		typedef enum {
			COM_SUCCESS = 0,
			COM_NULL_PTR
		} COM_STATUS;
	public:
		ComUDP();
		i8 init();
		i8 send(const char* data);
		i8 send_ok();
		i8 send_gnss(GNSSData &gnss);
		i8 close();
};

#endif /* HEADER_COMUDP_H_ */

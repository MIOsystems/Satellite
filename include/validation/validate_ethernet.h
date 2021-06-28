/*
 * validate_ethernet.h
 *
 *  Created on: 20 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_ETHERNET_H_
#define VALIDATE_ETHERNET_H_

#include <DAVE.h>
#include <include/util/types.h>
#include <include/validation/validate_model.h>


ip_addr_t addr;
struct udp_pcb *com_ctrl;


u8 validate_ethernet_init();
u8 validate_ethernet_update(validate_packet_t val_packet);

#endif /* VALIDATE_ETHERNET_H_ */

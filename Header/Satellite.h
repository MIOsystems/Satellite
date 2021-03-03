/*
 * Satellite.h
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_SATELLITE_H_
#define HEADER_SATELLITE_H_

#include <DAVE.h>
#include <Header/Types.h>

#define CLOCK_SPEED		144000000

// COMMUNICATIOn
#define COM_UDP_PORT_IN		(u16)	52256
#define COM_UDP_PORT_OUT	(u16)	64087
#define COM_UDP_IP_1		(u8)	192
#define COM_UDP_IP_2		(u8)	168
#define COM_UDP_IP_3		(u8)	0
#define COM_UDP_IP_4		(u8)	11


//GNSS
#define GNSS_GPS_BUFF_S		(u8)	92
#define GNSS_GPS_SYNC_1		(u8)	0xB5
#define GNSS_GPS_SYNC_2		(u8)	0x62


//BMI085
#define BMI_CS_A_GPIO				XMC_GPIO_PORT3 // 3.14	- 134
#define BMI_CS_G_GPIO				XMC_GPIO_PORT4 // 4.3	- 121
#define BMI_CS_A_PIN		(u8)	134
#define BMI_CS_G_PIN		(u8)	121
#define BMI_A_DATA_ADDR		(u8)	0x12
#define BMI_G_DATA_ADDR		(u8)	0x02

//OPCODES
#define BMI_A_RESET_ADDR	(u8)	0x7E
#define BMI_A_RESET_DATA	(u8)	0xB6
#define BMI_A_PWR_CTRL_ADDR (u8)	0x7D
#define BMI_A_PWR_OFF		(u8)	0x00
#define BMI_A_PWR_ON		(u8)	0x04
#define BMI_A_RANGE_ADDR	(u8)	0x41
#define BMI_A_RANGE_2G		(u8)	0x00

#define BMI_G_RESET_ADDR		(u8)	0x14
#define BMI_G_RESET_DATA		(u8)	0xB6
#define BMI_G_BANDWIDTH_ADDR	(u8)	0x10
#define BMI_G_BANDWIDTH_DATA	(u8)	0x02
#define BMI_G_RANGE_ADDR		(u8)	0x0F
#define BMI_G_RANGE_DATA		(u8)	0x04
#define BMI_BUFFER_SIZE 		(u8)	6

#endif /* HEADER_SATELLITE_H_ */

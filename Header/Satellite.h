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

//BMI085
#define BMI_CS_A_GPIO			XMC_GPIO_PORT3 // 3.14	- 134
#define BMI_CS_G_GPIO			XMC_GPIO_PORT4 // 4.3	- 121
#define BMI_CS_A_PIN	(u8)	134
#define BMI_CS_G_PIN	(u8)	121
#define BMI_XMC_MODE 			XMC_GPIO_MODE_OUTPUT_PUSH_PULL

//GNSS
#define GNSS_GPS_BUFF_S	(u8)	92
#define GNSS_GPS_SYNC_1	(u8)	0xB5
#define GNSS_GPS_SYNC_2	(u8)	0x62

//OPCODES
#define BMI_G_RST_ADDR	(u8) 	0x14
#define BMI_G_RST_DATA	(u8)	0xB6
#define BMI_G_BANW_ADDR	(u8)	0x10 // GYRO BANDWIDTH
#define BMI_G_BANW_DATA	(u8)	0x02
#define BMI_G_RANG_ADDR	(u8)	0x0F // GYRO RANGE
#define BMI_G_RANG_DATA	(u8)	0x04

#define BMI_A_RST_ADDR	(u8)	0x7E
#define BMI_A_RST_DATA	(u8)	0xB6
#define BMI_A_PWR_ADDR	(u8)	0x7C
#define BMI_A_PWR_DATA	(u8)	0x00
#define BMI_A_RANG_ADDR	(u8)	0x41
#define BMI_A_RANG_DATA	(u8)	0x00 // 2G

#define BMI_G_DATA_ADDR	(u8)	0x02
#define BMI_G_BUFF_S			6

#define BMI_A_DATA_ADDR	(u8)	0x12
#define BMI_A_BUFF_S	(u8)	6

#endif /* HEADER_SATELLITE_H_ */

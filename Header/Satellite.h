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

#define M_PI 				(f32)	3.14159265359
#define GYRO_SENSITIVITY	(f32)	262.144
#define ACCEL_SENSITIVITY	(f32)	32768


#define CLOCK_SPEED					144000000

// COMMUNICATION
#define COM_UDP_PORT_IN		(u16)	52256
#define COM_UDP_PORT_OUT	(u16)	62510
#define COM_UDP_IP_1		(u8)	192
#define COM_UDP_IP_2		(u8)	168
#define COM_UDP_IP_3		(u8)	0
#define COM_UDP_IP_4		(u8)	11


//GNSS
#define GNSS_GPS_BUFF_S		(u8)	92
#define GNSS_GPS_SYNC_1		(u8)	0xB5
#define GNSS_GPS_SYNC_2		(u8)	0x62


#define BMI085_G_RST_ADDR 	(u8)	0x14
#define BMI085_G_RST_DATA	(u8) 	0xB6
#define BMI085_G_BW_ADDR	(u8)	0x10
#define BMI085_G_BW_DATA	(u8)	0x02
#define BMI085_G_RANGE_ADDR	(u8)	0x0F
#define BMI085_G_RANGE_DATA	(u8)	0x04

#define BMI085_A_RST_ADDR 		(u8)	0x7E
#define BMI085_A_RST_DATA		(u8)	0xB6
#define BMI085_A_DUMMY_ADDR		(u8)	0xFF
#define BMI085_A_DUMMY_DATA		(u8)	0xFF
#define BMI085_A_PWR_CTRL_ADDR	(u8)	0x7D
#define BMI085_A_PWR_CTRL_DATA	(u8)	0x04
#define BMI085_A_PWR_CONF_ADDR	(u8)	0x7C
#define BMI085_A_PWR_CONF_DATA	(u8)	0x00
#define BMI085_A_RANGE_ADDR		(u8)	0x41
#define BMI085_A_RANGE_DATA		(u8)	0x03


#endif /* HEADER_SATELLITE_H_ */

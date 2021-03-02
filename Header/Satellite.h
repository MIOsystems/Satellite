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
#define BMI_CS_A_PIN				134
#define BMI_CS_G_PIN				121
#define BMI_XMC_MODE 				XMC_GPIO_MODE_OUTPUT_PUSH_PULL

//OPCODES

#define BMI_G_CHIP_ID_ADDR	(u8)	0x00
#define BMI_A_CHIP_ID_ADDR	(u8)	0x00
#define BMI_A_PWR_CTRL_ADDR (u8)	0x7C

// BMI ACCELEROMETER CONFIG
#define BMI_A_CONFIG_ADDR	(u8)	0x40
// PWR MODE
#define BMI_A_PWR_OFF		(u8)	0x00
#define BMI_A_PWR_ON		(u8)	0x04
// ODR (OUTPUT DATA RATE)
#define BMI_A_ODR_12_5_HZ	(u8)	0x05
#define BMI_A_ODR_25_HZ		(u8)	0x06
#define BMI_A_ODR_50_HZ		(u8)	0x07
#define BMI_A_ODR_100_HZ	(u8)	0x08
#define BMI_A_ODR_200_HZ	(u8)	0x09
#define BMI_A_ODR_400_HZ	(u8)	0x0A
#define BMI_A_ODR_800_HZ	(u8)	0x0B
#define BMI_A_ODR_1600_HZ	(u8)	0x0C
// RANGE
#define BMI_A_RANGE_2G		(u8)	0x00
#define BMI_A_RANGE_4G		(u8)	0x01
#define BMI_A_RANGE_8G		(u8)	0x02
#define BMI_A_RANGE_16G		(u8)	0x03
// BANDWIDTH
#define BMI_A_BWP_OSR4		(u8)	0x00
#define BMI_A_BWP_OSR2		(u8)	0x01
#define BMI_A_BWP_NORMAL	(u8)	0x02

#define BMI_A_ODR_MASK		(u8) 	0x0F
#define BMI_A_BW_MASK		(u8) 	0x70
#define BMI_A_BW_POS		(u8) 	4
#define BMI_A_RANGE_MASK	(u8) 	0x03


// BMI GYROSCOPE CONFIG 
//BANDWIDTH
#define BMI_G_ODR_BW_ADDR			(u8) 0x10
#define BMI_G_ODR_BW_MASK			(u8) 0x0F
#define BMI_G_ODR_2000_HZ_BW_523 	(u8) 0x00
#define BMI_G_ODR_2000_HZ_BW_230 	(u8) 0x01
#define BMI_G_ODR_1000_HZ_BW_116 	(u8) 0x02
#define BMI_G_ODR_400_HZ_BW_47 		(u8) 0x03
#define BMI_G_ODR_200_HZ_BW_23 		(u8) 0x04
#define BMI_G_ODR_100_HZ_BW_12	 	(u8) 0x05
#define BMI_G_ODR_200_HZ_BW_64 		(u8) 0x06
#define BMI_G_ODR_100_HZ_BW_32		(u8) 0x07

// RANGE
#define BMI_G_RANGE_ADDR			(u8) 0x0F
#define BMI_G_RANGE_MASK			(u8) 0x07
#define BMI_G_RANGE_2000_DPS 		(u8) 0x00
#define BMI_G_RANGE_1000_DPS 		(u8) 0x01
#define BMI_G_RANGE_500_DPS	 		(u8) 0x02
#define BMI_G_RANGE_250_DPS	 		(u8) 0x03
#define BMI_G_RANGE_125_DPS	 		(u8) 0x04

// POWER MODE
#define BMI_G_PWR_ADDR		(u8)	0x11
#define BMI_G_PWR_NORMAL	(u8)	0x00
#define BMI_G_PWR_SUSPEND	(u8)	0x80
#define BMI_G_PWR_D_SUSPEND	(u8)	0x20


#define BMI_G_DATA_ADDR	(u8)		0x02
#define BMI_G_BUFF_S				6

#define BMI_A_DATA_ADDR	(u8)		0x12
#define BMI_A_BUFF_S	(u8)		6

#endif /* HEADER_SATELLITE_H_ */

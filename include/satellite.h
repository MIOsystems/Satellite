#ifndef SATELLITE_H_
#define SATELLITE_H_

#include <include/util/types.h>

#define ONEMSDELAY 11500

// Dont use this for release builds
//#define DEBUG_MODE

//#define BMI_DATA_IN_MG

// Communication
#define COM_UDP_IP_1		(u8)	192
#define COM_UDP_IP_2		(u8)	168
#define COM_UDP_IP_3		(u8)	0
#define COM_UDP_IP_4		(u8)	11
#define COM_UDP_PORT_IN		(u16)	52256
#define COM_UDP_PORT_OUT	(u16)	62510

#endif

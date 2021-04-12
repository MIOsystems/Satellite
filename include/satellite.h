#ifndef SATELLITE_H_
#define SATELLITE_H_

#include <include/util/types.h>

#define ONEMSDELAY 11500

// turn this on if you want to validate hqw
#define RUN_HW_VALIDATIO

/**
 * ==========================================
 * Sensor Defines
 * ==========================================
 * Uncomment out which sensor you want to use,
 * and comment which sensor you want to use
 */

/* IMU */
#define BMI085

/* GNSS */
#define UBLX

/**
 * ==========================================
 * Filter Defines
 * ==========================================
 * Uncomment out which sensor you want to use,
 * and comment which sensor you want to use
 */
#define COMP_FILTER
//#define MADGWICK_FILTER

// Communication
#define COM_UDP_IP_1		(u8)	192
#define COM_UDP_IP_2		(u8)	168
#define COM_UDP_IP_3		(u8)	0
#define COM_UDP_IP_4		(u8)	11
#define COM_UDP_PORT_IN		(u16)	52256
#define COM_UDP_PORT_OUT	(u16)	62510

// in ms
#define UDP_INTERVAL_PACKET	(u32)	100 // 1 sec

#endif

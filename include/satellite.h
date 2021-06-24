#ifndef SATELLITE_H_
#define SATELLITE_H_

#include <include/util/types.h>

#define ONEMSDELAY 11500

// turn this on if you want to validate hqw
//#define RUN_HW_VALIDATION

/**
 * ==========================================
 * Sensor Defines
 * ==========================================
 * Uncomment out which sensor you want to use,
 * and comment which sensor you want to use
 */

/* IMU */
#define BMI085

///* GNSS */
#define UBLX

/* Proximity switch */
//#define ENABLE_PROXIMITY_SWITCH
//#define PROXIMITY_IO35
//
///* Altimeter */
//#define ENABLE_ALTIMETER
//#define ALTIMETER_SF30
/**
 * ==========================================
 * Filter Defines
 * ==========================================
 * Uncomment out which sensor you want to use,
 * and comment which sensor you want to use
 */
//#define COMP_FILTER
//#define MADGWICK_FILTER

/**
 * ==========================================
 * Transformations Defines
 * ==========================================
 */
//#define ENABLE_SPECTRUM_ANALYSIS

// Communication
#define COM_UDP_IP_1			(u8)	192
#define COM_UDP_IP_2			(u8)	168
#define COM_UDP_IP_3			(u8)	0
#define COM_UDP_IP_4			(u8)	11
#define COM_UDP_PORT_IN		(u16)	52256
#define COM_UDP_PORT_OUT		(u16)	62510

// HUB (CAN/SERIAL)
#define CAN_ADDRESS_SATELLITE			0x20
#define CAN_ADDRESS_MASTER			0x10
#define CAN_ADDRESS_BROADCAST			0x00

// in ms
#define UDP_INTERVAL_PACKET			(u32)	1000 // 1 sec
#define UDP_INTERVAL_DEBUG_PACKET	(u32)	1 // 1 ms
#define POLL_INTERVAL					(u32)	1
//#define UDP_BMI_DEBUG_MSG
#endif

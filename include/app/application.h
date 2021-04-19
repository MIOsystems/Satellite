/*
 * application.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <include/util/types.h>
#include <include/satellite.h>
#include <include/sensor/imu/imu.h>
#include <include/sensor/gps/gnss.h>
#include <include/communication/com_udp.h>

#ifdef BMI085
	bmi085x imu;
#endif

#ifdef UBLX
	ubx_frame_t gps_frame;
	gps_values_t gps_packet;
#endif

typedef struct
{
	volatile u32 udp_debug_counter;
	volatile u32 udp_counter;
} app_clock;

app_clock application_clock;


u8 app_init();
void app_hw_init();

void app_timer_update();

void app_update();

#endif /* APPLICATION_H_ */

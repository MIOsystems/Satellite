/*
 * application.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <DAVE.h>
#include <include/util/types.h>
#include <include/satellite.h>
#include <include/sensor/imu/imu.h>
#include <include/sensor/gps/gnss.h>
#include <include/communication/com_udp.h>

#ifdef ENABLE_PROXIMITY_SWITCH
	#include <include/sensor/proximity/proximity_switch.h>
	proximity_switch_t prox_switch;
	#ifdef IO35
		#include <include/sensor/proximity/IO35/proximity_IO35.h>

	#endif
#endif

#ifdef BMI085
	bmi085x imu;
#endif

#ifdef UBLX
	ubx_frame_t gps_frame;
	gps_values_t gps_packet;
#endif

#ifdef ENABLE_ALTIMETER
	#include <include/sensor/altimeter/altimeter.h>
	altimeter_data_t altimeter_data;
#endif



typedef struct
{
	volatile u32 udp_debug_counter;
	volatile u32 udp_counter;
} app_clock;

app_clock application_clock;


u8 app_init();

void app_timer_update();

void app_update();

#endif /* APPLICATION_H_ */

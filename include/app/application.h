/*
 * application.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <DAVE.h>
#include <include/communication/com_hub.h>
#include <include/util/types.h>
#include <include/satellite.h>
#include <include/sensor/imu/imu.h>
#include <include/sensor/gps/gnss.h>
#include <include/communication/com_udp.h>
#include <include/communication/com_hub.h>

#ifdef ENABLE_PROXIMITY_SWITCH
	#include <include/sensor/proximity/proximity_switch.h>
	#ifdef IO35
		#include <include/sensor/proximity/IO35/proximity_IO35.h>

	#endif
	proximity_switch_t prox_switch;

#endif

#ifdef BMI085
	bmi085x imu;
#endif

#ifdef UBLX
	UbxFrame_t gps_frame;
	GPSValues_t gps_packet;
#endif

#ifdef ENABLE_ALTIMETER
	#include <include/sensor/altimeter/altimeter.h>
	AltimeterData_t altimeter_data;
#endif



typedef struct
{
	volatile u32 udp_debug_counter;
	volatile u32 udp_counter;
} app_clock;

app_clock application_clock;


i8 app_init();

void app_timer_update();

void app_update();

#endif /* APPLICATION_H_ */

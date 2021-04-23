/*
 * application.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/app/application.h>


u8 app_init()
{
	application_clock.udp_counter = 0;
	application_clock.udp_debug_counter = 0;
	u8 status = DAVE_STATUS_SUCCESS;


	// Communication
	status = udp_initialize();
	if(status != 0)
	{
		return status;
	}
	// Sensors
	// IMU
#ifdef BMI085
	DIGITAL_IO_SetOutputHigh(&CS_A);
	status = imu_bmi085_init(&imu);
	if(status != BMI085X_SUCCESS)
	{
		return DAVE_STATUS_FAILURE;
	}
#endif
//
//	//GPS Sensor, only creates the structure
//#ifdef UBLX
//	//gnss_init();
//#endif
//
#ifdef ENABLE_PROXIMITY_SWITCH
	proximity_init(&prox_switch);
#endif
//
#ifdef ENABLE_ALTIMETER
	altimeter_init(&altimeter_data);
#endif
	return DAVE_STATUS_SUCCESS;

}

void app_timer_update()
{
	imu_poll(&imu);

#ifdef ENABLE_PROXIMITY_SWITCH
	proximity_update(&prox_switch);
#endif


#ifdef ENABLE_ALTIMETER
	altimeter_update(&altimeter_data);
#endif

	// udp cycle for every second send data
#ifdef UDP_BMI_DEBUG_MSG
	if(application_clock.udp_debug_counter == UDP_INTERVAL_DEBUG_PACKET)
	{
		udp_send_debug_bmi(imu);
		application_clock.udp_debug_counter = 0;
	}
#endif
	if(application_clock.udp_counter == UDP_INTERVAL_PACKET)
	{
		if(gps_rx_handler() == 0)
		{
			udp_send_gps(gps_packet);
		}
		udp_send_bmi(imu);
		udp_send_proximity(prox_switch);
		udp_send_altimeter(altimeter_data);
		application_clock.udp_counter = 0;
	}
	application_clock.udp_debug_counter++;
	application_clock.udp_counter++;
}

void app_update()
{

}

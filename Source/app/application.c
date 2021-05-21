/*
 * application.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#include <include/app/application.h>

bool sendData = false;
bool pollImu = false;
bool sendDebug = false;

i8 appInit()
{
	applicationClock.udp_counter = 0;
	applicationClock.udp_debug_counter = 0;
	i8 status = DAVE_STATUS_SUCCESS;


	// Communication
	status = udp_initialize();
	if(status != 0)
	{
		return status;
	}

	status = comHubInit();
	if(status != 0)
	{
		return status;
	}
	// Sensors
	// IMU
#ifdef BMI085
	DIGITAL_IO_SetOutputHigh(&CS_A);
	status = (i8) imu_bmi085_init(&imu);
	if(status != BMI085X_SUCCESS)
	{
		return DAVE_STATUS_FAILURE;
	}
#endif

	//GPS Sensor, only creates the structure
#ifdef UBLX
	//gnss_init();
#endif

#ifdef ENABLE_PROXIMITY_SWITCH
	proximity_init(&prox_switch);
#endif
//
#ifdef ENABLE_ALTIMETER
	altimeter_init(&altimeter_data);
#endif

#ifdef ENABLE_SPECTRUM_ANALYSIS
	fftCreate(&fftHandler);
#endif
	return DAVE_STATUS_SUCCESS;

}

void appTimerUpdate()
{
	// udp cycle for every second send data
	pollImu = true;
#ifdef UDP_BMI_DEBUG_MSG
	if(applicationClock.udp_debug_counter == UDP_INTERVAL_DEBUG_PACKET)
	{
		sendDebug = true;
		applicationClock.udp_debug_counter = 0;
	}
#endif
	if(applicationClock.udp_counter == UDP_INTERVAL_PACKET)
	{
		sendData = true;
		applicationClock.udp_counter = 0;
	}
	applicationClock.udp_debug_counter++;
	applicationClock.udp_counter++;
}

void appUpdate()
{
	if(pollImu)
	{
		imu_poll(&imu);
		pollImu = false;
	}

#ifdef ENABLE_SPECTRUM_ANALYSIS
//	//fftUpdate(&fftHandler, 	imu.data.accel_poll_val.x,
//							imu.data.accel_poll_val.y,
//							imu.data.accel_poll_val.z);

#endif

#ifdef ENABLE_PROXIMITY_SWITCH
	proximity_update(&prox_switch);
#endif


#ifdef ENABLE_ALTIMETER
	altimeter_update(&altimeter_data);
#endif
	if(sendData)
	{
		if(gps_rx_handler() == 0)
		{
			DIGITAL_IO_SetOutputLow(&LED_BLUE);
			udp_send_gps(gpsPacket);
		}
		udp_send_bmi(imu);
#if ENABLE_ALTIMETER
		udp_send_proximity(prox_switch);

#endif

#if ENABLE_PROXIMITY_SWITCH
		udp_send_altimeter(altimeter_data);
#endif
		sendData = false;
	}

#ifdef UDP_BMI_DEBUG_MSG
	if(sendDebug)
	{
		DIGITAL_IO_SetOutputLow(&LED_BLUE);
		udp_send_debug_bmi(imu);

		udp_send_spectrum(fftHandler);
		sendDebug = false;
	}
#endif

	comHubRecvHandle();
}

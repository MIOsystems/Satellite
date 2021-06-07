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
#ifdef ENABLE_SPECTRUM_ANALYSIS
bool sendSpectrum = false;
#endif

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
	fftCreate(&fft);
#endif
	return DAVE_STATUS_SUCCESS;

}

void appTimerUpdate()
{
	if(applicationClock.pollCounter == POLL_INTERVAL)
	{
		pollImu = true;
		applicationClock.pollCounter = 0;
	}
	else
	{
		applicationClock.pollCounter++;
	}


#ifdef UDP_BMI_DEBUG_MSG
	if(applicationClock.udp_debug_counter == UDP_INTERVAL_DEBUG_PACKET)
	{
		sendDebug = true;
		applicationClock.udp_debug_counter = 0;
	}
	else
	{
		applicationClock.udp_debug_counter++;
	}
#endif
	if(applicationClock.udp_counter == UDP_INTERVAL_PACKET)
	{
		sendData = true;
		pollImu = true;
#ifdef ENABLE_SPECTRUM_ANALYSIS
		sendSpectrum = true;
#endif
		applicationClock.udp_counter = 0;
	}
	else
	{
		applicationClock.udp_counter++;
	}

	if(applicationClock.udp_counter == 128)
	{
#ifdef ENABLE_SPECTRUM_ANALYSIS
		sendSpectrum = true;
#endif
	}

}

void appUpdate()
{
	if(pollImu)
	{
		imu_poll(&imu);
		pollImu = false;
		fftAddData(&fft, imu.data.accel_poll_val);


	}

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
		//udp_send_bmi(imu);

#if ENABLE_ALTIMETER
		udp_send_proximity(prox_switch);

#endif

#if ENABLE_PROXIMITY_SWITCH
		udp_send_altimeter(altimeter_data);
#endif
		sendData = false;
	}

#ifdef ENABLE_SPECTRUM_ANALYSIS
	if(sendSpectrum)
	{

		u8 status = fftUpdate(&fft);
		if(status == FFT_SUCCESS)
		{
			udp_send_spectrum(fft.buffOut.x, "x,");
			udp_send_spectrum(fft.buffOut.y, "y,");
			//udp_send_spectrum(fft.buffOut.z, "z,");
		}

		sendSpectrum = false;
	}
#endif


#ifdef UDP_BMI_DEBUG_MSG
	if(sendDebug)
	{
		DIGITAL_IO_SetOutputLow(&LED_BLUE);
		udp_send_debug_bmi(imu);
#ifdef ENABLE_SPECTRUM_ANALYSIS
		udp_send_spectrum(fft);
#endif
		sendDebug = false;
	}
#endif

	comHubRecvHandle();
}

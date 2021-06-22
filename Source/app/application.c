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
bool addSpectrumData = false;
#endif

i8 appInit()
{
	applicationClock.udpCounter = 0;
	applicationClock.udpDebugCounter = 0;
	applicationClock.udpSpectrumCounter = 0;
	applicationClock.pollCounter = 0;

	i8 status = DAVE_STATUS_SUCCESS;

	// Communication
	status = udp_initialize();
	if(status != 0)
	{
		return status;
	}

	status = (i8) comHubInit();
	if(status != 0)
	{
		return status;
	}
	// Sensors
	// IMU
#ifdef BMI085
	DIGITAL_IO_SetOutputHigh(&CS_A);
	status = (i8) imuInit(&imu);
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

	proximitInit(&prox_switch);
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
#ifdef ENABLE_SPECTRUM_ANALYSIS
		addSpectrumData = true;
#endif
		applicationClock.pollCounter = 0;
	}
	else
	{
		applicationClock.pollCounter++;
	}


#ifdef UDP_BMI_DEBUG_MSG
	if(applicationClock.udpDebugCounter == UDP_INTERVAL_DEBUG_PACKET)
	{
		sendDebug = true;
		applicationClock.udpDebugCounter = 0;
	}
	else
	{
		applicationClock.udpDebugCounter++;
	}
#endif
	if(applicationClock.udpCounter == UDP_INTERVAL_PACKET)
	{
		sendData = true;
		pollImu = true;
#ifdef ENABLE_SPECTRUM_ANALYSIS
		sendSpectrum = true;
#endif
		applicationClock.udpCounter = 0;
	}
	else
	{
		applicationClock.udpCounter++;
	}

#ifdef ENABLE_SPECTRUM_ANALYSIS
	if(applicationClock.udpSpectrumCounter == FFT_N)
	{
		sendSpectrum = true;
		applicationClock.udpSpectrumCounter = 0;
	}
	else
	{
		applicationClock.udpSpectrumCounter++;
	}
#endif

}

void appUpdate()
{

#ifdef ENABLE_PROXIMITY_SWITCH
	proximityUpdate(&prox_switch);
#endif


#ifdef ENABLE_ALTIMETER
	altimeter_update(&altimeter_data);
#endif

	appHandleCustomerPackets();
	appHandleSpectrum();
	appHandleDebugImu();
	comHubRecvHandle();
}

void appHandleCustomerPackets(void)
{
	if(pollImu)
	{
		imuPoll(&imu);
		pollImu = false;
	}

	if(sendData)
	{
		if(gpsRecvHandler() == 0)
		{
			DIGITAL_IO_SetOutputLow(&LED_BLUE);
			udp_send_gps(gpsPacket);
		}
		udp_send_bmi(imu);


		appHandleAltimeter();
		appHandleProxSwitch();


		sendData = false;
	}
}

void appHandleSpectrum(void)
{
#ifdef ENABLE_SPECTRUM_ANALYSIS
	if(addSpectrumData)
	{
		fftAddData(&fft, imu.data.accel_poll_val);
		addSpectrumData = false;
	}
	if(sendSpectrum)
	{
		u8 status = fftUpdate(&fft);
		if(status == FFT_SUCCESS)
		{
			udp_send_spectrum(fft.bufferOut.x, "x,");
			udp_send_spectrum(fft.bufferOut.y, "y,");
			udp_send_spectrum(fft.bufferOut.z, "z,");
		}
		sendSpectrum = false;
	}
#endif
}

void appHandleDebugImu(void)
{
#ifdef UDP_BMI_DEBUG_MSG
	if(sendDebug)
	{
		DIGITAL_IO_SetOutputLow(&LED_BLUE);
		udp_send_debug_bmi(imu);
		sendDebug = false;
	}
#endif
}

void appHandleAltimeter(void)
{
#ifdef ENABLE_ALTIMETER
	udp_send_altimeter(altimeter_data);
#endif
}

void appHandleProxSwitch(void)
{
#ifdef ENABLE_PROXIMITY_SWITCH
	udp_send_proximity(prox_switch);
#endif
}

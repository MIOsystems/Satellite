/*
 * main.c
 *
 *  Created on: 2020 Aug 27 09:10:51
 *  Author: Patrick
 */

#include <math.h>
//Declarations from DAVE Code Generation (includes SFR declaration)
#include <DAVE.h> 

#include <include/satellite.h>

#include <include/util/types.h>
#include <include/util/delay.h>
#include <include/util/math_utility.h>

#ifdef IMU_COM
#include "include/communication/com_serial_imu.h"
#endif

#ifdef RUN_HW_VALIDATION
	#include <include/validation/validate_app.h>
#else
	#include <include/app/application.h>
	#include <include/communication/com_udp.h>
	#include <include/app/application.h>
	#include <include/filters/complimentary_filter.h>
	#include <include/filters/MadgwickAHRS.h>
	#include <include/sensor/altimeter/SF30/sf30.h>
#endif

void rs232_interrupt(void) {
#ifndef RUN_HW_VALIDATION
	#ifdef UBLX
		gnssPoll();
	#endif
#else
	validate_rs232_update();
#endif
}

void rs422_interrupt(void)
{
#ifndef RUN_HW_VALIDATION
	#ifdef ALTIMETER_SF30
		sf30_rx_handle();
	#endif
	#ifdef IMU_COM
		imu_serial_com_recv();
	#endif
#else
	validate_rs422_update();
#endif
}

void can_uart_handler(void)
{
#ifndef RUN_HW_VALIDATION
	#ifdef HUB_CONNECTED
		comHubRecv();
	#endif
#else
#endif
}

void uart_interrupt(void)
{
#ifndef RUN_HW_VALIDATION
#else
	validate_uart_update();
#endif
}

void tick_timer_ISR(void)
{
#ifndef RUN_HW_VALIDATION
	appTimerUpdate();
#else
	validation_app_send();

#endif
}


int main(void)
{
	delayMs(100);
	// output 4.4 reset pin phy ethernet
	XMC_GPIO_SetMode(XMC_GPIO_PORT4, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	delayMs(20);
	XMC_GPIO_SetOutputLevel(XMC_GPIO_PORT4, 4, XMC_GPIO_OUTPUT_LEVEL_HIGH);
	delayMs(2000);


	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */
	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U)
		{
			/* Toggle error light */
			DIGITAL_IO_ToggleOutput(&LED_RED);
			delayMs(500);
		}
	}

#ifndef RUN_HW_VALIDATION
	i8 status_app = 0;
	status_app = appInit();
	if(status_app != DAVE_STATUS_SUCCESS)
	{
		while(1)
		{
			DIGITAL_IO_ToggleOutput(&LED_RED);
			delayMs(500);
		}
	}

#else
	validation_app_init();
#endif

	INTERRUPT_Enable(&POLL_TIMER_INTERRUPT);
	TIMER_Start(&POLL_TIMER);
//	INTERRUPT_Enable(&RS232_INTERRUPT);
	INTERRUPT_Enable(&RS422_INTERRUPT);
//	INTERRUPT_Enable(&UART_INTERRUPT);

//	INTERRUPT_Enable(&HUB_UART_3_INTERRUPT);

	while (1U)
	{
#ifdef RUN_HW_VALIDATION
		validation_app_run();
#else
		appUpdate();
#endif
		sys_check_timeouts();
	}
}

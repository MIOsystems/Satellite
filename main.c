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
	gnss_poll();

#else
	validate_rs232_update();
#endif
}

void rs422_interrupt(void)
{
#ifndef RUN_HW_VALIDATION
	#ifdef ALTIMETER_SF30
		//sf30_rx_handle();
	#endif

	com_hub_recv();

#else
	validate_rs422_update();
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
	app_timer_update();
#else

#endif
}



int main(void)
{
	delay_ms(100);
	// output 4.4 reset pin phy ethernet
	XMC_GPIO_SetMode(XMC_GPIO_PORT4, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	delay_ms(20);
	XMC_GPIO_SetOutputLevel(XMC_GPIO_PORT4, 4, XMC_GPIO_OUTPUT_LEVEL_HIGH);
	delay_ms(2000);

	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U)
		{
		}
	}
#ifndef RUN_HW_VALIDATION
	i8 status_app = 0;
	status_app = app_init();
	if(status_app != DAVE_STATUS_SUCCESS)
	{
		while(1)
		{
			DIGITAL_IO_ToggleOutput(&LED_0);
			DIGITAL_IO_ToggleOutput(&LED_1);
			DIGITAL_IO_ToggleOutput(&LED_2);
			DIGITAL_IO_ToggleOutput(&LED_3);
			delay_ms(500);
		}
	}

#else
	validation_app_init();
#endif

	TIMER_Start(&POLL_TIMER);
	INTERRUPT_Enable(&RS232_INTERRUPT);
	INTERRUPT_Enable(&RS422_INTERRUPT);
	INTERRUPT_Enable(&UART_INTERRUPT);
	INTERRUPT_Enable(&POLL_TIMER_INTERRUPT);


	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U)
	{
#ifdef RUN_HW_VALIDATION
		validation_app_run();
#else
		app_update();
#endif

		sys_check_timeouts();
	}
}

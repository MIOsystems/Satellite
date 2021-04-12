/*
 * main.c
 *
 *  Created on: 2020 Aug 27 09:10:51
 *  Author: Patrick
 */

//Declarations from DAVE Code Generation (includes SFR declaration)
#include <DAVE.h> 

#include <include/util/types.h>
#include <include/util/delay.h>
#include <include/util/math_utility.h>
#include <math.h>

#ifdef RUN_HW_VALIDATION
	#include <include/validation/validate_app.h>
#else
	#include <include/app/application.h>
	#include <include/communication/com_udp.h>
	#include <include/app/application.h>
	#include <include/filters/complimentary_filter.h>
	#include <include/filters/MadgwickAHRS.h>
#endif

void gnss_interrupt(void) {
	gnss_poll();
}

void tick_timer_ISR(void)
{
	app_timer_update();
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
	u8 status_app = 0;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

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
	TIMER_Start(&POLL_TIMER);



	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U)
		{
		}
	}

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U)
	{

		sys_check_timeouts();
	}
}

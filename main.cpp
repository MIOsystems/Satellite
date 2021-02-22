/*
 * main.c
 *
 *  Created on: 2020 Aug 27 09:10:51
 *  Author: Patrick
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

#include <Header/BMI085.h>
#include <Header/ComUDP.h>
#include <Header/Utility.h>
#include <Header/GNSS.h>

//GNSS gnss;

void tick_timer_ISR(void);


int main(void)
{
	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */
//	ComUDP udp;
//	udp.init();


	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U)
		{
		}
	}

	DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_0);
	DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_1);
	DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_2);
	DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_3);
	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U)
	{
		Utility::delay_ms(1);
		sys_check_timeouts();
	}
}

void tick_timer_ISR(void) {

}

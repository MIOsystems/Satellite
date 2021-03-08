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

BMI085 bmi;
GNSSData data;
GNSS gnss;
ComUDP udp;

#ifdef __cplusplus
extern "C" {
#endif

	void gnss_interrupt(void) {
		gnss.poll();
	}

	void tick_timer_ISR(void)
	{

		DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_0);
		if(gnss.rx_handler(data) == DAVE_STATUS_SUCCESS) {
			const GNSSData packet = data;
			udp.send_gnss(packet);
		}
		bmi.poll();
		udp.send_bmi(bmi);
		Utility::delay(2000);
	}


#ifdef __cplusplus
}
#endif


int main(void)
{
	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	Utility::delay(50000);
	udp.init();
	u8 status_bmi = 0;
	status_bmi = bmi.init();
	TIMER_Start(&POLL_TIMER);



	if(status_bmi != 0)
	{
		while(1U)
		{

		}
	}

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

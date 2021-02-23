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
		if(gnss.rx_handler() == DAVE_STATUS_SUCCESS) {
			udp.send_gnss(gnss.gnss_data);
		}
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_LED_0);
	}
#ifdef __cplusplus
}
#endif



int main(void)
{
	DAVE_STATUS_t _status;
	_status = DAVE_Init(); /* Initialization of DAVE APPs  */
	TIMER_Stop(&TIMER_0);
	udp.init();
	Utility::delay_ms(10);
	TIMER_Start(&TIMER_0);
	TIMER_SetTimeInterval(&TIMER_0, 1000000); // 1 second


	if(_status != DAVE_STATUS_SUCCESS)
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
//		_status = (DAVE_STATUS_t) udp.send_ok();
//		if(_status == DAVE_STATUS_SUCCESS) {
//			Utility::delay_ms(1);
//		} else {
//			Utility::delay_ms(1);
//		}
		//Utility::delay_ms(1);
		sys_check_timeouts();
	}
}

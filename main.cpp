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

#define ONEMSDELAY 11500
u32 counter = 0;
#ifdef __cplusplus
extern "C" {
#endif

	void gnss_interrupt(void) {
		gnss.poll();

	}

	void tick_timer_ISR(void)
	{
		// loop in the second thousandtimes
		if(counter == 1000 || counter > 1000)
		{
			if(gnss.rx_handler(data) == DAVE_STATUS_SUCCESS)
			{
				const GNSSData packet = data;
				udp.send_gnss(packet);
			}
			DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_3_SPI_ACCEL);
			udp.send_bmi(bmi);
			bmi.reset();
			counter = 0;
		}
		bmi.poll();
		counter++;

	}


#ifdef __cplusplus
}
#endif

void delay_ms(u32 time_ms)
{
	u32 cycle = ONEMSDELAY *time_ms;

	while(cycle--)
	{
		__NOP();
	}

}

int main(void)
{
	delay_ms(100);

	XMC_GPIO_SetMode(XMC_GPIO_PORT5, 6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(XMC_GPIO_PORT5, 7, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetOutputLevel(XMC_GPIO_PORT5, 7, XMC_GPIO_OUTPUT_LEVEL_HIGH);
	// output 4.4 reset pin phy ethernet
	XMC_GPIO_SetMode(XMC_GPIO_PORT4, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	delay_ms(20);
	XMC_GPIO_SetOutputLevel(XMC_GPIO_PORT4, 4, XMC_GPIO_OUTPUT_LEVEL_HIGH);
	delay_ms(2000);

	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	XMC_GPIO_SetOutputLevel(XMC_GPIO_PORT5, 6, XMC_GPIO_OUTPUT_LEVEL_HIGH);

	Utility::delay(50000);
	udp.init();
	u8 status_bmi = 0;
	status_bmi = bmi.init();
	TIMER_Start(&POLL_TIMER);



	if(status_bmi != 0)
	{
		DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_2_SPI_GYRO);
		DIGITAL_IO_ToggleOutput(&DIGITAL_IO_LED_3_SPI_ACCEL);
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

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
	#include <include/validation/valdiation_app.h>
#else
	#include <include/communication/com_udp.h>
	#include <include/composer/composer.h>
	#include <include/filters/complimentary_filter.h>
	#include <include/filters/MadgwickAHRS.h>
#endif



#define DT_SEC			(f32) 0.001
u32 counter = 0;

typedef struct {
  float         q1,q2,q3,q4;
} quaternion_t;

quaternion_t quat;

float r = 0.0f;
float p = 0.0f;
float y = 0.0f;

void eulerAngles(quaternion_t q, float* roll, float* pitch, float* yaw);

/*
 returns as pointers, roll pitch and yaw from the quaternion generated in imu_filter
 Assume right hand system
 Roll is about the x axis, represented as phi
 Pitch is about the y axis, represented as theta
 Yaw is about the z axis, represented as psi
 */
void eulerAngles(quaternion_t q, float* roll, float* pitch, float* yaw){

    *yaw = 		atan2f( (2 * q.q2 * q.q3 - 2 * q.q1 * q.q4), (2 * q.q1 * q.q1 + 2 * q.q2 * q.q2 - 1));
    *pitch = 	-asinf(2 * q.q2 * q.q4 + 2 * q.q1 * q.q3);
    *roll  = 	atan2f( (2 * q.q3 * q.q4 - 2 * q.q1 * q.q2), (2 * q.q1 * q.q1 + 2 * q.q4 * q.q4 - 1));
}



void gnss_interrupt(void) {
	gnss_poll();
}

void tick_timer_ISR(void)
{
#ifndef RUN_HW_VALIDATION
	bmi085a_poll(&imu);
	bmi085g_poll(&imu);
	complimentary_process(&imu);


	MadgwickAHRSupdateIMU(	imu.data.gyro_poll_val.x,
							imu.data.gyro_poll_val.y,
							imu.data.gyro_poll_val.z,
							imu.data.accel_poll_val.x,
							imu.data.accel_poll_val.y,
							imu.data.accel_poll_val.z,
							0.001f);

    quat.q1 = q0;
    quat.q2 = q1;
    quat.q3 = q2;
    quat.q4 = q3;

	eulerAngles(quat, &r, &p,  &y);
	imu.data.angle.x = r * RAD_TO_DEG_CONST;
	imu.data.angle.y = p * RAD_TO_DEG_CONST;
	imu.data.angle.z = y * RAD_TO_DEG_CONST;

	if(counter >= 100)
	{

		udp_send_debug_bmi(imu);
		bmi085x_reset_data(&imu);
	}
	if(counter >= 1000)
	{
		if(gps_rx_handler() == 0)
		{
			udp_send_gps(gps_packet);
		}
		//udp_send_bmi(imu);
		//bmi085x_reset_data(&imu);
		counter = 0;
	}
	counter++;
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

#ifndef RUN_HW_VALIDATION
	u8 status_app = 0;
	status_app = composer_init();
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

	INTERRUPT_Enable(&GNSS_INTERRUPT_0);
	TIMER_Start(&POLL_TIMER);
#else
	validation_app_init();

#endif

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
#ifdef RUN_HW_VALIDATION
		validation_app_run();
#endif
		delay_ms(1);
		sys_check_timeouts();
	}
}

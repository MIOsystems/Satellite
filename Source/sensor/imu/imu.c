/*
 * imu.c
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */
#include <include/sensor/imu/imu.h>

u8 imu_bmi085_init(bmi085x* imu)
{
	u8 status = 0;
#ifdef BMI085
	bmi085x_init(imu);
	status = bmi085a_init(imu);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}
	status = bmi085g_init(imu);
	return status;
#endif
	return status;
}

u8 imu_poll(bmi085x* imu)
{
#ifdef BMI085
	BMI085xStatus_e status = bmi085a_poll(imu);
	status = bmi085g_poll(imu);

	#ifdef COMP_FILTER
		complimentary_process(	imu->data.accel_poll_val.x, imu->data.accel_poll_val.y, imu->data.accel_poll_val.z,
								imu->data.gyro_poll_val.x, imu->data.gyro_poll_val.y,	imu->data.gyro_poll_val.z,
								&imu->data.angle.y, &imu->data.angle.x, &imu->data.angle.z);
	#endif
	#ifdef MADGWICK_FILTER
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
	#endif
#endif
	return status;
}

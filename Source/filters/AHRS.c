/*
 * AHRS.c
 *
 *  Created on: 30 Mar 2021
 *      Author: Patrick
 */
#include <math.h>

#include <include/filters/AHRS.h>


void AHRS_update(bmi085x* data)
{
	//f32 ax = data->data.accel_poll_val.x * 9.81f;
	//f32 ay = data->data.accel_poll_val.y * 9.81f;
	//f32 az = data->data.accel_poll_val.z * 9.81f;
	//f32 gx = data->data.gyro_poll_val.x;
	//f32 gy = data->data.gyro_poll_val.y;
	//f32 gz = data->data.gyro_poll_val.z;

	f32 ax = 0;
	f32 ay = 0;
	f32 az = 1.0f;
	f32 gx = 0;
	f32 gy = 0;
	f32 gz = 1.57;
	f32 recipNorm;

	// Rate of change of quaternion from gyroscope
	f32 qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	f32 qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	f32 qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	f32 qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		const f32 input = ax * ax + ay * ay + az * az;
		recipNorm = inverse_sqrt(input);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		f32 _2q0 = 2.0f * q0;
		f32 _2q1 = 2.0f * q1;
		f32 _2q2 = 2.0f * q2;
		f32 _2q3 = 2.0f * q3;
		f32 _4q0 = 4.0f * q0;
		f32 _4q1 = 4.0f * q1;
		f32 _4q2 = 4.0f * q2;
		f32 _8q1 = 8.0f * q1;
		f32 _8q2 = 8.0f * q2;
		f32 q0q0 = q0 * q0;
		f32 q1q1 = q1 * q1;
		f32 q2q2 = q2 * q2;
		f32 q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		f32 s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		f32 s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		f32 s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		f32 s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = inverse_sqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * DELTA;
	q1 += qDot2 * DELTA;
	q2 += qDot3 * DELTA;
	q3 += qDot4 * DELTA;

	// Normalise quaternion
	recipNorm = inverse_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;


	eulerAngles(data);
}

void eulerAngles(bmi085x* imu)
{
	const f32 yaw	= atan2f((2 * q1 * q2 - 2 * q0 * q3), (2 * powf(q0, 2) + 2 * powf(q1, 2) - 1));
	const f32 pitch = -asinf(2 * q1 * q3 + 2 * q0 * q2);
	const f32 roll  = atan2f((2 * q2 * q3 - 2 * q0 * q1), (2 * powf(q0, 2) + 2 * powf(q3, 2) - 1));

    imu->data.angle.z = yaw * (180 / M_PI);
    imu->data.angle.y = pitch * (180 / M_PI);
    imu->data.angle.x = roll * (180 / M_PI);
}

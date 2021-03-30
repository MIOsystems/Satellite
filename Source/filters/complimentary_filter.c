#include <math.h>

#include <include/filters/complimentary_filter.h>
#include <include/util/math_utility.h>




void complimentary_f_process(bmi085x* data)
{
	const f32 dt = 0.001f;
	const f32 Ax = roundf(data->data.accel_poll_val.x * 100) / 100;
	const f32 Ay = roundf(data->data.accel_poll_val.y * 100) / 100;
	const f32 Az = roundf(data->data.accel_poll_val.z * 100) / 100;
	const f32 Gx = data->data.gyro_poll_val.x;
	const f32 Gy = data->data.gyro_poll_val.y;
	const f32 Gz = data->data.gyro_poll_val.z;

	const f32 phi = 	(180 * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / M_PI;
	const f32 theta = 	(180 * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / M_PI;
	const f32 rho = 	(180 * atanf(Az / sqrtf( powf(Ax, 2) + powf(Ay, 2)))) / M_PI;
	data->data.angle.x = ((1 - alpha) * (prev_angle_x + Gx * dt)) + (alpha * phi);
	data->data.angle.y = ((1 - alpha) * (prev_angle_y + Gy * dt)) + (alpha * theta);
	data->data.angle.z = ((1 - alpha) * (prev_angle_z + Gz * dt)) + (alpha * rho);
	prev_angle_x = data->data.angle.x;
	prev_angle_y = data->data.angle.y;
	prev_angle_z = data->data.angle.z;
}




void AHR_update(bmi085x* data)
{
	f32 ax = data->data.accel_poll_val.x * 9.81f;
	f32 ay = data->data.accel_poll_val.y * 9.81f;
	f32 az = data->data.accel_poll_val.z * 9.81f;
	f32 gx = data->data.gyro_poll_val.x * (180 / M_PI);
	f32 gy = data->data.gyro_poll_val.y * (180 / M_PI);
	f32 gz = data->data.gyro_poll_val.z * (180 / M_PI);


	f32 recipNorm;
	f32 s0, s1, s2, s3;
	f32 qDot1, qDot2, qDot3, qDot4;
	f32 _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		const f32 input = ax * ax + ay * ay + az * az;
		recipNorm = inverse_sqrt(input);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
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
	q0 += qDot1 * (1 / SAMPLE_FREQ);
	q1 += qDot2 * (1 / SAMPLE_FREQ);
	q2 += qDot3 * (1 / SAMPLE_FREQ);
	q3 += qDot4 * (1 / SAMPLE_FREQ);

	// Normalise quaternion
	recipNorm = inverse_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;

	data->data.quat.q0 = q0;
	data->data.quat.q1 = q1;
	data->data.quat.q2 = q2;
	data->data.quat.q3 = q3;
}


void eulerAngles(bmi085x* imu)
{
	const f32 q0_data = imu->data.quat.q0;
	const f32 q1_data = imu->data.quat.q1;
	const f32 q2_data = imu->data.quat.q2;
	const f32 q3_data = imu->data.quat.q3;

	const f32 yaw	= atan2f((2 * q1_data * q2_data - 2 * q0_data * q3_data), (2 * powf(q0_data, 2) + 2 * powf(q1_data, 2)  - 1));
	const f32 pitch = -asinf(2 * q1_data * q3_data + 2 * q0_data * q2_data);
	const f32 roll  = atan2f((2 * q2_data * q3_data - 2 * q0_data * q1_data), (2 * powf(q0_data, 2) + 2 * powf(q3_data, 2)- 1));

    imu->data.angle.z = yaw;
    imu->data.angle.y = pitch;
    imu->data.angle.x = roll;
}

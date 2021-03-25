#include <math.h>

#include <include/filters/complimentary_filter.h>

void complimentary_f_process(bmi085x* data)
{
	const f32 Ax = data->data.accel_poll_val.x;
	const f32 Ay = data->data.accel_poll_val.y;
	const f32 Az = data->data.accel_poll_val.z;
	// make sure your gyroscope values are in deg/s
	const f32 Gx = data->data.gyro_poll_val.x;
	const f32 Gy = data->data.gyro_poll_val.y;
	const f32 Gz = data->data.gyro_poll_val.z;


	//const f32 pitch = ((atan2f(Ax, sqrtf( powf(Ax, 2) + powf(Az, 2)))) * 180.0f) / M_PI;
	//const f32 roll = ((atan2f(Ay, sqrtf( powf(Ax, 2) + powf(Az, 2)))) * 180.0f) / M_PI;
	//const f32 yaw = ((atan2f(Az, sqrtf( powf(Ax, 2) + powf(Az, 2)))) * 180.0f) / M_PI;

	const f32 pitch = 	(180 * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / M_PI;
	const f32 roll = 	(180 * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / M_PI;
	const f32 yaw = 	(180 * atanf(Ax / sqrtf( powf(Ax, 2) + powf(Ay, 2) ))) / M_PI;
	data->data.angle.x = (1- alpha) * (prev_angle_x + Gx * dt) + alpha * pitch;
	data->data.angle.y = (1- alpha) * (prev_angle_y + Gy * dt) + alpha * roll;
	data->data.angle.z = (1- alpha) * (prev_angle_z + Gz * dt) + alpha * yaw;

	prev_angle_x = data->data.angle.x;
	prev_angle_y = data->data.angle.y;
	prev_angle_z = data->data.angle.z;
}

#include <math.h>

#include <include/filters/complimentary_filter.h>
#include <include/util/math_utility.h>

void complimentary_process(bmi085x* data)
{

	const f32 Ax = data->data.accel_poll_val.x;
	const f32 Ay = data->data.accel_poll_val.y;
	const f32 Az = data->data.accel_poll_val.z;
	const f32 Gx = data->data.gyro_poll_val.x;
	const f32 Gy = data->data.gyro_poll_val.y;
	const f32 Gz = data->data.gyro_poll_val.z;

	const f32 pitch = 	(180 * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / M_PI;
	const f32 roll = 	(180 * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / M_PI;
	const f32 yaw = 	(180 * atanf(Az / sqrtf( powf(Ax, 2) + powf(Ay, 2)))) / M_PI;
	data->data.compliment.x = ((1 - ALPHA) * (prev_angle_x + Gx * DT)) + (ALPHA * roll);
	data->data.compliment.y = ((1 - ALPHA) * (prev_angle_y + Gy * DT)) + (ALPHA * pitch);
	data->data.compliment.z = ((1 - ALPHA) * (prev_angle_z + Gz * DT)) + (ALPHA * yaw);
	prev_angle_x = data->data.compliment.x;
	prev_angle_y = data->data.compliment.y;
	prev_angle_z = data->data.compliment.z;
}

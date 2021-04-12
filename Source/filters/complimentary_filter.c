#include <math.h>

#include <include/filters/complimentary_filter.h>
#include <include/util/math_utility.h>


volatile f32 prev_angle_x = 0;
volatile f32 prev_angle_y = 0;
volatile f32 prev_angle_z = 0;

//void complimentary_process(bmi085x* data)
//{
//
//	const f32 Ax = data->data.accel_poll_val.x;
//	const f32 Ay = data->data.accel_poll_val.y;
//	const f32 Az = data->data.accel_poll_val.z;
//	const f32 Gx = data->data.gyro_poll_val.x;
//	const f32 Gy = data->data.gyro_poll_val.y;
//	const f32 Gz = data->data.gyro_poll_val.z;
//
//	const f32 pitch = 	(180 * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / M_PI;
//	const f32 roll = 	(180 * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / M_PI;
//	const f32 yaw = 	(180 * atanf(Az / sqrtf( powf(Ax, 2) + powf(Ay, 2)))) / M_PI;
//	data->data.angle.x = ((1 - ALPHA) * (prev_angle_x + Gx * DT)) + (ALPHA * roll);
//	data->data.angle.y = ((1 - ALPHA) * (prev_angle_y + Gy * DT)) + (ALPHA * pitch);
//	data->data.angle.z = ((1 - ALPHA) * (prev_angle_z + Gz * DT)) + (ALPHA * yaw);
//	prev_angle_x = data->data.angle.x;
//	prev_angle_y = data->data.angle.y;
//	prev_angle_z = data->data.angle.z;
//}

void complimentary_process(const f32 Ax, const f32 Ay, const f32 Az,
							const f32 Gx, const f32 Gy, const f32 Gz,
							f32 *roll, f32 *pitch, f32 *yaw)
{
	const f32 a_pitch = (180 * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / M_PI;
	const f32 a_roll = 	(180 * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / M_PI;
	const f32 a_yaw = 	(180 * atanf(Az / sqrtf( powf(Ax, 2) + powf(Ay, 2)))) / M_PI;

	*roll = ((1 - ALPHA) * (prev_angle_x + Gx * DT)) + (ALPHA * a_roll);
	*pitch = ((1 - ALPHA) * (prev_angle_y + Gy * DT)) + (ALPHA * a_pitch);
	*yaw = ((1 - ALPHA) * (prev_angle_z + Gz * DT)) + (ALPHA * a_yaw);

	prev_angle_x = *roll;
	prev_angle_y = *pitch;
	prev_angle_z = *yaw;
}

#include <math.h>

#include <include/filters/complimentary_filter.h>
#include <include/util/math_utility.h>


volatile f32 prev_angle_x = 0;
volatile f32 prev_angle_y = 0;
volatile f32 prev_angle_z = 0;


void complimentary_process(const f32 Ax, const f32 Ay, const f32 Az,
							const f32 Gx, const f32 Gy, const f32 Gz,
							f32 *roll, f32 *pitch, f32 *yaw)
{
	const f32 a_pitch = (180.0f * atanf(Ax / sqrtf( powf(Ay, 2) + powf(Az, 2) ))) / (f32) (M_PI);
	const f32 a_roll = 	(180.0f * atanf(Ay / sqrtf( powf(Ax, 2) + powf(Az, 2) ))) / (f32) (M_PI);
	const f32 a_yaw = 	(180.0f * atanf(Az / sqrtf( powf(Ax, 2) + powf(Ay, 2) ))) / (f32) (M_PI);

	*roll =  ((1 - ALPHA) * (prev_angle_x + Gx * DT)) + (ALPHA * a_roll);
	*pitch = ((1 - ALPHA) * (prev_angle_y + Gy * DT)) + (ALPHA * a_pitch);
	*yaw =   ((1 - ALPHA) * (prev_angle_z + Gz * DT)) + (ALPHA * a_yaw);

	prev_angle_x = *roll;
	prev_angle_y = *pitch;
	prev_angle_z = *yaw;
}

/*
 * math_utility.c
 *
 *  Created on: 26 Mar 2021
 *      Author: Patrick
 */


#include <include/util/math_utility.h>

void eulerAngles(quaternion_t q, f32* roll, f32* pitch, f32* yaw){

    *yaw = 		atan2f( (2 * q.q2 * q.q3 - 2 * q.q1 * q.q4), (2 * q.q1 * q.q1 + 2 * q.q2 * q.q2 - 1));
    *pitch = 	-asinf(2 * q.q2 * q.q4 + 2 * q.q1 * q.q3);
    *roll  = 	atan2f( (2 * q.q3 * q.q4 - 2 * q.q1 * q.q2), (2 * q.q1 * q.q1 + 2 * q.q4 * q.q4 - 1));
}

/*
 * math.h
 *
 *  Created on: 26 Mar 2021
 *      Author: Patrick
 */

#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <include/util/types.h>
#include <math.h>

#define RAD_TO_DEG_CONST	(f32) (180 / M_PI)
#define DEG_TO_RAD_CONST	(f32) 0.01745329251f

typedef struct {
  float         q1,q2,q3,q4;
} quaternion_t;

/*
 * Calculate the euler angles  of quaternions
 * @param q, the quaternion you want to convert to euler angles
 * @param roll, is the rotation around the x axis
 * @param pitch, is the rotation around the y axis
 * @param yaw, is the rotation around the z axis
 */
void eulerAngles(quaternion_t q, f32* roll, f32* pitch, f32* yaw);

#endif /* MATH_UTILITY_H_ */

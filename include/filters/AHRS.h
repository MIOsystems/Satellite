/*
 * AHRS.h
 *
 *  Created on: 30 Mar 2021
 *      Author: Patrick
 */

#ifndef AHRS_H_
#define AHRS_H_

#include <include/util/types.h>
#include <include/util/math_utility.h>
#include <include/sensor/imu/bmi085x.h>

#define DELTA			(f32) 0.01f
#define beta			(f32) 0.01f

static volatile f32 q0 = 1.0f;
static volatile f32 q1 = 0.0f;
static volatile f32 q2 = 0.0f;
static volatile f32 q3 = 0.0f;

void AHRS_update(bmi085x* data);
void eulerAngles(bmi085x* imu);

#endif /* AHRS_H_ */

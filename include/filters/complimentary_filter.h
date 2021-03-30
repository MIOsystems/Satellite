/*
 * complimentary_filter.h
 *
 *  Created on: 23 Mar 2021
 *      Author: Patrick
 */

#ifndef COMPLIMENTARY_FILTER_H_
#define COMPLIMENTARY_FILTER_H_

#include <include/sensor/imu/bmi085x.h>
#include <include/util/types.h>

#define beta			(f32) 0.01f
#define alpha			(f32) 0.1
#define SAMPLE_FREQ		(f32) 1000


static volatile f32 prev_angle_x = 0;
static volatile f32 prev_angle_y = 0;
static volatile f32 prev_angle_z = 0;

static volatile f32 q0 = 1.0f;
static volatile f32 q1 = 0.0f;
static volatile f32 q2 = 0.0f;
static volatile f32 q3 = 0.0f;


void complimentary_f_process(bmi085x* data);
void AHR_update(bmi085x* data);
void eulerAngles(bmi085x* imu);



#endif /* COMPLIMENTARY_FILTER_H_ */

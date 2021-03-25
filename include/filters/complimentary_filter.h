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

#define alpha	(f32) 0.1
#define dt 		(f32) 0.01


static volatile f32 prev_angle_x = 0;
static volatile f32 prev_angle_y = 0;
static volatile f32 prev_angle_z = 0;



void complimentary_f_process(bmi085x* data);


#endif /* COMPLIMENTARY_FILTER_H_ */

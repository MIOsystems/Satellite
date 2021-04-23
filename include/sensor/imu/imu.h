/*
 * imu.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef IMU_H_
#define IMU_H_

#include <include/util/types.h>
#include <include/satellite.h>
#include <include/util/math_utility.h>

// IMU driver includes
#ifdef BMI085
#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/imu/bmi085/bmi085a.h>
#include <include/sensor/imu/bmi085/bmi085g.h>
#endif

// Filters
#ifdef COMP_FILTER
#include <include/filters/complimentary_filter.h>
#endif
#ifdef MADGWICK_FILTER
#include <include/filters/MadgwickAHRS.h>
	quaternion_t quat;

	f32 r = 0.0f;
	f32 p = 0.0f;
	f32 y = 0.0f;
#endif

u8 imu_bmi085_init(bmi085x* imu);
u8 imu_poll(bmi085x* imu);

#endif /* INCLUDE_SENSOR_IMU_IMU_H_ */

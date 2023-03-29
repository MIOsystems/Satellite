/*
 * imu.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef IMU_H_
#define IMU_H_

#include <include/satellite.h>

#ifdef BMI085

#include <include/util/types.h>
#include <include/util/math_utility.h>

// IMU driver includes
#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/imu/bmi085/bmi085a.h>
#include <include/sensor/imu/bmi085/bmi085g.h>

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

u8 imuInit(bmi085x* imu);
u8 imuInitParam(bmi085x* imu, bmi085xSensor accel, bmi085xSensor gyro);
u8 imuPoll(bmi085x* imu);

#endif

#endif /* INCLUDE_SENSOR_IMU_IMU_H_ */

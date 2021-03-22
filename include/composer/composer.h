#ifndef COMPOSER_H_
#define COMPOSER_H_

#include <include/sensor/imu/bmi085x.h>
#include <include/sensor/imu/bmi085a.h>
#include <include/sensor/imu/bmi085g.h>

static bmi085x imu;
u8 composer_init();
u8 imu_init();
#endif
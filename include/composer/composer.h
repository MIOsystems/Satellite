#ifndef COMPOSER_H_
#define COMPOSER_H_

#include <include/sensor/imu/bmi085x.h>
#include <include/sensor/imu/bmi085a.h>
#include <include/sensor/imu/bmi085g.h>
#include <include/sensor/gps/gnss.h>

bmi085x imu;
ubx_frame_t gps_raw;
gps_values_t gps_packet;

u8 composer_init();
u8 imu_init();
#endif

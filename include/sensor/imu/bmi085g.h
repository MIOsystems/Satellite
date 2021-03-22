#ifndef BMI085G_H_
#define BMI085G_H_

#include <include/sensor/imu/bmi085x.h>
#include <include/sensor/imu/bmi085x_config.h>
#include <include/sensor/imu/bmi085x_opcode.h>

u8 bmi085g_init(bmi085x *bmi085);
u8 bmi085g_poll(bmi085x *bmi085);
u8 bmi085g_read_reg(const u8 addr, u8 *data);
u8 bmi085g_write_reg(const u8 addr, const u8 data);
#endif

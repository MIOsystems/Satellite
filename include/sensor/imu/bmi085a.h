#ifndef BMI085A_H_
#define BMI085A_H_

#include <include/sensor/imu/bmi085x.h>
#include <include/sensor/imu/bmi085x_opcode.h>
#include <include/util/types.h>





bmi085x_status_e bmi085a_init(bmi085x *bmi085);
bmi085x_status_e bmi085a_poll(bmi085x *bmi085);
bmi085x_status_e bmi085a_read_reg(const u8 addr, u8 *data);
bmi085x_status_e bmi085a_write_reg(const u8 addr, const u8 data);

#endif

#ifndef BMI085G_H_
#define BMI085G_H_

#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/imu/bmi085/bmi085x_opcode.h>

BMI085xStatus_e bmi085gInit(bmi085x *bmi085);
BMI085xStatus_e bmi085gPoll(bmi085x *bmi085);
BMI085xStatus_e bmi085gReadRegister(const u8 addr, u8 *data);
BMI085xStatus_e bmi085gWriteRegister(const u8 addr, const u8 data);
#endif

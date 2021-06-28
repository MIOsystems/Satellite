#ifndef BMI085A_H_
#define BMI085A_H_

#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/imu/bmi085/bmi085x_opcode.h>

#define RAW_TO_MS2(raw, power) (raw * 9.81f / 32768 * powf(2.0f, power))

BMI085xStatus_e bmi085aInit(bmi085x *bmi085);
BMI085xStatus_e bmi085aPoll(bmi085x *bmi085);
BMI085xStatus_e bmi085aReadRegister(const u8 addr, u8 *data);
BMI085xStatus_e bmi085aWriteToRegister(const u8 addr, const u8 data);

#endif

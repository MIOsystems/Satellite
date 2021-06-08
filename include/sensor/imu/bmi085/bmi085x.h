#ifndef BMI085X_H_
#define BMI085X_H_

#include <DAVE.h>
#include <include/math/statistic.h>
#include <include/math/vector.h>

#include <include/util/types.h>
#include <include/util/error.h>
#include <include/util/model.h>

#define CONCAT_RAW_VAL(msb, lsb) (i16) ((msb << 8) | lsb)



typedef struct 
{
	RegOperation_t pwr_mode;
	RegOperation_t meas_range;
	RegOperation_t bandwidth;
	RegOperation_t odr;
} bmi085xConfig;

typedef struct 
{
	u8 chip_id;
	bmi085xConfig config;
} bmi085xSensor;

// the structure that will be send
typedef struct 
{
	Vec3f_t accel_poll_val;
	Vec3f_t gyro_poll_val;
	AggregateStateFloat_t x_stat;
	AggregateStateFloat_t y_stat;
	AggregateStateFloat_t z_stat;
	Vec3f_t angle;
} bmi085xData;

typedef struct 
{
	bmi085xData data;
	bmi085xSensor gyro;
	bmi085xSensor acc;
} bmi085x;


void bmi085xInitGyroscope(bmi085x *bmi085);
void bmi085xInitAccelerometer(bmi085x *bmi085);

void bmi085xInitSensor(bmi085x *bmi085);
void bmi085xResetSensorData(bmi085x *bmi085);
#endif

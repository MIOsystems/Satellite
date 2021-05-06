#ifndef BMI085X_H_
#define BMI085X_H_

#include <DAVE.h>

#include <include/util/types.h>
#include <include/data/vector.h>
#include <include/data/statistic.h>
#include <include/util/error.h>
#include <include/util/model.h>

#define CONCAT_RAW_VAL(msb, lsb) (i16) ((msb << 8) | lsb)



typedef struct 
{
	RegOperation_t pwr_mode;
	RegOperation_t meas_range;
	RegOperation_t bandwidth;
	RegOperation_t odr;
} bmi085x_cfg;

typedef struct 
{
	u8 chip_id;
	bmi085x_cfg config;
} bmi085x_dev;

// the structure that will be send
typedef struct 
{
	vec3f accel_poll_val;
	vec3f gyro_poll_val;
	stat_aggregate_f x_stat;
	stat_aggregate_f y_stat;
	stat_aggregate_f z_stat;
	vec3f angle;
} bmi085x_data;

typedef struct 
{
	bmi085x_data data;
	bmi085x_dev gyro;
	bmi085x_dev acc;
} bmi085x;


void bmi085x_init_gyro(bmi085x *bmi085);
void bmi085x_init_acc(bmi085x *bmi085);

/**
 * This will initialize the main struct to the standard values.
 * The configuration will also be set as defined in the header file
 * TODO: make main header file
 * @param main struct that will be used for every function of bmi085 imu.
 */
void bmi085x_init(bmi085x *bmi085);
void bmi085x_reset_data(bmi085x *bmi085);
#endif

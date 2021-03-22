#include <include/sensor/imu/bmi085x.h>
#include <include/sensor/imu/bmi085x_opcode.h>

void bmi085x_init_acc(bmi085x *bmi085)
{
	bmi085x_dev accel = {
		.chip_id = 0, // this will be replaced later in the init function of the accelerometer
		.config = {
			.pwr_mode_addr = BMI085A_PWR_MODE_ADDR,
			.pwr_mode = BMI085A_PWR_MODE_ACTIVE,
			.meas_range_addr = BMI085A_RANGE_ADDR,
			.meas_range = BMI085A_RANGE_2G,
			.bandwidth_addr = BMI085A_CFG_ADDR,
			.bandwidth = 0, // TODO set this
			.output_data_rate_addr = BMI085A_CFG_ADDR,
			.ouput_data_rate = 0, //TODO set this

		}
	};
	bmi085->acc = accel;
}

void bmi085x_init_gyro(bmi085x *bmi085)
{
	bmi085x_dev gyro = {
		.chip_id = 0, // this will be replaced later in the init function of the gyroscope
		.config = {
			.pwr_mode = BMI085G_CFG_PWR_MODE_NRML,
			.meas_range = BMI085G_CFG_RANGE_125,
			.bandwidth = BMI085G_CFG_BANDWIDTH_1000_116,
			.ouput_data_rate = 0,
		}
	};

	bmi085->gyro = gyro;
}

void bmi085x_init(bmi085x *bmi085)
{
	// Setting all of the data values to zero
	bmi085x_data data = {
		.accel_poll_val = { 
			.x = 0,
			.y = 0,
			.z = 0
		},
		.gyro_poll_val = { 
			.x = 0, 
			.y = 0, 
			.z = 0
		},
		.x_stat = {
			.avg = 0,
			.max = 0,
			.min = 0,
		},
		.y_stat = {
			.avg = 0,
			.max = 0,
			.min = 0,
		},
		.z_stat = {
			.avg = 0,
			.max = 0,
			.min = 0,
		},
		.angle = {
			.x = 0,
			.y = 0,
			.z = 0,
		}
	};

	bmi085x_init_acc(bmi085);
	bmi085x_init_gyro(bmi085);
	bmi085->data = data;
}

void bmi085x_reset_data(bmi085x *bmi085)
{
	bmi085x_data data = {
				.accel_poll_val = { .x = 0, .y = 0, .z = 0 },
				.gyro_poll_val = { .x = 0, .y = 0, .z = 0 },
				.x_stat = { .avg = 0, .max = 0, .min = 0 },
				.y_stat = { .avg = 0, .max = 0, .min = 0 },
				.z_stat = { .avg = 0, .max = 0, .min = 0 },
				.angle = { .x = 0, .y = 0, .z = 0 }
			};
	bmi085->data = data;
}

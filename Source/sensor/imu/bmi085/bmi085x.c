#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/imu/bmi085/bmi085x_opcode.h>

void bmi085xInitAccelerometer(bmi085x *bmi085)
{
	bmi085xSensor accel = {
		.chip_id = 0, // this will be replaced later in the init function of the accelerometer
		.config = {
			.pwr_mode = {
				.reg_addr = BMI085A_PWR_MODE_ADDR,
				.instr = BMI085A_PWR_MODE_ACTIVE,
			},
			.meas_range = {
				.reg_addr = BMI085A_RANGE_ADDR,
				.instr = BMI085A_RANGE_16G,
			},
			.bandwidth = {
				.reg_addr = BMI085A_CFG_ADDR,
				.instr = 0,
			},
			.odr = {
				.reg_addr = BMI085A_CFG_ADDR,
				.instr = 0x8c,
			}
		}
	};
	bmi085->acc = accel;
}

void bmi085xInitGyroscope(bmi085x *bmi085)
{
	bmi085xSensor gyro = {
		.chip_id = 0,
		.config = {
			.pwr_mode = {
				.reg_addr = BMI085G_CFG_PWR_MODE_ADDR,
				.instr = BMI085G_CFG_PWR_MODE_NRML,
			},
			.meas_range = {
				.reg_addr = BMI085G_CFG_RANG_ADDR,
				.instr = BMI085G_CFG_RANGE_2000,
			},
			.bandwidth = {
				.reg_addr = BMI085G_CFG_BANDWIDTH_ADDR,
				//.instr = BMI085G_CFG_BANDWIDTH_100_32,
				.instr = BMI085G_CFG_BANDWIDTH_1000_116,
			},
			.odr = {
				.reg_addr = 0,
				.instr = 0,
			}
		}
	};

	bmi085->gyro = gyro;
}

void bmi085xInitData(bmi085x *bmi085)
{
	// Setting all of the data values to zero
	bmi085xData data = {
		.raw_accel_poll_val = {
			.x = 0,
			.y = 0,
			.z = 0
		},
		.raw_gyro_poll_val = {
			.x = 0,
			.y = 0,
			.z = 0
		},
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

	bmi085->data = data;
}

void bmi085xInitSensor(bmi085x *bmi085)
{
	bmi085xInitAccelerometer(bmi085);
	bmi085xInitGyroscope(bmi085);
	bmi085xInitData(bmi085);
}

void bmi085xResetSensorData(bmi085x *bmi085)
{
	bmi085xData data = {
				.raw_accel_poll_val = { .x = 0, .y = 0, .z = 0 },
				.raw_gyro_poll_val = { .x = 0, .y = 0, .z = 0 },
				.accel_poll_val = { .x = 0, .y = 0, .z = 0 },
				.gyro_poll_val = { .x = 0, .y = 0, .z = 0 },
				.x_stat = { .avg = 0, .max = 0, .min = 0 },
				.y_stat = { .avg = 0, .max = 0, .min = 0 },
				.z_stat = { .avg = 0, .max = 0, .min = 0 },
				.angle = { .x = 0, .y = 0, .z = 0 }
			};
	bmi085->data = data;
}

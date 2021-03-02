/*
 * BMI085.h
 *
 *  Created on: 16 Feb 2021
 *  Author: Patrick
 */

#ifndef BMI085_H_
#define BMI085_H_

#include <Header/Sensor.h>
#include <Header/Types.h>
#include <Header/Vector.h>
#include <Header/Satellite.h>

enum SPI_BMI_CS {
	BMI_CS_ACCEL = 0U,
	BMI_CS_GYRO
};

class BMI085 
{
	private:
		Vector3 gyro_data;
		Vector3 acc_data;
		StatisticVector axis_data_stat;
		Vector3 axis_data;
		u8 status;
		struct bmi08x_cfg {
			u8 pwr_mode;
			u8 range;
			u8 bandwidth;
			u8 odr;
		};
		struct bmi08x {
			u8 accel_id;
			u8 gyro_id;
			bmi08x_cfg accel_cfg;
			bmi08x_cfg gyro_cfg;
			i32 accel_values[3]; //x,y,z
			i32 gyro_values[3]; //x,y,z
		};

		bmi08x imu;

		u8 init_accel();
		u8 init_gyro();
		u8 write_accel_config();
		u8 write_gyro_config();
		u8 poll_accel();
		u8 poll_gyro();
	public:
		BMI085();
		u8 init();
		u8 poll();
		u8 read_reg(u8 addr, u8 *rx_buff, u8 size);
		u8 write_to_reg(u8 addr, const u8* data);
		void select(u8 chip);
		void wait();

};
#endif /* BMI085_H_ */

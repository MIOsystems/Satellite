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
#include <Header/Satellite.h>
#include <Header/BusHandler.h>

class BMI085 
{
	private:
		struct acc_stat_imu {
			u16 id;
			u16 avg;
			u16 max;
			u16 min;
			u64 amount_values;
			u64 total;
		};

		struct angle_imu {
			u16 x;
			u16 y;
			u16 z;
		};

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
			i32 accel_values[3];	//x,y,z
			i32 gyro_values[3]; 	//x,y,z
		};

		bmi08x imu;
		acc_stat_imu acc_x_stat; 
		acc_stat_imu acc_y_stat;
		acc_stat_imu acc_z_stat;
		angle_imu angle;

		BusHandler bus_handle;

		void init_accel();
		void init_gyro();
		void poll_accel();
		void poll_gyro();

		void calculate_stats(acc_stat_imu _imu);
	public:
		BMI085();
		void init();
		void poll();
		void write_a(u8 addr, const u8 data);
		void write_g(u8 addr, const u8 data);

};
#endif

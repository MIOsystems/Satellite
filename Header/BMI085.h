/*
 * BMI085.h
 *
 *  Created on: 16 Feb 2021
 *  Author: Patrick
 */

#ifndef BMI085_H_
#define BMI085_H_

#include <Header/Types.h>
#include <Header/Satellite.h>

class BMI085 
{
	private:
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
			f32 accel_values[3];	//x,y,z
			f32 gyro_values[3]; 	//x,y,z
		};

		struct acc_stat_imu {
			u32 amount_values;
			u32 total;
			f64 avg;
			u16 max;
			u16 min;
			u16 id;
		};


		struct bmi_packet {
			acc_stat_imu acc_x_stat;
			acc_stat_imu acc_y_stat;
			acc_stat_imu acc_z_stat;
			f32 angle[3];
		};


		bmi08x imu;
		u8 init_gyro();
		u8 init_accel();
		void poll_gyro();
		void poll_accel();
		void calculate_stats(acc_stat_imu *_imu);
		void calculate_angle();
		void calculate_complimentary_filter();
	public:
		BMI085();
		bmi_packet packet;
		u8 init();
		void poll();
		void write_g(u8 addr, const u8 data);
		void write_a(u8 addr, const u8 data);
		void read_a(u8 addr, u8 *data);
};
#endif

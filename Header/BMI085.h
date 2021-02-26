/*
 * BMI085.h
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef BMI085_H_
#define BMI085_H_

#include <Header/Sensor.h>
#include <Header/Types.h>
#include <Header/Vector.h>
#include <Header/Satellite.h>
enum {
	BMI_GYRO = 0,
	BMI_ACCEL,
};

class BMI085: public Sensor
{
	private:
		Vector3 gyro_data;
		Vector3 acc_data;
		StatisticVector axis_data_stat;
		Vector3 axis_data;

		u8 poll_gyro();
		u8 poll_accelo();
		void reg_to_val(i32 *data, u8 *rx_buff);
	public:
		BMI085();
		u8 init() override;
		u8 poll() override;
		u8 select(u8 chip) override;
		u8 write(u8 addr, u8 data) override;
		char* to_string() override;
};
#endif /* BMI085_H_ */

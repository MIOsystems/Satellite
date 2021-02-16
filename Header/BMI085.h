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

namespace Satellite {

class BMI085 : public Sensor {
	private:
		// DATA
		const u8 BMI_A_DATA_OPCODE[6] = { 0x12,0x13,0x14,0x15,0x16,0x17 };
		const u8 BMI_G_DATA_OPCODE[6] = { 0x02,0x03,0x04,0x05,0x06,0x07 };
		Vector3* acc_data;
		StatisticVector* axis_data_stat;
		Vector3* axis_data;
	public:
		BMI085();
		u8 init();
		u8 poll();
		u8 select(XMC_GPIO_PORT_t* port, u8 pin);
		u8 write(u8 addr, u16 *data);
};

} /* namespace Satellite */

#endif /* BMI085_H_ */

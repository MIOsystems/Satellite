/*
 * Sensor.h
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include <DAVE.h>
#include <Header/Types.h>
class Sensor
{
	public:
		/**
		 * Initialize the hardware, this is not the constructor
		 * initialize the variables you need in the constructor
		 * @return status code
		 */
		virtual u8 init() = 0;

		/**
		 * Polls data, assumption is that you write and read
		 * @return status code
		 */
		virtual u8 poll() = 0;

		/**
		 * Select chip
		 * @return status code
		 */
		virtual u8 select(XMC_GPIO_PORT_t* port, u8 pin) = 0;

		/**
		 * Write opcode to data
		 * @return status code
		 */
		virtual u8 write(u8 addr, u16 *data) = 0;
};
#endif /* SENSOR_H_ */

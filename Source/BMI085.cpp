/*
 * BMI085.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#include <Header/BMI085.h>
#include <Header/Satellite.h>
#include <DAVE.h>
namespace Satellite {

BMI085::BMI085() {
	this->acc_data = new Vector3(0.0f, 0.0f, 0.0f);
	this->axis_data_stat = new StatisticVector(0.0f, 0.0f, 0.0f);
	this->axis_data = new Vector3(0.0f, 0.0f, 0.0f);

}

u8 BMI085::init() {
	u32 baud_rate = SPI_MASTER_1.config->channel_config->baudrate;
	u8 status = SPI_MASTER_SetBaudRate(&SPI_MASTER_1, baud_rate);
	// Check if setting baud rate went correctly
	if(status == SPI_MASTER_STATUS_SUCCESS) 
	{
		return status;
	}

	// Select gyroscope first
	//status = select()
	// Softreseting the BMI sensor
	//status = write();
	return 0;

}
u8 BMI085::poll() {
	return 0;
}
u8 BMI085::select(XMC_GPIO_PORT_t* _port, u8 _pin) {
	XMC_GPIO_SetOutputHigh(_port, _pin);
	return 0;
}


u8 BMI085::write(u8 addr, u16 *data) {
	return 0;
}

} /* namespace Satellite */

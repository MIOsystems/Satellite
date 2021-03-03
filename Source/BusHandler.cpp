/*
 * BusHandler.cpp
 *
 *  Created on: 3 Mar 2021
 *      Author: Patrick
 */

#include <Header/Satellite.h>
#include <Header/BusHandler.h>

BusHandler::BusHandler() {

}

void BusHandler::set(u16 bus_number)
{
	u16 mask = BUS_IO_Read(this->bus_handle);
	mask |= (1 << (bus_number));
	BUS_IO_Write(bus_handle, mask);
}

void BusHandler::reset(u16 bus_nr)
{
	u16 mask = BUS_IO_Read(this->bus_handle);
	if((bus_nr == BMI_CS_A_PIN) | (bus_nr == BMI_CS_G_PIN))
	{
		mask |= (1 << BMI_CS_A_PIN) |
				(1 << BMI_CS_G_PIN);
	}
	mask &= ~(1 << (bus_nr));
	BUS_IO_Write(bus_handle, mask);
}

/*
 * BusHandler.h
 *
 *  Created on: 3 Mar 2021
 *      Author: Patrick
 */

#ifndef HEADER_BUSHANDLER_H_
#define HEADER_BUSHANDLER_H_

#include <DAVE.h>
#include <Header/Types.h>

class BusHandler {
	private:
		BUS_IO_t* const bus_handle = &SPI_BUS;
	public:
		BusHandler();
		void set(u16 bus_number);
		void reset(u16 bus_nr);
};

#endif /* HEADER_BUSHANDLER_H_ */

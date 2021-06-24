/*
 * altimeter.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <include/sensor/altimeter/altimeter.h>
#include <include/util/types.h>

#ifdef ALTIMETER_SF30
#include <include/sensor/altimeter/SF30/sf30.h>
#endif

void altimeterInit(AltimeterData_t* data)
{
#ifdef ALTIMETER_SF30
	sf30_init(data);
#endif
}

void altimeterUpdate(AltimeterData_t* data)
{
	DIGITAL_IO_SetOutputLow(&LED_GREEN);
#ifdef ALTIMETER_SF30
	sf30_update(data);


#endif
	DIGITAL_IO_SetOutputHigh(&LED_GREEN);
}


#ifndef RUN_HW_VALIDATION
//void rs422_interrupt(void)
//{
//	sf30_rx_handle();
//}
#endif

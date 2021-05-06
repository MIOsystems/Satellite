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

void altimeter_init(AltimeterData_t* data)
{
#ifdef ALTIMETER_SF30
	sf30_init(data);
#endif
}

void altimeter_update(AltimeterData_t* data)
{
#ifdef ALTIMETER_SF30
	sf30_update(data);
#endif
}


#ifndef RUN_HW_VALIDATION
//void rs422_interrupt(void)
//{
//	sf30_rx_handle();
//}
#endif

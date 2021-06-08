/*
 * IO35.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <include/sensor/proximity/IO35/proximity_IO35.h>

#include <DAVE.h>

volatile u16 prox_poll_cur_val;

void proximityIo35Init(proximity_switch_t* data)
{
	prox_poll_cur_val = 0;
	data->distance = 0.0;
	ADC_MEASUREMENT_StartConversion(&AI);
}

void proximityIo35Update(proximity_switch_t* data)
{
	data->distance = prox_poll_cur_val;
}


void analog_handler(void)
{
	prox_poll_cur_val = ADC_MEASUREMENT_GetDetailedResult(&ADC_MEASUREMENT_Channel_B_handle);
}

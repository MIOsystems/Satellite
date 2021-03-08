/*
 * Utility.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#include <DAVE.h>

#include <Header/Satellite.h>
#include <Header/Utility.h>


Utility::Utility()
{
	// TODO Auto-generated constructor stub

}

void Utility::delay(u32 u_sec)
{
	u32 delay_cnt = u_sec * 100;
	TIMER_ClearEvent(&DELAY_TIMER_1);
	TIMER_SetTimeInterval(&DELAY_TIMER_1, delay_cnt);
	TIMER_Start(&DELAY_TIMER_1);

	while (!TIMER_GetInterruptStatus(&DELAY_TIMER_1)){}

	TIMER_Stop(&DELAY_TIMER_1);
	TIMER_Clear(&DELAY_TIMER_1);
}


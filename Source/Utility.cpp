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

void Utility::delay(u32 cycles)
{
	for(u32 i = 0; i < cycles; i++) {
		__NOP();
	}
}

void Utility::delay_ms(u32 ms)
{
	u32 cycles_ms = (144 * 1000) * ms;
	delay(cycles_ms);
}

void Utility::delay_sec(u32 sec)
{
	uint32_t ms = sec / 1000;
	delay_ms(ms);
}

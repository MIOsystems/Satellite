#include <DAVE.h>
#include <include/util/delay.h>
#include <include/satellite.h>

void delaySec(u32 sec)
{	
	// 1 sec = 1000 ms
	u32 ms = sec * 1000;
	delayMs(ms);
}

void delayMs(u32 ms)
{
	u32 amount_of_cycles = ONEMSDELAY * ms;

	while(amount_of_cycles--)
	{
		__NOP(); // No operation
	}
}
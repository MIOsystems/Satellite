/*
 * Utility
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_UTILITY_
#define HEADER_UTILITY_
#include <Header/Types.h>

class Utility
{
	public:
		Utility();
		static void delay(u32 cycles);
		static void delay_ms(u32 ms);
		static void delay_sec(u32 sec);
};
#endif /* HEADER_UTILITY_ */

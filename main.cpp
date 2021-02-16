/*
 * main.c
 *
 *  Created on: 2020 Aug 27 09:10:51
 *  Author: Patrick
 */
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

int main(void)
{
	DAVE_STATUS_t status;

	status = DAVE_Init();           /* Initialization of DAVE APPs  */

	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U)
		{

		}
	}

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U)
	{


	}
}

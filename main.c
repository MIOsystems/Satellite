/*
 * main.c
 *
 *  Created on: 2020 Aug 27 09:10:51
 *  Author: Arthur
 */
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdint.h>
#include <BMI085.h>

BMI085 bmi085;


int32_t initialize() {
	int32_t status;
	status = BMI_init(&bmi085);
	if(status != SPI_MASTER_STATUS_SUCCESS) {
		return -1;
	}


	return 1;

}
int main(void)
{
	DAVE_STATUS_t status;

	status = DAVE_Init();           /* Initialization of DAVE APPs  */
	initialize();

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

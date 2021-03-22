#ifndef ERROR_H_
#define ERROR_H_

/**
 *  Header file for all of the enum error codes
 */

typedef enum
{
	BMI085X_SUCCESS,
	BMI085X_INIT_FAILURE,
	BMI085X_INVALID_CHIP_ID,
	BMI085X_READ_FAILURE,
	BMI085X_WRITE_FAILURE,
	BMI085X_POLL_FAILURE,
} bmi085x_status_e;

#endif

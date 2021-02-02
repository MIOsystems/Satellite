/*
 * Utility.h
 *
 *  Created on: 30 Jan 2021
 *      Author: Patrick
 */
#ifndef BMI085_H_
#define BMI085_H_


typedef enum  {
	BMI_A_NORMAL,
	BMI_A_SUSPEND
} power_modes_accel_e;

typedef enum power_modes_gyro {
	BMI_G_NORMAL,
	BMI_G_SUSPEND,
	BMI_G_DEEP_SUSPEND
} power_modes_gyro_e;

typedef struct {
	power_modes_accel_e mode;
	uint16_t data[3]; // X, Y , Z
} BMI085_accelerometer;

typedef struct {
	power_modes_gyro_e mode;
	uint16_t data[3]; // X, Y , Z
} BMI085_gyroscope;


typedef struct {
	BMI085_gyroscope gyroscope;
	BMI085_accelerometer accelerometer;
} BMI085;


/**
 * Initialize sensor
 */
int32_t BMI_init(BMI085* sensor);

/**
 * Sets the mode of the accelerometer of the BMI085
 * @MODE NORMAL or SUSPEND. see the ENUM in the header file
 */
int32_t BMI_set_accel_mode(power_modes_accel_e mode, BMI085 *sensor);

/**
 * Sets the mode of the gyroscope of the BMI085
 * @MODE NORMAL, SUSPEND, DEEP SUSPEND. see the ENUM in the header file
 */
int32_t BMI_set_gyro_mode(power_modes_gyro_e mode, BMI085 *sensor);

int32_t BMI_poll(BMI085 *sensor);

#endif

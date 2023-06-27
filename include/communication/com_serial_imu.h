/*
 * com_serial_imu.h
 *
 *  Created on: 28 Mar 2023
 *      Author: Kenley Strik
 */

#ifndef COM_SERIAL_IMU_H_
#define COM_SERIAL_IMU_H_

#include "include/satellite.h"

#ifdef IMU_COM

#include <DAVE.h>

#include "include/sensor/imu/imu.h"
#include "include/hardware/fram.h"

#define COM_SERIAL_IMU_BUFFER_SIZE 3

#define START_BYTE_1 0xFO
#define START_BYTE_2 0x0F

typedef enum
{
    RECEIVING_STARTBYTE_1 = 0,
    RECEIVING_STARTBYTE_2 = 1,
    RECEIVING_PAYLOAD = 2
} com_serial_imu_receive_state;

typedef enum
{
	COM_SERIAL_IMU_ERR_OK = 0,
	COM_SERIAL_IMU_ERR_READ_ERROR = 1,
	COM_SERIAL_IMU_ERR_WRITE_ERROR = 2
} com_serial_imu_err_t;

typedef enum
{
	IMU_DATA = 0,
	ACKNOWLEGDEMENT = 1
} com_serial_imu_message_type;

typedef enum
{
	ACCELEROMETER = 0,
	GYRO = 1
} com_serial_imu_chip;

typedef struct
{
	uint8_t chip;
	uint8_t registerAddress;
	uint8_t registerValue;
} com_serial_imu_command;

typedef struct
{
	uint8_t startByte1;
	uint8_t startByte2;
	uint8_t messageType;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} com_serial_imu_data_packet;

typedef struct
{
	uint8_t startByte1;
	uint8_t startByte2;
	uint8_t messageType;
	uint8_t chip;
	uint8_t registerAddress;
	uint8_t registerValue;
	uint8_t ack;
} com_serial_imu_command_ack;

typedef struct
{
	uint8_t accelRangeRegisterValue;
	uint8_t accelBandwidthRegisterValue;
	uint8_t gyroRangeRegisterValue;
	uint8_t gyroBandwidthRegisterValue;
} com_serial_imu_fram_data;

int8_t imu_serial_com_init(bmi085x* imu, bool haltInterrupts);
void imu_serial_com_reset_recv();

com_serial_imu_err_t imu_serial_com_recv();
com_serial_imu_err_t imu_serial_com_write(uint8_t* data, uint32_t size);
void imu_serial_com_packet_received_handle();
bool imu_serial_com_handle_packet();

void imu_serial_com_send_measurements(bmi085x* imu);
bool imu_serial_com_validate_fram_data(com_serial_imu_fram_data* framData);
bool imu_serial_com_validate_accelerometer_bandwidth(uint8_t byte);

void imu_serial_com_reset_recv_buffer_pos();

#endif
#endif

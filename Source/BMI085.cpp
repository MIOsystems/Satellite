/*
 * BMI085.cpp
 *
 *  Created on: 16 Feb 2021
 *  Author: Patrick
 */

#include <DAVE.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Header/BMI085.h>
#include <Header/Satellite.h>
#include <Header/Utility.h>

BMI085::BMI085()
{
	this->imu = {	0,  // ACCELEROMETER chip ID
					0,	  // GYROSCOPE chip ID
					{ 0, 0, 0, 0 }, // ACCELEROMETER CONFIG
					{ 0, 0, 0, 0 }, // GYROSCOPE CONFIG
					{ 0, 0, 0 }, // ACCELEROMETER RAW VALUES F32 raw msb/lsb values xyz
					{ 0, 0, 0 }, // GYROSCOPE RAW VALUES F32 raw msb/lsb values xyz
	};

	this->packet = {
			{ 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 1},
			{ 0, 0, 0, 0, 0, 2}
	};

}

u8 BMI085::init()
{
	u8 status = 0;
	status = this->init_accel();
	if(status != 0)
		return status;

	status = this->init_gyro();
	return status;

}

u8 BMI085::init_gyro()
{
	// SW RESET
	this->write_g(BMI085_G_RST_ADDR, BMI085_G_RST_DATA);
	Utility::delay(50000); // 50 ms

	u8 chip_id = 0;
	this->read_g(0x00, &chip_id);
	if(chip_id != 0x0F)
		return 1;

	this->imu.gyro_id = chip_id;

	this->write_g(BMI085_G_BW_ADDR, BMI085_G_BW_DATA);
	this->write_g(BMI085_G_RANGE_ADDR, BMI085_G_RANGE_DATA);
	return 0;
}

u8 BMI085::init_accel()
{
	XMC_USIC_CH_RXFIFO_Flush(BMI_SPI_MASTER_1.channel);
	while(!SPI_MASTER_IsRxFIFOEmpty(&BMI_SPI_MASTER_1)) SPI_MASTER_GetReceivedWord(&BMI_SPI_MASTER_1);

	// Setting the accelerometer in SPI Mode
	DIGITAL_IO_SetOutputHigh(&CS_A);
	Utility::delay(1);
	// Turn the accelerometer on
	this->write_a(BMI085_A_PWR_CTRL_ADDR, BMI085_A_PWR_CTRL_DATA);
	Utility::delay(50000); // 50 ms

	this->write_a(BMI085_A_RANGE_ADDR, BMI085_A_RANGE_DATA);
	Utility::delay(50000); // 50 ms

	// Put the accelerometer in active mode
	this->write_a(BMI085_A_PWR_CONF_ADDR, BMI085_A_PWR_CONF_DATA);
	Utility::delay(50000); // 50 ms

	// Getting the chip id should be 0x1F which is the reset value
	u8 chip_id = 0;
	this->read_a(0x00, &chip_id);
	if(chip_id != 0x1F)		return 1;

	this->imu.accel_id = chip_id;

	return 0;
}

void BMI085::poll()
{
	this->poll_accel();
	this->poll_gyro();
	this->calculate_stats(&this->packet.acc_x_stat);
	this->calculate_stats(&this->packet.acc_y_stat);
	this->calculate_stats(&this->packet.acc_z_stat);
	//this->apply_gyro_angles();
	this->calculate_complimentary_filter();
}


void BMI085::write_g(u8 addr, const u8 data)
{
	u8 rx_buff[3];
	uint8_t tx[]=
	{
		addr,
		data,
	};

	u8 tx_len = sizeof(tx) / sizeof( (tx)[0]);
	DIGITAL_IO_SetOutputLow(&CS_G);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx, rx_buff, tx_len);
	DIGITAL_IO_SetOutputHigh(&CS_G);
}


void BMI085::write_a(u8 addr, const u8 data)
{
	u8 rx_buff[3];
	uint8_t tx[]=
	{
		addr,
		data,
	};
	u8 tx_len = sizeof(tx) / sizeof( (tx)[0]);
	DIGITAL_IO_SetOutputLow(&CS_A);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx, rx_buff, tx_len);
	DIGITAL_IO_SetOutputHigh(&CS_A);
}

void BMI085::poll_gyro()
{
	u8 lsb = 0;
	u8 msb = 0;
	i16 msb_lsb = 0;
	int counter = 0;
	f32 half_scale = ((float)(1 << 16) / 2.0f);
	f32 range_dps = 125;
	u8 rx_buff[7] = { 0 };
	u8 tx_buff[7] = {
		0x82,
		0xFF,
		0xFF,
		0xFF,
		0xFF,
		0xFF,
		0xFF
	};

	DIGITAL_IO_SetOutputLow(&CS_G);


	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 7);
	DIGITAL_IO_SetOutputHigh(&CS_G);

	for(int i = 1; i < 7; i = i + 2) {
		lsb = rx_buff[i];
		msb = rx_buff[i + 1];
		msb_lsb = (i16) ((msb << 8 ) | lsb); // raw data

		// degrees per second
		this->imu.gyro_values[counter] = msb_lsb / range_dps;
		counter++;
	}
}

/**
 * To read the accelerometer values in SPI Mode, the user has to read 7 bytes.
 * Starting from address 0x12 (ACC data). From these bytes the user must
 * discard the first byte and finds the acceleration information in byte #2-7
 */
void BMI085::poll_accel()
{

	u8 rx_buff[8] = { 0 };
	u8 tx_buff[8] = {0x92,
						0xFF,
						0xFF,
						0xFF,
						0xFF,
						0xFF,
						0xFF,
						0xFF};
	u8 lsb = 0;
	u8 msb = 0;
	i16 msb_lsb = 0;
	int counter = 0;

	DIGITAL_IO_SetOutputLow(&CS_A);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 8);
//	while(BMI_SPI_MASTER_1.runtime->rx_busy || BMI_SPI_MASTER_1.runtime->tx_busy);
	//Utility::delay(10);
	DIGITAL_IO_SetOutputHigh(&CS_A);
	Utility::delay(2);

	for(int i = 2; i < 8; i = i + 2) {
		lsb = rx_buff[i];
		msb = rx_buff[i + 1];
		msb_lsb = (i16) ((msb << 8 ) | lsb); // raw value
		// TODO CHANGE RANGE
		this->imu.accel_values[counter] = ((msb_lsb / 32768.0f) * 1000.0f * 2) / 1000;
		counter++;
	}
}

void BMI085::calculate_stats(acc_stat_imu* _imu)
{
	_imu->amount_values++;
	const int id = _imu->id;
	_imu->total += this->imu.accel_values[id];
	// check if it is the first value
	if(_imu->amount_values == 1)
	{
		_imu->max = this->imu.accel_values[id];
		_imu->min = this->imu.accel_values[id];
		// If we divide it already we will get division error
		_imu->avg = this->imu.accel_values[id];
	} else {
		// check if the new value is the max
		if(_imu->max < this->imu.accel_values[id])
		{
			_imu->max = this->imu.accel_values[id];
		}
		// If it is a new max value then don't check if its a new minimum value, but if it is not a new max value check the old value
		else if(_imu->min > this->imu.accel_values[id]) {
			_imu->min =  this->imu.accel_values[id];
		}
		// always add calculate the new average no matter if there is a new minimum or max
		_imu->avg = ( _imu->total / _imu->amount_values);
	}
}

/*
 * SOURCE: https://gunjanpatel.wordpress.com/2016/07/07/complementary-filter-design/
 * https://www.instructables.com/Angle-measurement-using-gyro-accelerometer-and-Ar/
 *
 */

void BMI085::calculate_complimentary_filter()
{
	f32 dt = 0.001;
	// Storing it in variables for readability
	f32 gyro_x = this->imu.gyro_values[0];
	f32 gyro_y = this->imu.gyro_values[1];
	f32 gyro_z = this->imu.gyro_values[2];
	f32 accel_x = this->imu.accel_values[0];
	f32 accel_y = this->imu.accel_values[1];
	f32 accel_z = this->imu.accel_values[2];

	//f32 gyro_x_with_old_angle = this->packet.angle[0] + gyro_x;
	//f32 gyro_y_with_old_angle = this->packet.angle[1] + gyro_y;
	f32 gyro_z_with_old_angle = this->packet.angle[2] + gyro_z;
	//f32 gyro_x_dt = gyro_x_with_old_angle * dt;
	//f32 gyro_y_dt = gyro_y_with_old_angle * dt;
	f32 angle_acc_z = (atan2f(accel_y, accel_z)) * 180 / M_PI;
//	angle_x += gyro_y * dt;
	this->packet.angle[0] = accel_x*90;
	this->packet.angle[1] = accel_y*90;
	this->packet.angle[2] = accel_z*90;
	//f32 angle_acc_x = (atan2f(accel_y, accel_z));
	//f32 angle_acc_y = (atan2f(accel_x, accel_z));


	//this->packet.angle[0] = (0.98 * gyro_x_dt) + (0.02 * angle_acc_x);
	//this->packet.angle[1] = (0.98 * gyro_y_dt) + (0.02 * angle_acc_y);
//	this->packet.angle[2] = (0.98 * this->packet.angle[2]) + (0.02 * angle_acc_z);
}

// ACCELEORMETER READS ARE DIFFERENT, ONE DUMMY BYTE THEN TRUE DATA
void BMI085::read_a(u8 addr, u8 *data)
{
	u8 tx_buff[3] = { (addr | 0x80), 0x00, 0x00 };
	u8 rx_buff[3];

	DIGITAL_IO_SetOutputLow(&CS_A);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 3);
	while(BMI_SPI_MASTER_1.runtime->rx_busy || BMI_SPI_MASTER_1.runtime->tx_busy);
	DIGITAL_IO_SetOutputHigh(&CS_A);
	Utility::delay(2);

	*data = rx_buff[2];
}

void BMI085::read_g(u8 addr, u8 *data)
{
	u8 tx_buff[2] = { (addr | 0x80), 0x00 };
	u8 rx_buff[2];

	DIGITAL_IO_SetOutputLow(&CS_G);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 3);
	while(BMI_SPI_MASTER_1.runtime->rx_busy || BMI_SPI_MASTER_1.runtime->tx_busy);
	DIGITAL_IO_SetOutputHigh(&CS_G);
	Utility::delay(2);

	*data = rx_buff[1];
}

void BMI085::reset()
{
	this->packet = {
			{ 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 1},
			{ 0, 0, 0, 0, 0, 2}
	};
}

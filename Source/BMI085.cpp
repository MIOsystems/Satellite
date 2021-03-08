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
	// Setting the accelerometer in SPI Mode
	DIGITAL_IO_SetOutputHigh(&CS_A);
	Utility::delay(1);
	DIGITAL_IO_SetOutputLow(&CS_A);

	// Resetting the accelerometer
	this->write_a(BMI085_A_RST_ADDR, BMI085_A_RST_DATA);
	Utility::delay(50000); // 50 ms

	// Getting the chip id should be 0x1F which is the reset value
	u8 chip_id = 0;
	this->read_a(0x00, &chip_id);
	if(chip_id != 0x1F)
		return 1;

	this->imu.accel_id = chip_id;


	// Configuring the range to 16g
	this->write_a(BMI085_A_RANGE_ADDR, BMI085_A_RANGE_DATA);
	Utility::delay(50000); // 50 ms

	// Put the accelerometer in active mode
	this->write_a(BMI085_A_PWR_CONF_ADDR, BMI085_A_PWR_CONF_DATA);
	Utility::delay(50000); // 50 ms
	// Turn the accelerometer on
	this->write_a(BMI085_A_PWR_CTRL_ADDR, BMI085_A_PWR_CTRL_DATA);
	Utility::delay(50000); // 50 ms

	return 0;
}

void BMI085::poll()
{
	this->poll_accel();
	this->poll_gyro();
	this->calculate_stats(&this->packet.acc_x_stat);
	this->calculate_stats(&this->packet.acc_y_stat);
	this->calculate_stats(&this->packet.acc_z_stat);
	this->calculate_complimentary_filter();
}


void BMI085::write_g(u8 addr, const u8 data)
{
	uint8_t tx[]=
	{
		addr,
		data,
	};

	u8 tx_len = sizeof(tx) / sizeof( (tx)[0]);
	DIGITAL_IO_SetOutputLow(&CS_G);
	SPI_MASTER_Transmit(&BMI_SPI_MASTER_1, tx, tx_len);
	while (BMI_SPI_MASTER_1.runtime->tx_busy);
	DIGITAL_IO_SetOutputHigh(&CS_G);
	Utility::delay(2);
}


void BMI085::write_a(u8 addr, const u8 data)
{
	uint8_t tx[]=
	{
		addr,
		data,
	};
	u8 tx_len = sizeof(tx) / sizeof( (tx)[0]);
	DIGITAL_IO_SetOutputLow(&CS_A);
	SPI_MASTER_Transmit(&BMI_SPI_MASTER_1, tx, tx_len);
	while (BMI_SPI_MASTER_1.runtime->tx_busy);
	DIGITAL_IO_SetOutputHigh(&CS_A);
}

void BMI085::poll_gyro()
{
	u8 lsb = 0;
	u8 msb = 0;
	i16 msb_lsb = 0;
	int counter = 0;
    f32 half_scale = ((f32)(1 << 16) / 2.0f);
    f32 range_dps = 125;
    f32 opcode_range_data = 0x04;
	u8 rx_buff[7] = { 0 };
	u8 tx_buff[7] = {
		0x02 | 0x80,
		0x03 | 0x80,
		0x04 | 0x80,
		0x05 | 0x80,
		0x06 | 0x80,
		0x07 | 0x80,
		0xFF,
	};

	DIGITAL_IO_SetOutputLow(&CS_G);


	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 7);

	while(BMI_SPI_MASTER_1.runtime->rx_busy || BMI_SPI_MASTER_1.runtime->tx_busy);

	DIGITAL_IO_SetOutputHigh(&CS_G);

	Utility::delay(2);

	 // lsb_to_dps(raw_val, range_dps, 16);

	for(int i = 0; i < 6; i = i + 2) {
		lsb = rx_buff[i];
		msb = rx_buff[i + 1];
		msb_lsb = (i16) ((msb << 8 ) | lsb); // raw data
		 /* Converting lsb to degree per second for 16 bit gyro at 125 dps range. */
		this->imu.gyro_values[counter] = (range_dps / ((half_scale) + opcode_range_data)) * (msb_lsb);

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
	u8 tx_buff[8] = {	(0x12 | 0x80),
						(0x13 | 0x80),
						(0x14 | 0x80),
						(0x15 | 0x80),
						(0x16 | 0x80),
						(0x17 | 0x80),
						0xFF,
				 		0xFF};
	int counter = 0;
	u8 range_opcode_data = 0x00;
	f32 power_of_range = 4.0f; // 2^(0x00 + 1)

	DIGITAL_IO_SetOutputLow(&CS_A);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, 8);
	while(BMI_SPI_MASTER_1.runtime->rx_busy || BMI_SPI_MASTER_1.runtime->tx_busy);
	DIGITAL_IO_SetOutputHigh(&CS_A);

	// raw_values
	i16 raw_x = (i16) ((rx_buff[3] << 8 ) | rx_buff[2]); // z
	i16 raw_y = (i16) ((rx_buff[5] << 8 ) | rx_buff[4]); // y
	i16 raw_z = (i16) ((rx_buff[7] << 8 ) | rx_buff[6]); // z

	// converting it to mg
	this->imu.accel_values[0] = ((-8000.0f) / 32768.0f) * 1000.0f * power_of_range;
	this->imu.accel_values[1] = ((8000.0f) / 32768.0f) * 1000.0f * power_of_range;
	this->imu.accel_values[2] = ((15000.0f) / 32768.0f) * 1000.0f * power_of_range; // z must be 1000

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
 *
 */
void BMI085::calculate_complimentary_filter()
{
	this->packet.angle[0] = 0.98 * (this->packet.angle[0] + this->imu.gyro_values[0]) + (0.02 *  this->imu.gyro_values[0]); // x
	this->packet.angle[1] = 0.98 * (this->packet.angle[1] + this->imu.gyro_values[1]) + (0.02 *  this->imu.gyro_values[1]); // y
	this->packet.angle[2] = 0.98 * (this->packet.angle[2] + this->imu.gyro_values[2]) + (0.02 *  this->imu.gyro_values[1]); // z
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

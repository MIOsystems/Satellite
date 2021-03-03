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

#include <Header/BMI085.h>
#include <Header/Satellite.h>
#include <Header/Utility.h>
#include <Header/BusHandler.h>

BMI085::BMI085()
{
	this->imu = {	0,  // ACCELEROMETER ID
					0,	  // GYROSCOPE ID
					{ 0, 0, 0, 0 }, // ACCELEROMETER CONFIG
					{ 0, 0, 0, 0 }, // GYROSCOPE CONFIG
					{ 0, 0, 0 }, // ACCELEROMETER RAW VALUES
					{ 0, 0, 0 }, // GYROSCOPE RAW VALUES
	};

	this->acc_x_stat = { 0, 0, 0, 0, 0, 0};
	this->acc_y_stat = { 1, 0, 0, 0, 0, 0};
	this->acc_z_stat = { 2, 0, 0, 0, 0, 0};
	this->angle = { 0, 0, 0};
}

void BMI085::init()
{
	this->init_accel();
	this->init_gyro();
}

void BMI085::poll()
{
	this->poll_accel();
	this->poll_gyro();
}

void BMI085::write_a(u8 addr, const u8 data)
{
	u8 tx[]=
	{
		addr,
		data,
	};
	this->bus_handle.reset(BMI_CS_A_PIN);
	if( SPI_MASTER_STATUS_SUCCESS == SPI_MASTER_Transmit(&BMI_SPI_MASTER_1, tx,  sizeof(tx) / sizeof( (tx)[0]) ))
	{
		while (BMI_SPI_MASTER_1.runtime->rx_busy){}
	}

	Utility::delay(1);
	this->bus_handle.set(BMI_CS_A_PIN);
}

void BMI085::write_g(u8 addr, const u8 data)
{
	u8 tx[]=
	{
		addr,
		data,
	};
	this->bus_handle.reset(BMI_CS_G_PIN);
	if( SPI_MASTER_STATUS_SUCCESS == SPI_MASTER_Transmit(&BMI_SPI_MASTER_1, tx,  sizeof(tx) / sizeof( (tx)[0]) ))
	{
		while (BMI_SPI_MASTER_1.runtime->rx_busy){}
	}

	Utility::delay(1);
	this->bus_handle.set(BMI_CS_G_PIN);
}

void BMI085::init_accel()
{
	this->write_a(BMI_A_RESET_ADDR, BMI_A_RESET_DATA);
	Utility::delay_ms(10);

	// Dummy write to turn it on
	this->write_a(0xFF, 0xFF);
	Utility::delay_ms(1);

	// Setting the power mode
	this->write_a(BMI_A_PWR_CTRL_ADDR, BMI_A_PWR_ON);
	Utility::delay_ms(50);

	// Setting the range
	this->write_a(BMI_A_RANGE_ADDR, BMI_A_RANGE_2G);
	Utility::delay_ms(50);
}

void BMI085::poll_accel()
{
	u8 rx[6] = { 0 };
	u8 tx = 0x12 | 0x80;

	this->bus_handle.reset(BMI_CS_A_PIN);
	Utility::delay_ms(1);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, &tx, rx, 6);
	Utility::delay_ms(1);
}

void BMI085::init_gyro()
{
	// Reset
	this->write_g(BMI_G_RESET_ADDR, BMI_G_RESET_DATA);
	Utility::delay_ms(50);
	// write configuration, set the bandwidth first
	this->write_g(BMI_G_BANDWIDTH_ADDR, BMI_G_BANDWIDTH_DATA);
	// set the range
	this->write_g(BMI_G_RANGE_ADDR, BMI_G_RANGE_DATA);
}

void BMI085::poll_gyro()
{
	u8 rx[6] = { 0 };
	u8 tx = 0x02 | 0x80;

	this->bus_handle.reset(BMI_CS_G_PIN);
	SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, &tx, rx, 6);
	Utility::delay_ms(1);
}

void BMI085::calculate_stats(acc_stat_imu _imu)
{
	_imu.amount_values++;
	_imu.total = _imu.total + (u16) (this->imu.accel_values[_imu.id]);
	// check if it is the first value
	if(_imu.amount_values == 0)
	{
		_imu.max = (u16) (this->imu.accel_values[_imu.id]);
		_imu.min = (u16) (this->imu.accel_values[_imu.id]);
		// If we divide it already we will get division error
		_imu.avg = (u16) (this->imu.accel_values[_imu.id]);
	} else {
		// check if the new value is the max
		if(_imu.max < this->imu.accel_values[_imu.id])
		{
			_imu.max = (u16) (this->imu.accel_values[_imu.id]);
		}
		// If it is a new max value then don't check if its a new minimum value, but if it is not a new max value check the old value
		else if(_imu.min > this->imu.accel_values[_imu.id]) { 
			_imu.min = (u16) (this->imu.accel_values[_imu.id]);
		}
		// always add calculate the new average no matter if there is a new minimum or max
		_imu.avg = (u16) ( _imu.total / _imu.amount_values);
	}
}

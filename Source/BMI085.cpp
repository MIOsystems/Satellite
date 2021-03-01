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

BMI085::BMI085()
{
	this->imu = {	0,  // ACCELEROMETER ID
					0,	  // GYROSCOPE ID
					{ 0, 0, 0, 0 }, // ACCELEROMETER CONFIG
					{ 0, 0, 0, 0 }, // GYROSCOPE CONFIG
					{ 0, 0, 0 }, // ACCELEROMETER RAW VALUES
					{ 0, 0, 0 }, // GYROSCOPE RAW VALUES
	};
	this->status = SPI_MASTER_STATUS_SUCCESS;
}

u8 BMI085::init()
{
	this->status = SPI_MASTER_SetBaudRate(&BMI_SPI_MASTER_1, BMI_SPI_MASTER_1.config->channel_config->baudrate);

	// Check if setting baud rate went correctly
	if (this->status != SPI_MASTER_STATUS_SUCCESS)
	{
		return this->status;
	}
	Utility::delay_ms(100);

	// Sending a high bit to the Accelerometer to put it in SPI mode
	XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	Utility::delay(1);
	XMC_GPIO_SetOutputLow(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	
	// Setting the accelo chip low and gyro high => this means that the gyro is unselected and accelo selected
	this->select(BMI_CS_ACCEL);
	this->init_accel();


	// Select the gyro

	return this->status;
}

u8 BMI085::poll()
{
}

u8 BMI085::read_reg(u8 addr, u8 *rx_buff, u8 size)
{
	this->wait();
	this->status = SPI_MASTER_STATUS_SUCCESS;
	this->status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, &addr, rx_buff, size);
	this->wait();
	return this->status;
}

void BMI085::select(u8 chip)
{
	switch(chip)
	{
		case BMI_CS_ACCEL:
			XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);
			XMC_GPIO_SetOutputLow(BMI_CS_A_GPIO, BMI_CS_A_PIN);
			break;
		case BMI_CS_GYRO:
			XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
			XMC_GPIO_SetOutputLow(BMI_CS_G_GPIO, BMI_CS_G_PIN);
			break;
		default:
			break;
	}
}

void BMI085::wait()
{
	const bool tx_busy = BMI_SPI_MASTER_1.runtime->rx_busy;
	const bool rx_busy = BMI_SPI_MASTER_1.runtime->tx_busy;
	if (tx_busy || rx_busy)
	{
		while (&BMI_SPI_MASTER_1.runtime->rx_busy || &BMI_SPI_MASTER_1.runtime->tx_busy);
	}
}

u8 BMI085::write_to_reg(u8 addr, const u8* data)
{
	this->wait();
	u8 count_data = sizeof(data) / sizeof( (data)[0] );
	u8 *tx = (u8 *) malloc( (count_data + 1) * sizeof(u8));
	u8 tx_len = sizeof(tx) / sizeof( (tx)[0] );
	this->status = SPI_MASTER_Transmit(&BMI_SPI_MASTER_1, tx, tx_len);
	this->wait();
	free(tx);
	return this->status;
}

u8 BMI085::init_accel()
{
	this->status = SPI_MASTER_STATUS_SUCCESS;
	u8 rx_buff = 0;

	// Reads the accelo id
	this->status = this->read_reg(BMI_A_CHIP_ID_ADDR, &rx_buff, 1);
	if(this->status != SPI_MASTER_STATUS_SUCCESS)
	{
		return this->status;
	}
	
	this->imu.accel_id = rx_buff;

	// Setting the accelerometer with the config
	this->imu.accel_cfg.odr = BMI_A_ODR_1600_HZ;
	this->imu.accel_cfg.range = BMI_A_RANGE_16G;
	this->imu.accel_cfg.pwr_mode = BMI_A_PWR_ON;
	this->imu.accel_cfg.bandwidth = BMI_A_BWP_NORMAL;

	// set power mode
	this->status = this->write_to_reg(BMI_A_PWR_CTRL_ADDR, (u8 *) BMI_A_PWR_ON);
	Utility::delay_ms(10);
	if(this->status != SPI_MASTER_STATUS_SUCCESS)
	{
		return this->status;
	}

	// Writing the rest of the config
	this->status = this->write_accel_config();
	Utility::delay_ms(10);
	if(this->status != SPI_MASTER_STATUS_SUCCESS)
	{
		return this->status;
	}


	return this->status;
}

u8 BMI085::write_accel_config()
{
	this->status = SPI_MASTER_STATUS_SUCCESS;
	u8 data[2] = {0};
	u8 bw = this->imu.accel_cfg.bandwidth;
	u8 range = this->imu.accel_cfg.range; 
	u8 odr = this->imu.accel_cfg.odr;

	// getting the registers
	this->status = this->read_reg(0x40, data, 2);
	if(this->status != SPI_MASTER_STATUS_SUCCESS)
	{
		return this->status;
	}

	// update it with new odr and bw values, that was set in the config struct
	data[0] = ((data[0] & ~(BMI_A_ODR_MASK)) | (odr & BMI_A_ODR_MASK));
	data[0] = ((data[0] & ~(BMI_A_BW_MASK)) | ((bw << 4) & BMI_A_BW_MASK));
	data[1] = ((data[1] & ~(BMI_A_RANGE_MASK)) | (range & BMI_A_RANGE_MASK));

	this->status = this->write_to_reg(BMI_A_CONFIG_ADDR, data);

	return this->status;
}

u8 BMI085::write_gyro_config()
{

}

/*
 * BMI085.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#include <DAVE.h>
#include <string>

#include <Header/BMI085.h>
#include <Header/Satellite.h>
#include <Header/Utility.h>


BMI085::BMI085()
{
	this->gyro_data = new Vector3(0, 0, 0);
	this->acc_data = new Vector3(0, 0, 0);
	this->axis_data_stat = new StatisticVector(0, 0, 0);
	this->axis_data = new Vector3(0, 0, 0);
}

u8 BMI085::init()
{
	u32 baud_rate = SPI_MASTER_1.config->channel_config->baudrate;
	u8 status = SPI_MASTER_SetBaudRate(&SPI_MASTER_1, baud_rate);

	// Check if setting baud rate went correctly
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	XMC_GPIO_SetMode(BMI_CS_A_GPIO, BMI_CS_A_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(BMI_CS_G_GPIO, BMI_CS_G_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	Utility::delay_ms(100);
	XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);
//	status = init_gyro();
//	if (status != SPI_MASTER_STATUS_SUCCESS)
//	{
//		return status;
//	}
//	status = init_accelo();
	// Last status does not matter because after this we are done anyway so just return the last statement
	return status;

}
u8 BMI085::poll()
{
	const bool tx_busy = SPI_MASTER_1.runtime->rx_busy;
	const bool rx_busy = SPI_MASTER_1.runtime->tx_busy;
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	if (tx_busy || rx_busy)
	{
		while (SPI_MASTER_1.runtime->rx_busy || SPI_MASTER_1.runtime->tx_busy);
	}
	// GYROSCOPE
	status = poll_gyro();
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	// ACCELEROMETER
	//status = poll_accelo();
	return status;
}

u8 BMI085::select(u8 chip)
{
	// High is unselected, low is selected
	switch (chip)
	{
	case BMI_GYRO:
		XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);// ACCELO PIN => HIGH
		XMC_GPIO_SetOutputLow(BMI_CS_G_GPIO, BMI_CS_G_PIN);	// GYRO PIN => LOW
		break;
	case BMI_ACCEL:
		XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);// GYRO PIN => HIGH
		XMC_GPIO_SetOutputLow(BMI_CS_A_GPIO, BMI_CS_A_PIN);	// ACCELO PIN => LOW
		break;
	}
	return 0;
}

u8 BMI085::write(u8 addr, u8 data)
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	u8 tx_buff[2] =
	{ addr, data };
	u32 buff_len = (sizeof(tx_buff) / sizeof((tx_buff)[0]));
	status = SPI_MASTER_Transmit(&SPI_MASTER_1, tx_buff, buff_len);
	if (status == SPI_MASTER_STATUS_SUCCESS)
	{
		// if success wait for it to fully transmit
		while (SPI_MASTER_1.runtime->tx_busy)
			;
	}
	return status;
}

u8 BMI085::init_gyro()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;

	// Access gyroscope only and turn off accelerometer
	select(BMI_GYRO);
	// Soft reseting the BMI sensor
	status = write(BMI_G_RST_ADDR, BMI_G_RST_DATA);
	Utility::delay_ms(40); // REQUIRES ATLEAST 30, chose 40 to be safe

	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}
	// Setting the correct values for bandwidth
	status = write(BMI_G_BANW_ADDR, BMI_G_BANW_DATA);
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	// Setting the correct values for range
	status = write(BMI_G_RANG_ADDR, BMI_G_RANG_DATA);
	return status;
}

u8 BMI085::poll_gyro()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	//select(BMI_GYRO);

	u8 rx_buff[BMI_G_BUFF_S] = { };
	u8 tx_buff = 0x02;
	XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	XMC_GPIO_SetOutputLow(BMI_CS_G_GPIO, BMI_CS_G_PIN);
	status = SPI_MASTER_Transfer(&SPI_MASTER_1, (u8 *) tx_buff, rx_buff, BMI_G_BUFF_S);
	while (SPI_MASTER_1.runtime->rx_busy || SPI_MASTER_1.runtime->tx_busy);
	XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);
	if (status != SPI_MASTER_STATUS_SUCCESS)
		return status;

	i32 data[3] = { 0, 0, 0 };
	reg_to_val(data, rx_buff);
	this->gyro_data = new Vector3(data[0], data[1], data[2]);
	return status;
}

u8 BMI085::init_accelo()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	// Access accelerometer only and turn off gyroscope
	select(BMI_ACCEL);

	// Soft resetting accelerometer
	status = write(BMI_A_RST_ADDR, BMI_A_RST_DATA);
	Utility::delay_ms(10); // Requires at least 1 ms
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	// Setting the power mode
	status = write(BMI_A_PWR_ADDR, BMI_A_PWR_DATA);
	Utility::delay_ms(50);
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	// Setting the Range
	status = write(BMI_A_RANG_ADDR, BMI_A_RANG_DATA);
	Utility::delay_ms(50);
	return status;
}

u8 BMI085::poll_accelo()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	select(BMI_ACCEL);
	u8 rx_buff[BMI_A_BUFF_S ] =
	{ };

	status = SPI_MASTER_Transfer(&SPI_MASTER_1, (u8 *) BMI_A_DATA_ADDR, rx_buff,
			BMI_A_BUFF_S);
	while (SPI_MASTER_1.runtime->rx_busy || SPI_MASTER_1.runtime->tx_busy)
		;
	return status;
}

void BMI085::reg_to_val(i32 *data, u8 *rx_buff)
{
	for (i32 i = 0; i < BMI_G_BUFF_S; i = (i + 2))
	{
		data[i] = (rx_buff[i + 1] << 8) | rx_buff[i];
	}
}

const char* BMI085::to_string()
{
	std::string data = "BMI085: \n";
	std::string gyro_data		= "\n\tACC_DATA: " + this->gyro_data->to_string();
	std::string acc_data		= "\n\tACC_DATA: " + this->acc_data->to_string();
	std::string axis_data		= "\n\tACC_DATA: " + this->axis_data->to_string();
	std::string axis_data_stat	= "\n\tACC_DATA: " + this->axis_data_stat->to_string();
	data = data + gyro_data + acc_data + axis_data + axis_data_stat;
	return data.c_str();
}


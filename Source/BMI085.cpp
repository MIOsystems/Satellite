/*
 * BMI085.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
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
}

u8 BMI085::init()
{
	u8 status = SPI_MASTER_SetBaudRate(&SPI_MASTER_1, SPI_MASTER_1.config->channel_config->baudrate);

	// Check if setting baud rate went correctly
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	XMC_GPIO_SetMode(BMI_CS_A_GPIO, BMI_CS_A_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(BMI_CS_G_GPIO, BMI_CS_G_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

	Utility::delay_ms(100);
	//XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	//XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);
	//XMC_SPI_CH_EnableSlaveSelect(&SPI_MASTER_1, XMC_SPI_CH_SLAVE_SELECT_0);

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
	//status = poll_gyro();
	if (status != SPI_MASTER_STATUS_SUCCESS)
	{
		return status;
	}

	// ACCELEROMETER
	status = poll_accelo();
	return status;
}

u8 BMI085::select(u8 chip)
{
	return 0;
}

u8 BMI085::write(u8 addr, u8 data)
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	u8 tx_buff[2] = { addr, data };
	u32 buff_len = (sizeof(tx_buff) / sizeof((tx_buff)[0]));
	status = SPI_MASTER_Transmit(&SPI_MASTER_1, tx_buff, buff_len);
	if (status == SPI_MASTER_STATUS_SUCCESS)
	{
		// if success wait for it to fully transmit
		while (SPI_MASTER_1.runtime->tx_busy);
	}
	return status;
}

u8 BMI085::poll_gyro()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	u8 rx_buff[BMI_G_BUFF_S] = { };
	u8 tx_buff = 0x02;
	// Selecting GYRO CHIP
	XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);
	XMC_GPIO_SetOutputLow(BMI_CS_G_GPIO, BMI_CS_G_PIN);
	// Transmitting the opcode and returns the raw data of the gyro
	status = SPI_MASTER_Transfer(&SPI_MASTER_1, &tx_buff, rx_buff, BMI_G_BUFF_S);
	// Waiting for transmission and receiving is done
	while (SPI_MASTER_1.runtime->rx_busy || SPI_MASTER_1.runtime->tx_busy);
	// Unselecting the chip
	XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);

	if (status != SPI_MASTER_STATUS_SUCCESS)
		return status;

	// Calculating the values again;
	i32 data[3] = { 0, 0, 0 };
	reg_to_val(data, rx_buff);
	this->gyro_data.setX(data[0]);
	this->gyro_data.setY(data[1]);
	this->gyro_data.setZ(data[2]);
	return status;
}

u8 BMI085::poll_accelo()
{
	u8 status = SPI_MASTER_STATUS_SUCCESS;
	u8 rx_buff[BMI_A_BUFF_S] = { };
	u8 tx_buff = 0x12 | 0x80;
	XMC_GPIO_SetOutputHigh(BMI_CS_G_GPIO, BMI_CS_G_PIN);
	XMC_GPIO_SetOutputLow(BMI_CS_A_GPIO, BMI_CS_A_PIN);

	status = SPI_MASTER_Transfer(&SPI_MASTER_1, &tx_buff, rx_buff, BMI_A_BUFF_S);
	while (SPI_MASTER_1.runtime->rx_busy || SPI_MASTER_1.runtime->tx_busy);
	// Unselecting the chip
	XMC_GPIO_SetOutputHigh(BMI_CS_A_GPIO, BMI_CS_A_PIN);

	if (status != SPI_MASTER_STATUS_SUCCESS)
		return status;

	return status;


}

void BMI085::reg_to_val(i32 *data, u8 *rx_buff)
{
	for (i32 i = 0; i < BMI_G_BUFF_S; i = (i + 2))
	{
		data[i] = (rx_buff[i + 1] << 8) | rx_buff[i];
	}
}

char* BMI085::to_string()
{
	size_t len = 0;
	size_t len_check = 0;

	len = snprintf(NULL, len, "BMI085");
	char *data = (char *) calloc(1, (sizeof(char *) * (len + 1)));
	if(!data) {
		return NULL;
	}
	
	len_check = snprintf(data, len + 1, "GNSS");
	if(len_check > (len + 1)) {
		return NULL;
	}
	return data;
}


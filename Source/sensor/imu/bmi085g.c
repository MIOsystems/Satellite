/*
 * bmi085g.c
 *
 *  Created on: 22 Mar 2021
 *      Author: Patrick
 */

#include <math.h>

#include <DAVE.h>

#include <include/hardware/spi_handler.h>
#include <include/sensor/imu/bmi085g.h>

#include <include/util/delay.h>
#include <include/util/utility.h>
#include <include/util/math_utility.h>

#include <include/satellite.h>

u8 bmi085g_init(bmi085x *bmi085)
{
	bmi085x_status_e status = BMI085X_SUCCESS;

	// Softresetting the gyroscope first
	status = bmi085g_write_reg(BMI085G_SOFT_RST_ADDR, BMI085G_RESET_DATA);
	delay_ms(50);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}

	// writing configuration
	status = bmi085g_write_reg(bmi085->gyro.config.bandwidth.reg_addr, bmi085->gyro.config.bandwidth.instr);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}

	delay_ms(1);

	status = bmi085g_write_reg(bmi085->gyro.config.meas_range.reg_addr, bmi085->gyro.config.meas_range.instr);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}

	// Validating gyroscope to read the chip id which we know should be its reset value
	bmi085g_read_reg(BMI085G_CHIP_ID_ADDR, &bmi085->gyro.chip_id);
	if(bmi085->gyro.chip_id != BMI085G_DEFAULT_CHIP_ID)
	{
		return BMI085X_INVALID_CHIP_ID;
	}
	return status;
}

u8 bmi085g_poll(bmi085x *bmi085)
{
	u8 rx_buff[7] = { 0 };
	u8 tx_buff[7] = { BMI085G_DATA_ADDR | BMI085X_READMASK, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	u8 status = 0;
	spi_select_chip(SPI_SLAVE_BMI085G_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, ARRAY_SIZEOF(tx_buff));
	spi_unselect_chip(SPI_SLAVE_BMI085G_CS);

	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_POLL_FAILURE;
	}


	// conversion to rad per seconds depending on the configuration that is set
//	f32 conv_raw_rad_s = 0;
//	switch(bmi085->gyro.config.meas_range.instr)
//	{
//		case BMI085G_CFG_RANGE_125:
//			conv_raw_rad_s = DEG_TO_RAD_CONST * 125.0f / 32768.0f;
//			break;
//		case BMI085G_CFG_RANGE_250:
//			conv_raw_rad_s = DEG_TO_RAD_CONST * 250.0f / 32768.0f;
//			break;
//		case BMI085G_CFG_RANGE_500:
//			conv_raw_rad_s = DEG_TO_RAD_CONST * 500.0f / 32768.0f;
//			break;
//		case BMI085G_CFG_RANGE_1000:
//			conv_raw_rad_s = DEG_TO_RAD_CONST * 1000.0f / 32768.0f;
//			break;
//		case BMI085G_CFG_RANGE_2000:
//			conv_raw_rad_s = DEG_TO_RAD_CONST * 2000.0f / 32768.0f;
//			break;
//	}
	i16 raw_x = CONCAT_RAW_VAL(rx_buff[2], rx_buff[1]);
	i16 raw_y = CONCAT_RAW_VAL(rx_buff[4], rx_buff[3]);
	i16 raw_z = CONCAT_RAW_VAL(rx_buff[6], rx_buff[5]);

	// values in degrees per seconds
//	bmi085->data.gyro_poll_val.x = (f32) (raw_x * conv_raw_rad_s);
//	bmi085->data.gyro_poll_val.y = (f32) (raw_y * conv_raw_rad_s);
//	bmi085->data.gyro_poll_val.z = (f32) (raw_z * conv_raw_rad_s);

	const f32 gain = (1.0f / 16.384f) * (M_PI / 180.0f);
	bmi085->data.gyro_poll_val.x = (raw_x * gain) + 0.0;
	bmi085->data.gyro_poll_val.y = (raw_y * gain) + 0.0;
	bmi085->data.gyro_poll_val.z = (raw_z * gain) + 0.0;
	return BMI085X_SUCCESS;
}

u8 bmi085g_read_reg(const u8 addr, u8 *data)
{
	u8 status = BMI085X_SUCCESS;
	u8 tx_buff[2] = { addr | BMI085X_READMASK, 0x00};
	u8 rx_buff[2] = { 0 };

	spi_select_chip(SPI_SLAVE_BMI085G_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, ARRAY_SIZEOF(tx_buff));
	spi_wait(&BMI_SPI_MASTER_1, SPI_BOTH);
	spi_unselect_chip(SPI_SLAVE_BMI085G_CS);
	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_READ_FAILURE;
	}
	*data = rx_buff[1];
	return BMI085X_SUCCESS;
}

u8 bmi085g_write_reg(const u8 addr, const u8 data)
{
	u8 status = BMI085X_SUCCESS;
	u8 tx_buff[] = { addr, data };
	const u8 tx_len = ARRAY_SIZEOF(tx_buff);
	u8 rx_buff[tx_len];

	spi_select_chip(SPI_SLAVE_BMI085G_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, tx_len);
	spi_wait(&BMI_SPI_MASTER_1, SPI_BOTH);
	spi_unselect_chip(SPI_SLAVE_BMI085G_CS);

	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_WRITE_FAILURE;
	}
	return BMI085X_SUCCESS;
}

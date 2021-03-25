#include <math.h>

#include <DAVE.h>

#include <include/hardware/spi_handler.h>
#include <include/sensor/imu/bmi085a.h>
#include <include/util/delay.h>
#include <include/util/types.h>
#include <include/util/utility.h>
#include <include/data/statistic.h>
#include <include/satellite.h>


#define BMI085A_BUFF_SIZE	8
static u8 rx_buff_poll[BMI085A_BUFF_SIZE] = { 0 };
static u8 tx_buff_poll[BMI085A_BUFF_SIZE] = { BMI085A_DATA_ADDR | BMI085X_READMASK,
												0xFF,
												0xFF,
												0xFF,
												0xFF,
												0xFF,
												0xFF,
												0xFF
											};

const f32 bmi085a_sensivity = 32768.0f;



bmi085x_status_e bmi085a_init(bmi085x *bmi085)
{
	bmi085x_status_e status = BMI085X_SUCCESS;
	spi_flush(&BMI_SPI_MASTER_1, SPI_RX);

	// Setting the accelerometer in SPI mode by setting
	DIGITAL_IO_SetOutputHigh(SPI_SLAVE_BMI085A_CS);
	delay_ms(1);

	// Turning the accelerometer on and waiting for 50 ms
	status = bmi085a_write_reg(BMI085A_PWR_CNTRL_ADDR, BMI085A_PWR_CNTRL_ACC_ON);
	delay_ms(50);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}

	/* Write configuration */
	// Setting the range configuration
	status = bmi085a_write_reg(bmi085->acc.config.meas_range.reg_addr, bmi085->acc.config.meas_range.instr);
	delay_ms(50);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}
	// The accelerometer is default in suspend mode it has to be put in active mode
	status = bmi085a_write_reg(bmi085->acc.config.pwr_mode.reg_addr, bmi085->acc.config.pwr_mode.instr);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}
	/* to validate the initializing went
	 * correct the chip id is checked,
	 * which should be its default value
	 */
	bmi085a_read_reg(BMI085A_CHIP_ID_ADDR, &bmi085->acc.chip_id);
	if(bmi085->acc.chip_id != BMI085A_DEFAULT_CHIP_ID)
	{
		return BMI085X_INVALID_CHIP_ID;
	}
	return BMI085X_SUCCESS;
}

bmi085x_status_e bmi085a_poll(bmi085x *bmi085)
{
	u8 status = 0;
	spi_select_chip(SPI_SLAVE_BMI085A_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff_poll, rx_buff_poll, BMI085A_BUFF_SIZE);
	spi_unselect_chip(SPI_SLAVE_BMI085A_CS);
	//delay_ms(2);

	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_POLL_FAILURE;
	}
#ifdef DEBUG_MODE
	i16 raw_x = CONCAT_RAW_VAL(rx_buff_poll[3], rx_buff_poll[2]);
	i16 raw_y = CONCAT_RAW_VAL(rx_buff_poll[5], rx_buff_poll[4]);
	i16 raw_z = CONCAT_RAW_VAL(rx_buff_poll[7], rx_buff_poll[6]);
#endif
	bmi085->data.accel_poll_val.x = (( (f32) (CONCAT_RAW_VAL(rx_buff_poll[3], rx_buff_poll[2])) / bmi085a_sensivity) * powf(2.0f, (f32) (bmi085->acc.config.meas_range.reg_addr + 1)));
	bmi085->data.accel_poll_val.y = (( (f32) (CONCAT_RAW_VAL(rx_buff_poll[5], rx_buff_poll[4])) / bmi085a_sensivity) * powf(2.0f, (f32) (bmi085->acc.config.meas_range.reg_addr + 1)));
	bmi085->data.accel_poll_val.z = (( (f32) (CONCAT_RAW_VAL(rx_buff_poll[7], rx_buff_poll[6])) / bmi085a_sensivity) * powf(2.0f, (f32) (bmi085->acc.config.meas_range.reg_addr + 1)));

// Set this in the configuration
#ifdef BMI_DATA_IN_MG
	bmi085->data.accel_poll_val.x *= 100;
	bmi085->data.accel_poll_val.y *= 100;
	bmi085->data.accel_poll_val.z *= 100;

#endif

	if(bmi085a_poll_counter == 1000)
	{
		bmi085a_poll_counter = 0;
	}
	// calculates the min/max/avg of each axis
	statistic_calc_aggregate_val(&bmi085->data.x_stat, &bmi085->data.accel_poll_val.x, bmi085a_poll_counter);
	statistic_calc_aggregate_val(&bmi085->data.y_stat, &bmi085->data.accel_poll_val.y, bmi085a_poll_counter);
	statistic_calc_aggregate_val(&bmi085->data.z_stat, &bmi085->data.accel_poll_val.z, bmi085a_poll_counter);
	bmi085a_poll_counter++;

	return status;
}

bmi085x_status_e bmi085a_read_reg(const u8 addr, u8 *data)
{
	u8 status = BMI085X_SUCCESS;
	u8 tx_buff[3] = { addr | BMI085X_READMASK, 0x00, 0x00 };
	u8 rx_buff[3] = { 0 };

	spi_select_chip(SPI_SLAVE_BMI085A_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, ARRAY_SIZEOF(tx_buff));
	//spi_wait(SPI_SLAVE_BMI085A_CS, SPI_BOTH);
	spi_unselect_chip(SPI_SLAVE_BMI085A_CS);
	delay_ms(2);

	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_READ_FAILURE;
	}
	// first byte is the address, second is the dummy byte, third is the actual data
	*data = rx_buff[2];
	return BMI085X_SUCCESS;
}

bmi085x_status_e bmi085a_write_reg(const u8 addr, const u8 data)
{
	// TODO check if this can this be void???
	u8 status = BMI085X_SUCCESS;
	u8 tx_buff[] = { addr, data };
	const u8 tx_len = ARRAY_SIZEOF(tx_buff);
	u8 rx_buff[tx_len];
	spi_select_chip(SPI_SLAVE_BMI085A_CS);
	status = SPI_MASTER_Transfer(&BMI_SPI_MASTER_1, tx_buff, rx_buff, tx_len);
	spi_wait(&BMI_SPI_MASTER_1, SPI_BOTH);
	spi_unselect_chip(SPI_SLAVE_BMI085A_CS);

	if(status != SPI_MASTER_STATUS_SUCCESS)
	{
		return BMI085X_WRITE_FAILURE;
	}
	return BMI085X_SUCCESS;
}


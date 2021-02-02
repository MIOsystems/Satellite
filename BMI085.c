#include <stdint.h>
#include <DAVE.h>

#include <BMI085.h>
#include <PinConfiguration.h>


#include <Utility.h>

int32_t BMI_init(BMI085* sensor) {
	uint32_t baudrate = SPI_MASTER_1.config->channel_config->baudrate;
	int8_t status = SPI_MASTER_SetBaudRate(&SPI_MASTER_1, baudrate);
	if(status != SPI_MASTER_STATUS_SUCCESS) {
		return status;
	}

	XMC_GPIO_SetMode(BMI_GPIO_PORT, BMI_PIN_NUMBER, BMI_XMC_MODE);
	delay_ms(145); // TODO CHECK IF THIS LONG ENOUGH
	XMC_GPIO_SetOutputHigh(BMI_GPIO_PORT, BMI_PIN_NUMBER);
	delay_ms(145); // TODO CHECK IF THIS LONG ENOUGH



	status = BMI_set_gyro_mode(BMI_A_NORMAL, sensor);
	if(status == SPI_MASTER_STATUS_SUCCESS) {
		//Setting the data of array to zeros
		memset(sensor->gyroscope.data, 0, 3 * sizeof(sensor->gyroscope.data[0]));
	} else {
		// Something failed program should break if setting a mode does not work
		return status;
	}
	status = BMI_set_gyro_mode(BMI_G_NORMAL, sensor);
	if(status == SPI_MASTER_STATUS_SUCCESS) {
		//Setting the data of array to zeros
		memset(sensor->gyroscope.data, 0, 3 * sizeof(sensor->gyroscope.data[0]));
	}
	return status;
}



int32_t BMI_set_accel_mode(power_modes_accel_e mode, BMI085 *sensor) {
	int8_t status = SPI_MASTER_STATUS_SUCCESS;
	//TODO FIX CODE DUPLICATION
	switch(mode) {
		case BMI_A_NORMAL:
			status = SPI_MASTER_Transmit(&SPI_MASTER_1, (uint8_t *) BMI_A_NORMAL_OPCODE, sizeof(uint8_t));
			if(status == SPI_MASTER_STATUS_SUCCESS) {
				sensor->accelerometer.mode = BMI_A_NORMAL;
			}
			flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
			break;
		case BMI_A_SUSPEND:
			status = SPI_MASTER_Transmit(&SPI_MASTER_1, (uint8_t *) BMI_A_SUSPEND_OPCODE, sizeof(uint8_t));
			if(status == SPI_MASTER_STATUS_SUCCESS) {
				sensor->accelerometer.mode = BMI_A_SUSPEND;
			}
			flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
			break;
		default:
			return -1;
	}
	return status;
}


int32_t BMI_set_gyro_mode(power_modes_gyro_e mode, BMI085 *sensor) {
	int8_t status = SPI_MASTER_STATUS_SUCCESS;
	switch(mode) {
		//TODO FIX CODE DUPLICATION
		case BMI_G_NORMAL:
			status = SPI_MASTER_Transmit(&SPI_MASTER_1, (uint8_t *) BMI_G_NORMAL_OPCODE, sizeof(uint8_t));
			if(status == SPI_MASTER_STATUS_SUCCESS) {
				sensor->gyroscope.mode = BMI_G_NORMAL;
			}
			flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
			break;
		case BMI_G_SUSPEND:
			status = SPI_MASTER_Transmit(&SPI_MASTER_1, (uint8_t *) BMI_G_SUSPEND_OPCODE, sizeof(uint8_t));
			if(status == SPI_MASTER_STATUS_SUCCESS) {
				sensor->gyroscope.mode = BMI_G_SUSPEND;
			}
			flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
			break;
		case BMI_G_DEEP_SUSPEND:
			status = SPI_MASTER_Transmit(&SPI_MASTER_1, (uint8_t *) BMI_G_D_SUSPEND_OPCODE, sizeof(uint8_t));
			if(status == SPI_MASTER_STATUS_SUCCESS) {
				sensor->gyroscope.mode = BMI_G_DEEP_SUSPEND;
			}
			flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
			break;
		default:
			return -1;
	}
	return status;
}


int32_t BMI_poll(BMI085 *sensor) {
	const uint8_t size = 6;
	uint8_t raw_counter = 0;
	uint8_t msb = 0;
	uint8_t lsb = 0;
	int8_t status = 0;

	// Initializes raw data and sets all the entries to zero
	uint8_t *raw_data = (uint8_t*)calloc(size, sizeof(uint8_t));

	// GRYOSCOPE
	XMC_GPIO_SetOutputLow(BMI_GPIO_PORT, BMI_PIN_NUMBER);
	status = SPI_MASTER_Transfer(&SPI_MASTER_1, (uint8_t *) BMI_G_DATA_OPCODE, raw_data, size);
	flush_SPI_buffer(&SPI_MASTER_1, SPI_RX);
	flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);
	if(status != SPI_MASTER_STATUS_SUCCESS) {
		return status; // SPI STATUS CODE
	}

	//gyroscope can be calculated like this:
	//rateXYZ = RATEXYZ_MSB * 256 + RATEXYZ_LSB
	for(uint16_t i = 0; i < 3; i++) {
		// MSB is bit 8 to 15
		// LSB is bit 0 to 7
		// Calculate and set the value in the sensor struct
		msb = raw_data[raw_counter + 1];
		lsb = raw_data[raw_counter];
		sensor->gyroscope.data[i] = msb * 256 + lsb;
		raw_counter += 2;
	}

	// clearing the raw_data of the gyroscope values
	memset(raw_data, 0, size * sizeof(raw_data[0]));

	// ACCELEROMETER
	XMC_GPIO_SetOutputLow(BMI_GPIO_PORT, BMI_PIN_NUMBER);
	status = SPI_MASTER_Transfer(&SPI_MASTER_1, (uint8_t *) BMI_A_DATA_OPCODE, raw_data, size);
	flush_SPI_buffer(&SPI_MASTER_1, SPI_RX);
	flush_SPI_buffer(&SPI_MASTER_1, SPI_TX);

	if(status != SPI_MASTER_STATUS_SUCCESS) {
		return status; // SPI STATUS CODE
	}
	// TODO remove this loop and add it to the previous loop
	//accelerometer can be calculated like this:
	//accelXYZ = ACC_XYZ_MSB * 256 + ACC_XYZ_LSB
	for(uint8_t i = 0; i < 3; i++) {
		// MSB is bit 8 to 15
		// LSB is bit 0 to 7
		// Calculate and set the value in the sensor
		msb = raw_data[raw_counter + 1];
		lsb = raw_data[raw_counter];
		sensor->accelerometer.data[i] = msb * 256 + lsb;
		raw_counter += 2;
	}
	// FREEING POINTERS
	free(raw_data);
	return status;
}

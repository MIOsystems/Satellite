#include "include/communication/com_serial_imu.h"

#ifdef IMU_COM

com_serial_imu_command imuComBuffer;
int imuComBufferPos = 0;

bmi085x* imuRef = NULL;

com_serial_imu_command_ack commandAck = { 0xF0, 0x0F, 0, 0, 0, 0, 0 };
bool sendCommandAck = false;

int8_t imu_serial_com_init(bmi085x* imu, bool haltInterrupts)
{
	if(haltInterrupts)
	{
		TIMER_Stop(&POLL_TIMER);
		INTERRUPT_Disable(&POLL_TIMER_INTERRUPT);
		INTERRUPT_Disable(&RS422_INTERRUPT);
	}
	int8_t status = 0;
	imuRef = imu;

	com_serial_imu_fram_data framData = { 0, 0, 0 };
	fram_read_data(0, &framData, sizeof(com_serial_imu_fram_data));

	bool framDataValid = imu_serial_com_validate_fram_data(&framData);
	if(!framDataValid)
	{
		status = (int8_t)imuInit(imu);
		framData.accelRangeRegisterValue = imu->acc.config.meas_range.instr;
		framData.gyroRangeRegisterValue = imu->gyro.config.meas_range.instr;
		framData.gyroBandwidthRegisterValue = imu->gyro.config.bandwidth.instr;

		fram_enable_write();
		fram_write_data(0, &framData, sizeof(com_serial_imu_fram_data));
		fram_disable_write();

		return status;
	}

	bmi085xSensor accel = {
		.chip_id = 0,
		.config = {
			.pwr_mode = {
				.reg_addr = BMI085A_PWR_MODE_ADDR,
				.instr = BMI085A_PWR_MODE_ACTIVE,
			},
			.meas_range = {
				.reg_addr = BMI085A_RANGE_ADDR,
				.instr = framData.accelRangeRegisterValue,
			},
			.bandwidth = {
				.reg_addr = BMI085A_CFG_ADDR,
				.instr = 0,
			},
			.odr = {
				.reg_addr = BMI085A_CFG_ADDR,
				.instr = 0x8c,
			}
		}
	};

	bmi085xSensor gyro = {
		.chip_id = 0,
		.config = {
			.pwr_mode = {
				.reg_addr = BMI085G_CFG_PWR_MODE_ADDR,
				.instr = BMI085G_CFG_PWR_MODE_NRML,
			},
			.meas_range = {
				.reg_addr = BMI085G_CFG_RANG_ADDR,
				.instr = framData.gyroRangeRegisterValue,
			},
			.bandwidth = {
				.reg_addr = BMI085G_CFG_BANDWIDTH_ADDR,
				.instr = framData.gyroBandwidthRegisterValue,
			},
			.odr = {
				.reg_addr = 0,
				.instr = 0,
			}
		}
	};

	status = (int8_t)imuInitParam(imu, accel, gyro);

	if(haltInterrupts)
	{
		INTERRUPT_Enable(&POLL_TIMER_INTERRUPT);
		TIMER_Start(&POLL_TIMER);
		INTERRUPT_Enable(&RS422_INTERRUPT);
	}

	return status;
}

com_serial_imu_err_t imu_serial_com_recv()
{
	uint8_t rx_data = 0;
	DIGITAL_IO_SetOutputHigh(&RE_422);
	UART_STATUS_t status = UART_Receive(&RS422_UART_0, &rx_data , 1);
	DIGITAL_IO_SetOutputLow(&RE_422);

	if(status != UART_STATUS_SUCCESS)
	{
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		return COM_SERIAL_IMU_ERR_READ_ERROR;
	}

	DIGITAL_IO_SetOutputLow(&LED_RED);

	((uint8_t*)(&imuComBuffer))[imuComBufferPos] = rx_data;
	imuComBufferPos++;

	if(imuComBufferPos == COM_SERIAL_IMU_BUFFER_SIZE)
	{
		imu_serial_com_packet_received_handle();
		imuComBufferPos = 0;
	}

	return COM_SERIAL_IMU_ERR_OK;
}

com_serial_imu_err_t imu_serial_com_write(uint8_t* data, uint32_t size)
{
	DIGITAL_IO_SetOutputHigh(&LED_BLUE);
	DIGITAL_IO_SetOutputHigh(&DE_422);
	delayMs(10);
	UART_STATUS_t status = UART_Transmit(&RS422_UART_0, data, size);
	delayMs(10);
	DIGITAL_IO_SetOutputLow(&DE_422);
	DIGITAL_IO_SetOutputLow(&LED_BLUE);

	if(status != UART_STATUS_SUCCESS)
	{
		DIGITAL_IO_SetOutputHigh(&LED_RED);
		return COM_SERIAL_IMU_ERR_WRITE_ERROR;
	}

	return COM_SERIAL_IMU_ERR_OK;
}

void imu_serial_com_packet_received_handle()
{
	bool isValidPacket = imu_serial_com_handle_packet();

	com_serial_imu_command_ack commandAckTemp = {
		0xF0,
		0x0F,
		(uint8_t)ACKNOWLEGDEMENT,
		imuComBuffer.chip,
		imuComBuffer.registerAddress,
		imuComBuffer.registerValue,
		(isValidPacket) ? 1 : 0
	};
	commandAck = commandAckTemp;
	sendCommandAck = true;

	if(isValidPacket)
		imu_serial_com_init(imuRef, true);
}

bool imu_serial_com_handle_packet()
{
	if(imuComBuffer.chip == ACCELEROMETER && imuComBuffer.registerAddress == BMI085A_RANGE_ADDR && imuComBuffer.registerValue < 4) // Valid below max value
	{
		fram_enable_write();
		fram_write_data(0, &imuComBuffer.registerValue, 1);
		fram_disable_write();
		return true;
	}
	else if(imuComBuffer.chip == GYRO)
	{
		if(imuComBuffer.registerAddress == BMI085G_CFG_RANG_ADDR && imuComBuffer.registerValue < 5) // Valid below max value
		{
			fram_enable_write();
			fram_write_data(1, &imuComBuffer.registerValue, 1);
			fram_disable_write();
			return true;
		}
		else if(imuComBuffer.registerAddress == BMI085G_CFG_BANDWIDTH_ADDR && imuComBuffer.registerValue < 8) // Valid below max value
		{
			fram_enable_write();
			fram_write_data(2, &imuComBuffer.registerValue, 1);
			fram_disable_write();
			return true;
		}
	}

	return false;
}

void imu_serial_com_send_measurements(bmi085x* imu)
{
	if(sendCommandAck)
	{
		imu_serial_com_write((uint8_t*)(&commandAck), sizeof(com_serial_imu_command_ack));
		sendCommandAck = false;
	}

	com_serial_imu_data_packet dataPacket = {
		0xF0,
		0x0F,
		(uint8_t)IMU_DATA,
		imu->data.raw_accel_poll_val.x, imu->data.raw_accel_poll_val.y, imu->data.raw_accel_poll_val.z,
		imu->data.raw_gyro_poll_val.x, imu->data.raw_gyro_poll_val.y, imu->data.raw_gyro_poll_val.z
	};

	imu_serial_com_write((uint8_t*)(&dataPacket), 15);
}

bool imu_serial_com_validate_fram_data(com_serial_imu_fram_data* framData)
{
	if(framData->accelRangeRegisterValue > 3)
		return false;
	if(framData->gyroRangeRegisterValue > 4)
		return false;
	if(framData->gyroBandwidthRegisterValue > 7)
		return false;

	return true;
}

#endif

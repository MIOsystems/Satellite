#include <DAVE.h>

#include <include/composer/composer.h>

u8 composer_init()
{
	u8 status = DAVE_STATUS_SUCCESS;


	// Communication
	status = udp_initialize();
	if(status != 0)
	{
		return status;
	}
	// Sensors
	// IMU

	DIGITAL_IO_SetOutputHigh(&CS_A);
	status = imu_init();
	if(status != BMI085X_SUCCESS)
	{
		return DAVE_STATUS_FAILURE;
	}
	return DAVE_STATUS_SUCCESS;

	// GPS Sensor, only creates the structure
	gnss_init();

}

u8 imu_init()
{
	bmi085x_init(&imu);
	u8 status = bmi085a_init(&imu);
	if(status != BMI085X_SUCCESS)
	{
		return status;
	}
	status = bmi085g_init(&imu);
	return status;
}

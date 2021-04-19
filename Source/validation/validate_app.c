#include <include/validation/validate_app.h>



void validation_app_init()
{
	validate_digital_out_init();
	validate_rs232_init();
	validate_uart_init();
	validate_rs422_init();
	validate_a_io_init();
	validate_relay_init();
}

void validation_app_run()
{
	validate_dip_update();
	validate_digital_out_update();
	validate_rs232_send();
	validate_rs422_send();
	validate_uart_send();
	validate_relay_update();
}

#include <include/validation/validate_app.h>


volatile u32 counter;
void validation_app_init()
{
	validate_digital_out_init();
	validate_rs232_init();
	validate_uart_init();
	validate_rs422_init();
	validate_a_io_init();
	validate_relay_init();
	validate_ethernet_init();
	validate_sensor_out_init();
	counter = 0;

	TIMER_Start(&POLL_TIMER);
	INTERRUPT_Enable(&RS232_INTERRUPT);
	INTERRUPT_Enable(&RS422_INTERRUPT);
	INTERRUPT_Enable(&UART_INTERRUPT);


}

void validation_app_run()
{
	validate_dip_update(&packet.dip);
	validate_digital_out_update(&packet.dout);
	validate_rs232_send();
	validate_rs422_send();
	validate_uart_send();
	validate_relay_update(&packet.relay);
	validate_sensor_out_update(&packet.sout);

	if(counter >= 250)
	{
		packet.ain.a_in_1 = ai1;
		packet.ain.a_in_2 = ai2;
		packet.ain.a_in_3 = ai3;
		validate_ethernet_update(packet);
		counter = 0;
	}
	counter++;
}

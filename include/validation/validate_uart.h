/*
 * validate_uart.h
 *
 *  Created on: 12 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_UART_H_
#define VALIDATE_UART_H_

#include <DAVE.h>
#include <include/util/types.h>

#define MAX_CHAR_RECV		32
#define MAX_CHAR_SEND		512

void validate_uart_init();
void validate_uart_update();
void validate_uart_send();

#endif /* VALIDATE_UART_H_ */

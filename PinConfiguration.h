/*
 * PinConfiguration.h
 *
 *  Created on: 30 Jan 2021
 *      Author: Patrick
 */

#ifndef PINCONFIGURATION_H_
#define PINCONFIGURATION_H_

#include <DAVE.h>


// BMI085 SPI HW
#define BMI_GPIO_PORT (XMC_GPIO_PORT_t *)	1								// Constant pointer pointing to GPIO port
#define BMI_PIN_NUMBER						XMC_GPIO_PORT1					// Port pin number
#define BMI_XMC_MODE						XMC_GPIO_MODE_OUTPUT_PUSH_PULL	// SEE XMC_GPIO_MODE_t
// BMI085 OPCODES
#define BMI_A_NORMAL_OPCODE		0x04
#define BMI_A_SUSPEND_OPCODE	0x00
#define BMI_G_NORMAL_OPCODE		0x00
#define BMI_G_SUSPEND_OPCODE	0x80
#define BMI_G_D_SUSPEND_OPCODE	0x20
#define BMI_G_DATA_OPCODE		0x12
#define BMI_A_DATA_OPCODE		0x02

#endif /* PINCONFIGURATION_H_ */

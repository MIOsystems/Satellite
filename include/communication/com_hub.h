/*
 * com_hub.h
 *
 *  Created on: 29 Apr 2021
 *      Author: Patrick
 */

#ifndef COM_HUB_H_
#define COM_HUB_H_

#include <stdbool.h>

#include <DAVE.h>
#include <include/util/types.h>
#include <include/util/model.h>
#include <include/util/error.h>
#include <include/satellite.h>

#define HUB_BUFFER_SIZE 	128
#define CAM_FRAME_START1_OPCODE		0x40
#define CAN_FRAME_START2_OPCODE		0x02

typedef enum
{
	CAN_FRAME_START0	= 0,
	CAN_FRAME_START1	= 1,
	CAN_FRAME_DEST		= 2,
	CAN_FRAME_SRC		= 3,
	CAN_FRAME_FLAGS		= 4,
	CAN_FRAME_DLC_MSB	= 5,
	CAN_FRAME_DLC_LSB	= 6,
	CAN_FRAME_PAYLOAD	= 7,
	CAN_FRAME_CRC_MSB	= 8,
	CAN_FRAME_CRC_LSB	= 9
} CanFrameStates_e;

typedef struct
{
	u8 start1;
	u8 start2;
	u8 dest;
	u8 src;
	u8 flag;
	u8 data[HUB_BUFFER_SIZE];
	BitNumbering_t dlc;
	BitNumbering_t crc;
} ComHubPacket_t;

u8 com_hub_init();
void com_hub_recv();
u8 com_hub_send(void* payload, u16 len);
void com_hub_recv_handle();
void com_hub_clear_buffer();
void com_hub_reset();


#endif

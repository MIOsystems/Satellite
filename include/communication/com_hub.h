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
#include <include/app/application.h>
#include <include/util/types.h>
#include <include/util/model.h>
#include <include/util/error.h>
#include <include/util/crc.h>
#include <include/satellite.h>

#define HUB_PAYLOAD_BUFFER_SIZE		128
#define CAN_FRAME_START1_OPCODE		0x40
#define CAN_FRAME_START2_OPCODE		0x02
#define CAN_REGUEST_FLAG			0x01


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

typedef enum
{
	CAN_REQ_EXISTENCE = 0U,
	CAN_REQ_MEASUREMENTS,
	CAN_REQ_GNSS_DATA,
	CAN_REQ_EVENTS,
	CAN_REQ_STATUS
} CANReqTypes_e;


typedef enum
{
	RM_SENSOR_INDUCTOR = 0U,
	RM_SENSOR_ALTIMETER,
} RequestMeasurementSensorID_e;

typedef enum
{
	FLAG_REQUEST = 0U,
	FLAG_COMMAND,
} FlagOptions_e;

typedef struct
{
	RequestMeasurementSensorID_e id;
	u8 size;
	u16 value;
} MeasurementPayloadPacket_t;



u8 com_hub_init();
void com_hub_recv();
u8 com_hub_send(void);
void com_hub_recv_handle();
void com_hub_clear_buffer();
void com_hub_reset();

void com_hub_create_measure_packet();


#endif

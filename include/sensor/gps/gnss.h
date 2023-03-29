#ifndef GNSS_H_
#define GNSS_H_

#include <include/satellite.h>

#ifdef UBLX

#include <stdbool.h>

#include <include/util/types.h>

#define PAYLOAD_LENGTH	(u8)	92
#define GPS_SYNC1 		(u8)	0xB5
#define GPS_SYNC2 		(u8)	0x62

static volatile bool gpsReceive_ready = false;
static volatile u8 gpsFrameCounter = 0;
static volatile u8 gpsPayloadIndex = 0;


typedef enum
{
	UBX_FRAME_SYNC1 = 0U,
	UBX_FRAME_SYNC2,
	UBX_FRAME_CLASS,
	UBX_FRAME_ID,
	UBX_FRAME_DLC1,
	UBX_FRAME_DLC0,
	UBX_FRAME_PAYLOAD,
	UBX_FRAME_CK_A,
	UBX_FRAME_CK_B
} UbxFrame_e;

typedef struct
{
	u8 class;
	u8 id;
	u16 length;
	u16 checksum_rx;
	u16 checksum_calc;
	u8 ck_a;
	u8 ck_b;
	u8 payload[PAYLOAD_LENGTH];
} UbxFrame_t;

typedef struct
{
	i32 lon;
	i32 lat;
	i32 height_ellipsoid;
	i32 height_msl;
	i32 hor_acc;
	i32 ver_acc;
	i32 speed;
	i32 heading;
	i32 speed_acc;
	i32 head_acc;
	u32 epoch;
	u8 fix;
	u8 num_sat;
} GPSValues_t;

void gnssInit();
void gnssPoll(void);
void gnssFrameReset(void);
void gnssUpdateChecksum(u8 data);
void gnssGetChecksum(void);
u8 gpsRecvHandler(void);
void gnssConvert(void);

#endif

#endif

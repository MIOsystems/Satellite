#ifndef GNSS_H_
#define GNSS_H_

#include <stdbool.h>

#include <include/util/types.h>

#define PAYLOAD_LENGTH	(u8)	92
#define GPS_SYNC1 		(u8)	0xB5
#define GPS_SYNC2 		(u8)	0x62

static volatile bool gps_receive_ready = false;
static volatile u8 gps_frame_counter = 0;
static volatile u8 gps_payload_index = 0;


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

void gnss_init();
void gnss_poll(void);
void gnss_poll_test(void);
void gnss_frame_reset(void);
void gnss_update_checksum(u8 data);
void gnss_get_checksum(void);
u8 gps_rx_handler(void);
void gnss_convert(void);

#endif

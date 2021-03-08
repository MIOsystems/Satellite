/*
 * GNSS.h
 *
 *  Created on: 22 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_GNSS_H_
#define HEADER_GNSS_H_

#include <Header/Types.h>
#include <Header/Satellite.h>
#include <Header/Sensor/GNSSUtility.h>

class GNSS
{
	private:
		typedef enum
		{
			UBX_FRAME_HEADER_1 = 0U,
			UBX_FRAME_HEADER_2,
			UBX_FRAME_CLASS,
			UBX_FRAME_ID,
			UBX_FRAME_DLC1,
			UBX_FRAME_DLC0,
			UBX_FRAME_PAYLOAD,
			UBX_FRAME_CK_A,
			UBX_FRAME_CK_B
		} UBX_Frame;

		typedef enum {
			GNSS_SUCCESS = 0,
			GNSS_NO_PAYLOAD
		} GNSS_STATUS;

		GNSSFrame gnss_frame;
		GNSSData gnss_data;

		u8 raw_data;
		u8 frame_counter;
		u8 gps_payload_index = 0;
		bool rx_ready = false;

		void validate(u8 _data, u8 _expected_data, u8 _fallback);
		void convert_payload();
	public:
		GNSS();
		u8 init();
		u8 poll();
		u8 select(u8 chip);
		u8 write(u8 addr, u8 data);
		char* to_string();

		u8 rx_handler(GNSSData &data);
};
#endif /* HEADER_GNSS_H_ */

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
#include <Header/Sensor.h>

class GNSS : public Sensor
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
		};


		GNSSFrame gnss_frame;
		u8 raw_data;
		u8 frame_counter;
		u8 gps_payload_index = 0;
		bool rx_ready = false;

		void validate(u8 _data, u8 _expected_data, u8 _fallback);
		void convert_payload();
	public:
		GNSSData gnss_data;
		GNSS();
		/**
		 * Not implemented
		 */
		u8 init() override;
		u8 poll() override;
		u8 select(u8 chip) override;
		u8 write(u8 addr, u8 data) override;
		const char* to_string() override;

		u8 rx_handler();
};
#endif /* HEADER_GNSS_H_ */

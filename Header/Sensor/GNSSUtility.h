/*
 * GNSSUtility.h
 *
 *  Created on: 22 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_SENSOR_GNSSUTILITY_H_
#define HEADER_SENSOR_GNSSUTILITY_H_

#include <array>

#include <Header/Types.h>
#include <Header/Satellite.h>

class GNSSFrame
{
	private:
		u8 class_def;
		u8 id;
		u16 length;
		u16 checksum_rx;
		u16 checksum_calc;
		u8 ck_a;
		u8 ck_b;

	public:
		GNSSFrame();
		u8 payload[GNSS_GPS_BUFF_S];
		void updateCheckSum(u8 data);
		u16 getChecksumRx() const;
		void setChecksumRx(u16 checksumRx);
		u8 getCkA() const;
		void setCkA(u8 ckA);
		u8 getCkB() const;
		void setCkB(u8 ckB);
		u8 getClassDef() const;
		void setClassDef(u8 classDef);
		u8 getId() const;
		void setId(u8 id);
		u16 getLength() const;
		void setLength(u16 length);
		void getChecksum();
		u16 getChecksumCalc() const;
		void setChecksumCalc(u16 checksumCalc);
};

class GNSSData
{
	public:
		GNSSData();
		i32 lon{0};
		i32 lat{0};
		i32 height_ellipsoid{0};
		i32 height_msl{0};
		i32 hor_acc{0};
		i32 ver_acc{0};
		i32 speed{0};
		i32 heading{0};
		i32 speed_acc{0};
		i32 head_acc{0};
		u32 epoch{0};
		u8 fix{0};
		u8 num_sat{0};

		char* to_string();
};

#endif /* HEADER_SENSOR_GNSSUTILITY_H_ */

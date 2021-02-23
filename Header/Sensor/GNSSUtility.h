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

		const char* to_string();
};

#endif /* HEADER_SENSOR_GNSSUTILITY_H_ */

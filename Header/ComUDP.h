/*
 * ComUDP.h
 *
 *  Created on: 19 Feb 2021
 *      Author: Patrick
 */

#ifndef HEADER_COMUDP_H_
#define HEADER_COMUDP_H_

#include <DAVE.h>

#include <Header/Types.h>
#include <Header/GNSS.h>
#include <Header/BMI085.h>

class ComUDP
{
	private:
		ip_addr_t addr;
		struct udp_pcb *com_ctrl;
		typedef enum {
			COM_SUCCESS = 0,
			COM_NULL_PTR
		} COM_STATUS;

		typedef struct
		{
		    char prefix[5];
		    f32 avg_x; // 4
		    u16 max_x; // 2
		    u16 min_x; // 2
		    f32 avg_y;
		    u16 max_y;
		    u16 min_y;
		    f32 avg_z;
		    u16 max_z;
		    u16 min_z;
		    f32 angle_x;
		    f32 angle_y;
		    f32 angle_z;

		} bmi_packet;

		typedef struct
		{
		    char prefix[6];
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
		} gnss_packet;

	public:
		ComUDP();
		i8 init();
		i8 send_ok();
		i8 send_gnss(GNSSData data);
		i8 send_bmi(BMI085 data);
		i8 close();
};

#endif /* HEADER_COMUDP_H_ */

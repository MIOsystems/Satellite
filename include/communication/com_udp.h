/*
 * udp.h
 *
 *  Created on: 22 Mar 2021
 *      Author: Patrick
 */

#ifndef UDP_H_
#define UDP_H_

#include <DAVE.h>
#include <include/satellite.h>

#include <include/util/types.h>
#include <include/sensor/gps/gnss.h>
#include <include/sensor/imu/bmi085x.h>

ip_addr_t addr;
struct udp_pcb *com_ctrl;

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


typedef struct
{
    char prefix[5];
    f32 avg_x;
    f32 max_x;
    f32 min_x;
    f32 avg_y;
    f32 max_y;
    f32 min_y;
    f32 avg_z;
    f32 max_z;
    f32 min_z;
    f32 angle_x;
    f32 angle_y;
    f32 angle_z;
} imu_packet;


typedef struct
{
	f32 Ax;
	f32 Ay;
	f32 Az;
	f32 Gx;
	f32 Gy;
	f32 Gz;
    f32 angleX;
    f32 angleY;
    f32 angleZ;
} imu_debug_packet;

i8 udp_initialize();
i8 udp_send_gps(gps_values_t data);
i8 udp_send_bmi(bmi085x data);
i8 udp_send_debug_bmi(bmi085x data);


#endif /* UDP_H_ */

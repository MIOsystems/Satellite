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
#include <include/sensor/imu/bmi085/bmi085x.h>
#include <include/sensor/proximity/proximity_switch.h>
#include <include/sensor/altimeter/altimeter.h>
#include <include/transformation/fft.h>
#include <include/app/application.h>
#include <include/math/vector.h>

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
} GnssPacket_t;


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
} InertialMeasurementUnitPacket_t;


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
    f32 complimentAngleX;
    f32 complimentAngleY;
    f32 complimentAngleZ;
} IMUDebugPacket_t;

typedef struct
{
	char prefix[8];
	i32 distance;
	u32 sum;
	u32 counter;
} AltimeterPacket_t;

typedef struct
{
	char prefix[8];
	proximity_switch_t data;
} ProximityPacket_t;

typedef struct
{
	char prefix[8];
	f32 data[FFT_N];
} FFTPacket_t;

typedef struct
{
	char prefix[8];
	void *data;
} UDPPacket_t;

i8 udp_initialize();
#ifdef UBLX
i8 udp_send_gps(GPSValues_t data);
#endif
#ifdef BMI085
i8 udp_send_bmi(bmi085x data);
i8 udp_send_debug_bmi(bmi085x data);
i8 udp_send_proximity(proximity_switch_t data);
#endif
i8 udp_send_packet(void* data, size_t size, char* prefix);
i8 udp_send_altimeter(AltimeterData_t data);

//i8 udp_send_spectrum(cplxf *data, char* specifier);
i8 udp_send_spectrum(kiss_fft_cpx *data, char* specifier);
#endif /* UDP_H_ */

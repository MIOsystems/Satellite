/*
 * GNSSUtility.cpp
 *
 *  Created on: 22 Feb 2021
 *      Author: Patrick
 */

#include <array>
#include <stdio.h>
#include <stdlib.h>

#include <Header/Sensor/GNSSUtility.h>
#include <Header/Satellite.h>

GNSSFrame::GNSSFrame()
{
	this->class_def = 0;
	this->id = 0;
	this->length = 0;
	this->checksum_rx = 0;
	this->checksum_calc = 0;
	this->ck_a = 0;
	this->ck_b = 0;
}

// GNSDATA
GNSSData::GNSSData() {
	this->epoch = 0;
	this->fix = 0;
	this->num_sat = 0;
	this->lon = 0;
	this->lat = 0;
	this->height_ellipsoid = 0;
	this->height_msl = 0;
	this->hor_acc = 0;
	this->ver_acc = 0;
	this->speed = 0;
	this->heading = 0;
	this->speed_acc = 0;
	this->head_acc = 0;
}

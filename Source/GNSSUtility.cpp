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
u16 GNSSFrame::getChecksumRx() const
{
	return checksum_rx;
}

void GNSSFrame::setChecksumRx(u16 checksumRx)
{
	checksum_rx = checksumRx;
}
u8 GNSSFrame::getCkA() const
{
	return ck_a;
}

void GNSSFrame::setCkA(u8 ckA)
{
	ck_a = ckA;
}

u8 GNSSFrame::getCkB() const
{
	return ck_b;
}

void GNSSFrame::setCkB(u8 ckB)
{
	ck_b = ckB;
}

u8 GNSSFrame::getClassDef() const
{
	return class_def;
}

void GNSSFrame::setClassDef(u8 classDef)
{
	class_def = classDef;
}

u8 GNSSFrame::getId() const
{
	return id;
}

void GNSSFrame::setId(u8 _id)
{
	this->id = _id;
}

u16 GNSSFrame::getLength() const
{
	return length;
}

void GNSSFrame::setLength(u16 _length)
{
	this->length = _length;
}


void GNSSFrame::updateCheckSum(u8 data) {
	this->ck_a = (u8) (this->ck_a + data);
	this->ck_b = (u8) (this->ck_b + this->ck_a);
}

u16 GNSSFrame::getChecksumCalc() const
{
	return checksum_calc;
}

void GNSSFrame::setChecksumCalc(u16 checksumCalc)
{
	checksum_calc = checksumCalc;
}

void GNSSFrame::getChecksum() {
	this->checksum_calc = this->ck_a;
	this->checksum_calc |= this->ck_b << 8;
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

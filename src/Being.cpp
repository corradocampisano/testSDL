/*
 * Being.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#include "Being.h"

#include <iostream>
#include <sstream> // for ostringstream
#include <string>


Being::Being() {
	this->weight=1;
}

Being::Being(int weight) {
	this->weight=weight;
}

Being::~Being() {
	// TODO Auto-generated destructor stub
}

double Being::getPosX(void) {
	return posX;
}
double Being::getPosY(void) {
	return posY;
}
double Being::getPosZ(void) {
	return posZ;
}
double Being::getVelX(void) {
	return velX;
}
double Being::getVelY(void) {
	return velY;
}
double Being::getVelZ(void) {
	return velZ;
}
double Being::getAccX(void) {
	return accX;
}
double Being::getAccY(void) {
	return accY;
}
double Being::getAccZ(void) {
	return accZ;
}


void Being::setPosX(double x) {
	posX = x;
}
void Being::setPosY(double y) {
	posY = y;
}
void Being::setPosZ(double z) {
	posZ = z;
}
void Being::setVelX(double x) {
	velX = x;
}
void Being::setVelY(double y) {
	velY = y;
}
void Being::setVelZ(double z) {
	velZ = z;
}
void Being::setAccX(double x) {
	accX = x;
}
void Being::setAccY(double y) {
	accY = y;
}
void Being::setAccZ(double z) {
	accZ = z;
}



std::string Being::toString(void) {

	std::ostringstream ret;
	ret << "P (" << posX << "," << posY << "," << posZ << ")";
	ret << "\t\tV (" << velX << "," << velY << "," << velZ << ")";
	ret << "\t\tA (" << accX << "," << accY << "," << accZ << ")";

	return ret.str();
}

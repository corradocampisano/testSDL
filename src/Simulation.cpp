/*
 * Simulation.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#include "Simulation.h"

#include "Constants.h"

#include <math.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>

using namespace std;

vector<vector<double> > distancesArr;

ofstream myfile;

double const G_FACTOR = 0.05;

Simulation::Simulation(unsigned beings) {

	if (beings > 0) {
		// file to log positions to
		myfile.open("logs.txt");

		// setup distance matrix
		distancesArr.resize(beings);
		for (unsigned i = 0; i < beings; i++) {
			distancesArr[i].resize(beings);
		}

		setupBeings(beings);

		cout << "Check startup conditions..." << "\n";
		for (unsigned i = 0; i < beingsArr.size(); i++) {
			Being curr = beingsArr.at(i);
			cout << curr.toString() << '\n';
		}

		cout << "init ok!!!" << "\n";

		// setup baricentre
		baricentre = new Being((int) beings);

		baricentre->setAccX(0);
		baricentre->setAccY(0);
		baricentre->setAccZ(0);

		baricentre->setVelX(0);
		baricentre->setVelY(0);
		baricentre->setVelZ(0);

		updateBaricentre();

		cout << "baricentre in : " << "\n";
		cout << baricentre->toString() << "\n\n";

	} else {
		cout << "initing as replay, shall refactor this...";
	}
}

Simulation::~Simulation() {
	// close data file
	myfile.close();
}

std::vector<Being> Simulation::getBeings() {
	return beingsArr;
}

void Simulation::move(void) {
	moveWithDistanceMatrix();
	updateBaricentre();
}

Being* Simulation::getBaricentre(void) {
	return baricentre;
}

void Simulation::setupBeings(unsigned beings) {

	// first loop

	{
		Being *curr = new Being();

		curr->setPosX(-4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.1+0.1);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(-6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(-0.1+0.1);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// second loop
	if (beings < 4)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(-0.1-0.1);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.1-0.1);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.1
	if (beings < 5)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(20.0);
		curr->setPosY(0.26);
		curr->setPosZ(20.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.2
	if (beings < 6)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(-16.0);
		curr->setPosY(-0.26);
		curr->setPosZ(-16.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}
}




/*

void setupNiceButMoving(unsigned beings) {

	// first loop

	{
		Being *curr = new Being();

		curr->setPosX(-4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.1+0.1);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(-6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(-0.1+0.1);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// second loop
	if (beings < 4)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(-0.1-0.1);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.1-0.1);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.1
	if (beings < 5)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(20.0);
		curr->setPosY(0.26);
		curr->setPosZ(20.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.2
	if (beings < 6)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(-16.0);
		curr->setPosY(-0.26);
		curr->setPosZ(-16.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}
}



void setupPlainSfigatto(unsigned beings) {

	// first loop

	{
		Being *curr = new Being();

		curr->setPosX(-4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.1+0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(-6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(-0.1+0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// second loop
	if (beings < 4)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(-0.1-0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.1-0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.1
	if (beings < 5)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(20.0);
		curr->setPosY(0.26);
		curr->setPosZ(20.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.2
	if (beings < 6)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(-16.0);
		curr->setPosY(-0.26);
		curr->setPosZ(-16.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}
}



void setupExploderer(unsigned beings) {

	// first loop

	{
		Being *curr = new Being();

		curr->setPosX(-4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.1+0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(-6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(-0.1+0.08);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// second loop
	if (beings < 4)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(4.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(-0.1-0.08);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	{
		Being *curr = new Being();

		curr->setPosX(6.0);
		curr->setPosY(2.0);
		curr->setPosZ(0.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.1-0.08);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.1
	if (beings < 5)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(20.0);
		curr->setPosY(0.26);
		curr->setPosZ(20.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}

	// unwanted n.2
	if (beings < 6)
		return;
	{
		Being *curr = new Being();

		curr->setPosX(-16.0);
		curr->setPosY(-0.26);
		curr->setPosZ(-16.0);

		curr->setVelX(0.0);
		curr->setVelY(0.0);
		curr->setVelZ(0.0);

		curr->setAccX(0.0);
		curr->setAccY(0.0);
		curr->setAccZ(0.0);

		//cout << curr->toString() << '\n'; //
		beingsArr.push_back(*curr);
	}
}


 void setupSfigatto(unsigned beings) {
 // first loop

 {
 Being *curr = new Being();

 curr->setPosX(-4.0);
 curr->setPosY(2.0);
 curr->setPosZ(0.0);

 curr->setVelX(0.0);
 curr->setVelY(0.1);
 curr->setVelZ(-0.08);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }

 {
 Being *curr = new Being();

 curr->setPosX(-6.0);
 curr->setPosY(2.0);
 curr->setPosZ(0.0);

 curr->setVelX(0.0);
 curr->setVelY(-0.1);
 curr->setVelZ(-0.08);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }

 // second loop
 if (beings < 4)
 return;
 {
 Being *curr = new Being();

 curr->setPosX(4.0);
 curr->setPosY(2.0);
 curr->setPosZ(0.0);

 curr->setVelX(0.0);
 curr->setVelY(-0.1);
 curr->setVelZ(0.08);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }

 {
 Being *curr = new Being();

 curr->setPosX(6.0);
 curr->setPosY(2.0);
 curr->setPosZ(0.0);

 curr->setVelX(0.0);
 curr->setVelY(0.1);
 curr->setVelZ(0.08);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }

 // unwanted n.1
 if (beings < 5)
 return;
 {
 Being *curr = new Being();

 curr->setPosX(20.0);
 curr->setPosY(0.26);
 curr->setPosZ(20.0);

 curr->setVelX(0.0);
 curr->setVelY(0.0);
 curr->setVelZ(0.0);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }

 // unwanted n.2
 if (beings < 6)
 return;
 {
 Being *curr = new Being();

 curr->setPosX(-15.0);
 curr->setPosY(-0.26);
 curr->setPosZ(-13.0);

 curr->setVelX(0.0);
 curr->setVelY(0.0);
 curr->setVelZ(0.0);

 curr->setAccX(0.0);
 curr->setAccY(0.0);
 curr->setAccZ(0.0);

 //cout << curr->toString() << '\n'; //
 beingsArr.push_back(*curr);
 }
 }
 */

void Simulation::updateBaricentre(void) {

	myfile << a_tom::Constants::LOG_STEP_SEPARATOR << "\n";

	unsigned beings = beingsArr.size();
	double posX = 0, posY = 0, posZ = 0;
	for (unsigned i = 0; i < beings; i++) {
		Being curr = beingsArr.at(i);
		posX += curr.getPosX() / beings;
		posY += curr.getPosY() / beings;
		posZ += curr.getPosZ() / beings;

		myfile << curr.getPosX() << "\t" << curr.getPosY() << "\t"
				<< curr.getPosZ() << "\n";
		//myfile << curr.toString() << "\n";
	}
	baricentre->setPosX(posX);
	baricentre->setPosY(posY);
	baricentre->setPosZ(posZ);

	//cout << "baricentre in : " << "\n";
	//cout << baricentre->toString() << "\n\n";
}

void Simulation::moveWithDistanceMatrix(void) {
	//cout << " moving! " << '\n';

	/*
	 * calculate distances and accelerations
	 *
	 * the one below is the first implementation
	 * which calculates all distances matrix
	 *
	 for (unsigned i = 0; i < beingsArr.size(); i++) {

	 Being I = beingsArr.at(i);

	 for (unsigned j = 0; j < beingsArr.size(); j++) {

	 if(i!=j) {
	 Being J = beingsArr.at(j);

	 double x2 = pow( (I.getPosX() - J.getPosX()), 2.0 );
	 double y2 = pow( (I.getPosY() - J.getPosY()), 2.0 );
	 double z2 = pow( (I.getPosZ() - J.getPosZ()), 2.0 );

	 double distIJ = sqrt(x2+y2+z2);

	 distancesArr[i][j] = distIJ;
	 }
	 }
	 }
	 *
	 * calculate distances and accelerations
	 *
	 * the one below is the reviewed implementation
	 * which only calculates a half of the distances
	 * matrix, and get the other half by simmetry
	 */
	for (unsigned i = 0; i < beingsArr.size(); i++) {

		Being I = beingsArr.at(i);

		for (unsigned j = i + 1; j < beingsArr.size(); j++) {

			if (i != j) {
				Being J = beingsArr.at(j);

				double x2 = pow((I.getPosX() - J.getPosX()), 2.0);
				double y2 = pow((I.getPosY() - J.getPosY()), 2.0);
				double z2 = pow((I.getPosZ() - J.getPosZ()), 2.0);

				double distIJ = sqrt(x2 + y2 + z2);

				distancesArr[i][j] = distIJ;
				distancesArr[j][i] = distIJ;
			}
		}
	}

	/* calculate accelerations */
	for (unsigned i = 0; i < beingsArr.size(); i++) {

		Being curr = beingsArr.at(i);

		double ax = 0;
		double ay = 0;
		double az = 0;

		for (unsigned j = 0; j < beingsArr.size(); j++) {

			if (i != j && distancesArr[i][j] != 0.0) {
				Being other = beingsArr.at(j);

				ax += G_FACTOR * (other.getPosX() - curr.getPosX())
						/ pow(distancesArr[i][j], 3.0);
				ay += G_FACTOR * (other.getPosY() - curr.getPosY())
						/ pow(distancesArr[i][j], 3.0);
				az += G_FACTOR * (other.getPosZ() - curr.getPosZ())
						/ pow(distancesArr[i][j], 3.0);
			}
		}

		curr.setAccX(ax);
		curr.setAccY(ay);
		curr.setAccZ(az);

		beingsArr.at(i) = curr;
	}

	/* do movement */
	for (unsigned i = 0; i < beingsArr.size(); i++) {
		Being curr = beingsArr.at(i);

		curr.setVelX(curr.getVelX() + curr.getAccX());
		curr.setVelY(curr.getVelY() + curr.getAccY());
		curr.setVelZ(curr.getVelZ() + curr.getAccZ());

		curr.setPosX(curr.getPosX() + curr.getVelX());
		curr.setPosY(curr.getPosY() + curr.getVelY());
		curr.setPosZ(curr.getPosZ() + curr.getVelZ());

		beingsArr.at(i) = curr;
		//cout << curr.toString() << '\n';
	}
}


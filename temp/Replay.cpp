/*
 * Simulation.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#include "Replay.h"

#include <math.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>

using namespace std;


void loadBeings(bool startup, unsigned beings);


Replay::Replay(unsigned beings) : Simulation(0) {

	//this->Simulation(0);

	loadBeings(true, beings);

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
}

Replay::~Replay() {

}

std::vector<Being> Simulation::getBeings() {
	return beingsArr;
}

void Replay::move(void) {
	loadBeings(false, beingsArr.size());
	updateBaricentre();
}


void loadBeings(bool startup, unsigned beings) {

	/* reads positions from file */
	for (unsigned i = 0; i < beingsArr.size(); i++) {

		double x = 0;
		double y = 0;
		double z = 0;

		if (startup) {

			Being *curr = new Being();

			curr->setPosX(x);
			curr->setPosY(y);
			curr->setPosZ(z);

			curr->setVelX(0.0);
			curr->setVelY(0.0);
			curr->setVelZ(0.0);

			curr->setAccX(0.0);
			curr->setAccY(0.0);
			curr->setAccZ(0.0);

			//cout << curr->toString() << '\n';
			beingsArr.push_back(*curr);

		} else {

			Being curr = beingsArr.at(i);

			curr.setAccX(x);
			curr.setAccY(y);
			curr.setAccZ(z);

			beingsArr.at(i) = curr;
		}

	}
}


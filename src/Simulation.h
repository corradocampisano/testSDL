/*
 * Simulation.h
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#ifndef Simulation_H_
#define Simulation_H_


#include "Being.h"
#include <vector>


class Simulation {

public:
	Simulation(unsigned);
	virtual ~Simulation();

	std::vector<Being> getBeings(void);
	Being* getBaricentre(void);

	void move(void);


protected:
	std::vector<Being> beingsArr;
	Being *baricentre;

	void updateBaricentre(void);


private:
	void setupBeings(unsigned beings);
	void moveWithDistanceMatrix(void);

};

#endif /* Simulation_H_ */

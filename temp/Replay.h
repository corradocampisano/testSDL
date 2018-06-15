/*
 * Simulation.h
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#ifndef Replay_H_
#define Replay_H_


#include "Being.h"

#include "Simulation.h"

#include <vector>


class Replay : public Simulation {
public:
	Replay(unsigned);
	virtual ~Replay();

	/*
	 * shall inherit
	std::vector<Being> getBeings(void);
	Being* getBaricentre(void);

	void move(void);
	*/
};

#endif /* Simulation_H_ */

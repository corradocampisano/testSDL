/*
 * Being.h
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#ifndef Being_H_
#define Being_H_

#include <cstdlib>
#include <string>

class Being {

private:
	int weight;

	double posX;
	double posY;
	double posZ;

	double velX;
	double velY;
	double velZ;

	double accX;
	double accY;
	double accZ;

public:
	Being();
	Being(int);
	virtual ~Being();

	double getPosX(void);
	double getPosY(void);
	double getPosZ(void);

	double getVelX(void);
	double getVelY(void);
	double getVelZ(void);

	double getAccX(void);
	double getAccY(void);
	double getAccZ(void);

	void setPosX(double);
	void setPosY(double);
	void setPosZ(double);

	void setVelX(double);
	void setVelY(double);
	void setVelZ(double);

	void setAccX(double);
	void setAccY(double);
	void setAccZ(double);

	std::string toString(void);
};

#endif /* Being_H_ */

#ifndef __ENEMYROBOT_H
#define __ENEMYROBOT_H

#include "Robot.h"

class EnemyRobot : public Robot // enemy robot, extends robot class 
{
private:
	int walkingSpeed;//speed of the robots walk
	
public:
	EnemyRobot();
	virtual ~EnemyRobot();

	//getters and setters for robots walking speed
	void setWalkingSpeed(int aSpeed);
	int getWalkingSpeed();
};

#endif
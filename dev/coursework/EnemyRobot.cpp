#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "EnemyRobot.h"

EnemyRobot::EnemyRobot()
{
}

EnemyRobot::~EnemyRobot()
{
}

void EnemyRobot::setWalkingSpeed(int aSpeed)
{
	walkingSpeed = aSpeed;
}

int EnemyRobot::getWalkingSpeed()
{
	return walkingSpeed;
}
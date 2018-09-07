#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

GLfloat GameObject::getXPos()
{
	return xPos;
}

void GameObject::setXPos(GLfloat aXPos)
{
	xPos = aXPos;
}

GLfloat GameObject::getYPos()
{
	return yPos;
}

void GameObject::setYPos(GLfloat aYPos)
{
	yPos = aYPos;
}

GLfloat GameObject::getZPos()
{
	return zPos;
}

void GameObject::setZPos(GLfloat aZPos)
{
	zPos = aZPos;
}

GLfloat GameObject::getRotationAngle()
{
	return rotationAngle;
}

void GameObject::setRotationAngle(GLfloat aRotationAngle)
{
	rotationAngle = aRotationAngle;
}
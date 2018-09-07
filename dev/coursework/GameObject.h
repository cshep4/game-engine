#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

class GameObject // base object class used for anything with a postion in the level
{
protected:
	GLfloat rotationAngle; // angle of rotation for the direction of the object

	GLfloat xPos; // position of the object
	GLfloat yPos;
	GLfloat zPos;
public:
	GameObject();
	virtual ~GameObject();

	//getter and setter for rotation angle
	GLfloat getRotationAngle();
	void setRotationAngle(GLfloat aRotationAngle);

	//getters and setters for position
	GLfloat getXPos();
	void setXPos(GLfloat aXPos);
	GLfloat getYPos();
	void setYPos(GLfloat aYPos);
	GLfloat getZPos();
	void setZPos(GLfloat aZPos);
};

#endif
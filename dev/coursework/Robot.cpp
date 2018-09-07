#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "Robot.h"

Robot::Robot()
{
	armAngles[kLeft] = 0.0;//reset robot to default state
	armAngles[kRight] = 0.0;
	legAngles[kLeft] = 0.0;
	legAngles[kRight] = 0.0;

	armStates[kLeft] = kForwardState;
	armStates[kRight] = kBackwardState;

	legStates[kLeft] = kForwardState;
	legStates[kRight] = kBackwardState;

	rotationAngle = 0.0f;

	xPos = 0.0f;//initialise deafult position if none is loaded in
	yPos = 0.0f;
	zPos = -30.0f;
}

Robot::~Robot()
{
}

void Robot::drawArm(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();
		glTranslatef(aXPos, aYPos, aZPos);
		glScalef(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
		drawCube(0.0f, 0.0f, 0.0f,armTexture);
	glPopMatrix();
}

void Robot::drawHead(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);	// white
		glTranslatef(aXPos, aYPos, aZPos);
		glScalef(2.0f, 2.0f, 2.0f);		// head is a 2x2x2 cube
		drawCube(0.0f, 0.0f, 0.0f, headTexture);
	glPopMatrix();
}

void Robot::drawTorso(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();
		glTranslatef(aXPos, aYPos, aZPos);
		glScalef(3.0f, 5.0f, 2.0f);		// torso is a 3x5x2 cube
		drawCube(0.0f, 0.0f, 0.0f, chestTexture);
	glPopMatrix();
}

void Robot::drawLeg(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();
		glTranslatef(aXPos, aYPos, aZPos);
		
		// draw the foot
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			drawFoot(0.0f, -5.0f, 0.0f);
		glPopMatrix();		
		
		glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
		drawCube(0.0f, 0.0f, 0.0f, legTexture);
	glPopMatrix();
}

void Robot::drawFoot(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();
		glTranslatef(aXPos, aYPos, aZPos);
		glScalef(1.0f, 0.5f, 3.0f);
		drawCube(0.0f, 0.0f, 0.0f, footTexture);
	glPopMatrix();
}

void Robot::drawRobot(float aXPos, float aYPos, float aZPos)
{
	glPushMatrix();	
		glTranslatef(aXPos, aYPos, aZPos);	// draw robot at desired coordinates

		// draw head and torso parts
		drawHead(1.0f, 2.0f, 0.0f);		
		drawTorso(1.5f, 0.0f, 0.0f);

		// move the left arm away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngles[kLeft], 1.0f, 0.0f, 0.0f);
			drawArm(2.5f, 0.0f, -0.5f);
		glPopMatrix();

		// move the right arm away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngles[kRight], 1.0f, 0.0f, 0.0f);
			drawArm(-1.5f, 0.0f, -0.5f);
		glPopMatrix();

		// move the left leg away from the torso and rotate it to give "walking" effect
		glPushMatrix();					
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[kLeft], 1.0f, 0.0f, 0.0f);
			drawLeg(-0.5f, -5.0f, -0.5f);
		glPopMatrix();

		// move the right leg away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[kRight], 1.0f, 0.0f, 0.0f);
			drawLeg(1.5f, -5.0f, -0.5f);
		glPopMatrix();

	glPopMatrix();	// pop back to original coordinate system
}

void Robot::prepare(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == kForwardState)
			armAngles[side] += 100.0f * dt;
		else
			armAngles[side] -= 100.0f * dt;

		// change state if exceeding angles
		if (armAngles[side] >= 15.0f)
			armStates[side] = kBackwardState;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = kForwardState;

		// legs
		if (legStates[side] == kForwardState)
			legAngles[side] += 100.0f * dt;
		else
			legAngles[side] -= 100.0f * dt;

		// change state if exceeding angles
		if (legAngles[side] >= 15.0f)
			legStates[side] = kBackwardState;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = kForwardState;		
	}
}

bool Robot::getMove()
{
	return move;
}

void Robot::setMove(bool aMove)
{
	move = aMove;
}

string Robot::getFaceTextureFile()
{
	return faceHeadTextureFile;
}

void Robot::setFaceTextureFile(string aFaceTextureFile)
{
	faceHeadTextureFile = aFaceTextureFile;
}

string Robot::getBackHeadTextureFile()
{
	return backHeadTextureFile;
}

void Robot::setBackHeadTextureFile(string aBackHeadTextureFile)
{
	backHeadTextureFile = aBackHeadTextureFile;
}

string Robot::getLeftHeadTextureFile()
{
	return leftHeadTextureFile;
}

void Robot::setLeftHeadTextureFile(string aLeftHeadTextureFile)
{
	leftHeadTextureFile = aLeftHeadTextureFile;
}

string Robot::getRightHeadTextureFile()
{
	return rightHeadTextureFile;
}

void Robot::setRightHeadTextureFile(string aRightHeadTextureFile)
{
	rightHeadTextureFile = aRightHeadTextureFile;
}

string Robot::getTopHeadTextureFile()
{
	return topHeadTextureFile;
}

void Robot::setTopHeadTextureFile(string aTopHeadTextureFile)
{
	topHeadTextureFile = aTopHeadTextureFile;
}

string Robot::getBottomHeadTextureFile()
{
	return bottomHeadTextureFile;
}

void Robot::setBottomHeadTextureFile(string aBottomHeadTextureFile)
{
	bottomHeadTextureFile = aBottomHeadTextureFile;
}

string Robot::getTopArmTextureFile()
{
	return armTopTextureFile;
}

void Robot::setTopArmTextureFile(string aTopArmTextureFile)
{
	armTopTextureFile = aTopArmTextureFile;
}

string Robot::getArmTextureFile()
{
	return armTextureFile;
}

void Robot::setArmTextureFile(string aArmTextureFile)
{
	armTextureFile = aArmTextureFile;
}

string Robot::getBottomArmTextureFile()
{
	return armBottomTextureFile;
}

void Robot::setBottomArmTextureFile(string aArmBottomTextureFile)
{
	armBottomTextureFile = aArmBottomTextureFile;
}

string Robot::getChestTextureFile()
{
	return chestTextureFile;
}

void Robot::setChestTextureFile(string aChestTextureFile)
{
	chestTextureFile = aChestTextureFile;
}

string Robot::getLegTextureFile()
{
	return legTextureFile;
}

void Robot::setLegTextureFile(string aLegTextureFile)
{
	legTextureFile = aLegTextureFile;
}

string Robot::getFootTextureFile()
{
	return footTextureFile;
}

void Robot::setFootTextureFile(string aFootTextureFile)
{
	footTextureFile = aFootTextureFile;
}

string Robot::getRobotPositionString()
{
	//set up text report position string
	stringstream result;
	result << "Player Pos: x=" << xPos << ", z=" << zPos;
	std::string stringResult = result.str(); 
	return stringResult;
}

void Robot::createTextures()
{
	//set up all textures for robot body
	glDeleteTextures(1,headTexture); // clear previous textures out of memory
	headTexture[0] = setTexture(faceHeadTextureFile);
	headTexture[1] = setTexture(topHeadTextureFile);
	headTexture[2] = setTexture(rightHeadTextureFile);
	headTexture[3] = setTexture(bottomHeadTextureFile);
	headTexture[4] = setTexture(leftHeadTextureFile);
	headTexture[5] = setTexture(backHeadTextureFile);

	glDeleteTextures(1,armTexture); 
	armTexture[0] = setTexture(armTextureFile);
	armTexture[1] = setTexture(armTopTextureFile);
	armTexture[2] = armTexture[0];
	armTexture[3] = setTexture(armBottomTextureFile);
	armTexture[4] = armTexture[0];
	armTexture[5] = armTexture[0];

	glDeleteTextures(1,chestTexture); 
	chestTexture[0] = setTexture(chestTextureFile);
	chestTexture[1] = chestTexture[0];
	chestTexture[2] = chestTexture[0];
	chestTexture[3] = chestTexture[0];
	chestTexture[4] = chestTexture[0];
	chestTexture[5] = chestTexture[0];

	glDeleteTextures(1,legTexture); 
	legTexture[0] = setTexture(legTextureFile);
	legTexture[1] = legTexture[0];
	legTexture[2] = legTexture[0];
	legTexture[3] = legTexture[0];
	legTexture[4] = legTexture[0];
	legTexture[5] = legTexture[0];

	glDeleteTextures(1,footTexture); 
	footTexture[0] = setTexture(footTextureFile);
	footTexture[1] = footTexture[0];
	footTexture[2] = footTexture[0];
	footTexture[3] = footTexture[0];
	footTexture[4] = footTexture[0];
	footTexture[5] = footTexture[0];
}
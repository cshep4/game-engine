#ifndef __ROBOT_H
#define __ROBOT_H

#include <string>
#include <vector>
#include <sstream>
//#include <SFML/Graphics/Texture.hpp>
#include "GameObject.h"
#include "CubeObject.h"

using namespace std;

// constants for arm and leg movement states
const char kBackwardState = 0;
const char kForwardState  = 1;

// index constants for accessing arm and leg array data
const char kLeft  = 0;
const char kRight = 1;

class Robot : public CubeObject // class used for robot character, inherits from CubeObject
{
protected:
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	bool move; // if true the robot will animate

	//texture file names
	string faceHeadTextureFile;
	string leftHeadTextureFile;
	string rightHeadTextureFile;
	string backHeadTextureFile;
	string topHeadTextureFile;
	string bottomHeadTextureFile;

	string armTopTextureFile;
	string armTextureFile;
	string armBottomTextureFile;

	string chestTextureFile;
	string legTextureFile;
	string footTextureFile;

	//textures for each body part
	GLuint headTexture[6];
	GLuint armTexture[6];
	GLuint chestTexture[6];
	GLuint legTexture[6];
	GLuint footTexture[6];

private:
	// methods to draw the parts of the robot
	void drawArm(float aXPos, float aYPos, float aZPos);
	void drawHead(float aXPos, float aYPos, float aZPos);
	void drawTorso(float aXPos, float aYPos, float aZPos);
	void drawLeg(float aXPos, float aYPos, float aZPos);
	void drawFoot(float aXPos, float aYPos, float aZPos);

public:

	Robot();
	virtual ~Robot();

	// draws the entire robot
	void drawRobot(float aXPos, float aYPos, float aZPos);

	// updates the robot animation data
	void prepare(float dt);

	//getter and setter for move boolean
	bool getMove();
	void setMove(bool aMove);

	//getters and settings for texture file names
	string getFaceTextureFile();
	void setFaceTextureFile(string aFaceTextureFile);
	string getBackHeadTextureFile();
	void setBackHeadTextureFile(string aBackHeadTextureFile);
	string getLeftHeadTextureFile();
	void setLeftHeadTextureFile(string aLeftHeadTextureFile);
	string getRightHeadTextureFile();
	void setRightHeadTextureFile(string aRightHeadTextureFile);
	string getTopHeadTextureFile();
	void setTopHeadTextureFile(string aTopHeadTextureFile);
	string getBottomHeadTextureFile();
	void setBottomHeadTextureFile(string aBottomHeadTextureFile);

	string getArmTextureFile();
	void setArmTextureFile(string aArmTextureFile);
	string getTopArmTextureFile();
	void setTopArmTextureFile(string aTopArmTextureFile);
	string getBottomArmTextureFile();
	void setBottomArmTextureFile(string aBottomArmTextureFile);

	string getChestTextureFile();
	void setChestTextureFile(string aChestTextureFile);

	string getLegTextureFile();
	void setLegTextureFile(string aLegTextureFile);

	string getFootTextureFile();
	void setFootTextureFile(string aFootTextureFile);

	void createTextures();// create all robot textures using file names

	string getRobotPositionString();//position string for text reports
};


#endif
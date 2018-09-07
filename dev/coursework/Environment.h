#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <string>
#include <vector>
#include <sstream>
#include "TextureObject.h"

using namespace std;

class Building;
class CubeObject;

class Environment : public TextureObject// class used to draw level including ground and buildings
{
private:
	GLfloat levelWidth;//width of map
	GLfloat levelDepth;//depth of map
	GLfloat levelBottomY;//y coordinate of level bottom
	GLfloat levelTopY;//y coordinate of level top

	string groundTextureFile;//ground texure file name

	GLuint groundTexture;//ground texture

public:
	Environment();
	virtual ~Environment();

	void drawEnvironment(); // draw level
	void drawGround(); // draw ground

	// setters for size of level
	void setLevelWidth(GLfloat aLevelWidth);
	void setLevelDepth(GLfloat aLevelDepth);
	void setLevelBottomY(GLfloat aLevelBottomY);
	void setLevelTopY(GLfloat aLevelTopY);

	vector< Building* > building; // vector of buildings in the level

	// getter and setter for ground texture file name
	string getGroundTextureFile();
	void setGroundTextureFile(string aGroundTextureFile);


	void addBuilding();// add new building to vector
	void addWallTexture(int aIndex);//add wall texture to building

	string getMapSizeString();//get map size string for text report

	void createTextures();//create textures for ground and buildings
};

#endif
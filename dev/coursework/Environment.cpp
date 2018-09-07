#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "Environment.h"
#include "Building.h"
#include "CubeObject.h"

Environment::Environment()
{
	levelDepth = 20000.0;//default ground size if none are read in
	levelWidth = 8000.0;
	levelBottomY = -100;
	levelTopY = 80;

	building.clear(); //initialise to nothing as there are no buildings yet
}

Environment::~Environment()
{
}

void Environment::drawEnvironment()
{
	drawGround();
	for (int i = 0; i < building.size(); i++)// for each building stored, draw
	{
		building[i]->drawBuilding();
	}
}

void Environment::drawGround()
{
	glTranslatef(0,-12,100);	
	//glColor3f(1.0f, 1.0f, 1.0f); // orange
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glBindTexture(GL_TEXTURE_2D,groundTexture);
    glBegin(GL_QUADS);
		glNormal3d(0, 1, 0);
		//bottom left
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-levelWidth/2, levelBottomY, levelDepth/2);
		//bottom right
		glTexCoord2f(1.0f, 1.0f); glVertex3f(levelWidth/2, levelBottomY, levelDepth/2);
		//top right
		glTexCoord2f(0.0f, 1.0f); glVertex3f(levelWidth/2, levelTopY, -levelDepth/2);
		//top left
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-levelWidth/2, levelTopY, -levelDepth/2);
	glEnd();
}

void Environment::setLevelWidth(GLfloat aLevelWidth)
{
	levelWidth = aLevelWidth;
}

void Environment::setLevelDepth(GLfloat aLevelDepth)
{
	levelDepth = aLevelDepth;
}

void Environment::setLevelBottomY(GLfloat aLevelBottomY)
{
	levelBottomY = aLevelBottomY;
}

void Environment::setLevelTopY(GLfloat aLevelTopY)
{
	levelTopY = aLevelTopY;
}

string Environment::getGroundTextureFile()
{
	return groundTextureFile;
}

void Environment::setGroundTextureFile(string aGroundTextureFile)
{
	groundTextureFile = aGroundTextureFile;
}

void Environment::addBuilding()
{
	building.push_back(new Building);// add new building to the building vector
}

string Environment::getMapSizeString()
{
	stringstream result;// get the text string for the size of the map
	result << "Map Dimensions: " << levelWidth << "x" << levelDepth;
	std::string stringResult = result.str(); 
	return stringResult;
}

void Environment::createTextures()
{
	groundTexture = setTexture(groundTextureFile);// set the ground texture
}
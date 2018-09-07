#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "Building.h"

Building::Building()
{
}

Building::~Building()
{
}

void Building::drawBuilding()
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(width, height, depth);
		drawCube(0.0f, 0.0f, 0.0f, texture);
	glPopMatrix();
}

string Building::getFrontTextureFile()
{
	return frontTextureFile;
}

void Building::setFrontTextureFile(string aTextureFile)
{
	frontTextureFile = aTextureFile;
}

string Building::getBackTextureFile()
{
	return backTextureFile;
}

void Building::setBackTextureFile(string aTextureFile)
{
	backTextureFile = aTextureFile;
}

string Building::getBottomTextureFile()
{
	return bottomTextureFile;
}

void Building::setBottomTextureFile(string aTextureFile)
{
	bottomTextureFile = aTextureFile;
}

string Building::getLeftTextureFile()
{
	return leftTextureFile;
}

void Building::setLeftTextureFile(string aTextureFile)
{
	leftTextureFile = aTextureFile;
}

string Building::getRightTextureFile()
{
	return rightTextureFile;
}

void Building::setRightTextureFile(string aTextureFile)
{
	rightTextureFile = aTextureFile;
}

GLfloat Building::getHeight()
{
	return height;
}

void Building::setHeight(GLfloat aHeight)
{
	height = aHeight;
}

GLfloat Building::getWidth()
{
	return width;
}

void Building::setWidth(GLfloat aWidth)
{
	width = aWidth;
}

GLfloat Building::getDepth()
{
	return depth;
}

void Building::setDepth(GLfloat aDepth)
{
	depth = aDepth;
}

string Building::getRoofTextureFile()
{
	return roofTextureFile;
}

void Building::setRoofTextureFile(string aRoofTextureFile)
{
	roofTextureFile = aRoofTextureFile;
}

void Building::createTextures()
{
	texture[0] = setTexture(frontTextureFile);//for each side of the building set up textures
	texture[1] = setTexture(roofTextureFile);
	texture[2] = setTexture(rightTextureFile);
	texture[3] = setTexture(bottomTextureFile);
	texture[4] = setTexture(leftTextureFile);
	texture[5] = setTexture(backTextureFile);
}
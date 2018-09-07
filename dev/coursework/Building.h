#ifndef __BUILDING_H
#define __BUILDING_H

#include <string>
#include <vector>
#include "CubeObject.h"
using namespace std;

class Building : public CubeObject // building class, extends from a cube object, used for buildings in level
{
private:

	GLfloat height; //size of the building
	GLfloat width;
	GLfloat depth;

	string frontTextureFile; // texture file names
	string backTextureFile;
	string rightTextureFile;
	string leftTextureFile;
	string bottomTextureFile;
	string roofTextureFile;

	GLuint texture[6]; // building textures

public:
	Building();
	virtual ~Building();

	void drawBuilding(); // draws the building

	// getter and setter for building height
	GLfloat getHeight();
	void setHeight(GLfloat aHeight);
	
	// getter and setter for building width
	GLfloat getWidth();
	void setWidth(GLfloat aWidth);

	// getter and setter for building depth
	GLfloat getDepth();
	void setDepth(GLfloat aDepth);

	// getters and setters for building texture files
	string getFrontTextureFile();
	void setFrontTextureFile(string aTextureFile);
	string getBackTextureFile();
	void setBackTextureFile(string aTextureFile);
	string getLeftTextureFile();
	void setLeftTextureFile(string aTextureFile);
	string getRightTextureFile();
	void setRightTextureFile(string aTextureFile);
	string getBottomTextureFile();
	void setBottomTextureFile(string aTextureFile);
	string getRoofTextureFile();
	void setRoofTextureFile(string aRoofTextureFile);

	void createTextures(); // create building textures, based on filenames
};

#endif
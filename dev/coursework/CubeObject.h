#ifndef __CUBEOBJECT_H
#define __CUBEOBJECT_H

#include <string>
#include <vector>
#include <fstream>
#include "GameObject.h"
#include "TextureObject.h"

using namespace std;

class CubeObject : public GameObject, public TextureObject //class used for drawing textured cube at certain positions
{
protected:
	// draws a cube
	void drawCube(float aXPos, float aYPos, float aZPos, GLuint* aTexture);

public:
	CubeObject();
	virtual ~CubeObject();

	//draws a cube at (1,1,1)
	void drawCube(GLuint* aTexture);
};

#endif
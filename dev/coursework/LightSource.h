#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

#include <string>
#include <vector>
#include "CubeObject.h"
using namespace std;

class LightSource : public CubeObject //class used to store details about light sources
{
private:
	unsigned int lightIndex;//lights index

	GLfloat attenuationFactor;//brightness of light

	void drawCube(float aXPos, float aYPos, float aZPos);//draw the light object
public:
	LightSource();
	virtual ~LightSource();

	void setAttenuationFactor(GLfloat aAttenuationFactor);//set brightness

	void setLightIndex(unsigned int aLightIndex);//set index

	void enableLight();//enable each light index
	void disableLight();//disable each light index

	void CreateLight();// create light components
	void drawLight();//draw lights
};

#endif
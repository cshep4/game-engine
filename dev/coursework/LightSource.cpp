#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "LightSource.h"

LightSource::LightSource()
{
	xPos = 0.0f;
	yPos = 0.0f;
	zPos = 0.0f;
	attenuationFactor = 0.001;
}

LightSource::~LightSource()
{
}

void LightSource::setAttenuationFactor(GLfloat aAttenuationFactor)
{
	attenuationFactor = aAttenuationFactor;
}

void LightSource::setLightIndex(unsigned int aLightIndex)
{
	lightIndex = aLightIndex;
}

void LightSource::enableLight()
{
	glEnable(lightIndex);
}

void LightSource::disableLight()
{
	glDisable(lightIndex);
}

void LightSource::drawLight()
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);	// white
		glTranslatef(xPos, yPos, zPos);
		glScalef(0.5f, 2.0f, 2.0f);
		drawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void LightSource::drawCube(float aXPos, float aYPos, float aZPos)
{
	//draw cube for light source, without texture
	glPushMatrix();
		// enable color tracking
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glTranslatef(aXPos, aYPos, aZPos);
		glBegin(GL_POLYGON);
			glNormal3d(0, 1, 0);	//Normals set for lighting
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, 0, 1);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(1, 0, 0);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(-1, 0, 0);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, -1, 0);
			glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, 0, -1);
			glVertex3f(0.0f, 0.0f, -1.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}

void LightSource::CreateLight()
{
	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightpos[] = {xPos, yPos, zPos, 1.0f};
 
	// Assign created components to lightIndex
	glLightfv(lightIndex, GL_AMBIENT, ambientLight);
	glLightfv(lightIndex, GL_DIFFUSE, diffuseLight);
	glLightfv(lightIndex, GL_SPECULAR, specularLight);
	glLightfv(lightIndex, GL_POSITION, lightpos);
	glLightf(lightIndex, GL_CONSTANT_ATTENUATION, attenuationFactor*2);
	glLightf(lightIndex, GL_LINEAR_ATTENUATION, attenuationFactor*1);
	glLightf(lightIndex, GL_QUADRATIC_ATTENUATION, attenuationFactor*0.5);
	drawLight();
}
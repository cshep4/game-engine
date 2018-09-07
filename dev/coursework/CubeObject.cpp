#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "CubeObject.h"

CubeObject::CubeObject()
{
}

CubeObject::~CubeObject()
{
}

void CubeObject::drawCube(float aXPos, float aYPos, float aZPos, GLuint* aTexture)
{

	glPushMatrix();
		// enable color tracking
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glTranslatef(aXPos, aYPos, aZPos);
		glBindTexture(GL_TEXTURE_2D,aTexture[1]);//bind texture for each face
		glBegin(GL_QUADS);
			glNormal3d(0, 1, 0);	//Normals set for lighting
			// sets texture coords and vertex coords for each face
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,aTexture[5]);
		glBegin(GL_QUADS);
			glNormal3d(0, 0, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,aTexture[2]);
		glBegin(GL_QUADS);
			glNormal3d(1, 0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,aTexture[4]);
		glBegin(GL_QUADS);
			glNormal3d(-1, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f); // left face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,aTexture[3]);
		glBegin(GL_QUADS);
			glNormal3d(0, -1, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,aTexture[0]);
		glBegin(GL_QUADS);
			glNormal3d(0, 0, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f); // back face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}

void CubeObject::drawCube(GLuint* aTexture)
{
	drawCube(0, 0, 0, aTexture);
}
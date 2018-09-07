#ifndef __CAMERA_H
#define __CAMERA_H

#include "GameObject.h"

enum cameraState{characterCamera, panCamera};

const int kCharacterCamera = 0;
const int kPanCamera = 1;

class Camera : public GameObject // camera class, extends game object as it has a position, used for cameras in level
{
private:

	GLfloat xRotate; // vector for pan cameras rotation
	GLfloat yRotate;
	GLfloat zRotate;

	GLfloat xTranslate; // vector for pan cameras translation
	GLfloat yTranslate;
	GLfloat zTranslate;

	cameraState currentCamera; // current camera being used

public:
	Camera();
	virtual ~Camera();

	//getters and setters for pan cameras tranlate position
	GLfloat getXTranslate();
	void setXTranslate(GLfloat aXTranslate);
	GLfloat getYTranslate();
	void setYTranslate(GLfloat aYTranslate);
	GLfloat getZTranslate();
	void setZTranslate(GLfloat aZTranslate);

	//getters and setters for pan cameras rotation
	GLfloat getXRotate();
	void setXRotate(GLfloat aXRotate);
	GLfloat getYRotate();
	void setYRotate(GLfloat aYRotate);
	GLfloat getZRotate();
	void setZRotate(GLfloat aZRotate);

	bool characterCam();//check if character camera being used
	bool panCam();//check if pan camera being used
	void setState(int aState); // set active camera

	LPCSTR getCamText(); //get text string for text report
};

#endif
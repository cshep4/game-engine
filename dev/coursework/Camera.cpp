#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>
#include <amp_math.h>

#include "Camera.h"

Camera::Camera()
{
	rotationAngle = 0.0f; // angle of rotation for the direction of the camera

	/////////////////////////////////////////Pan Camera
	xRotate = 20.f;
	yRotate = 0.f;
	zRotate = 0.f;

	xTranslate = 0.f;
	yTranslate = -50.f;
	zTranslate = -130.f;
	/////////////////////////////////////////

	/////////////////////////////////////////Character Camera
	xPos = 0.0f; // position of the camera
	yPos = 0.0f;
	zPos = 0.0f;
	/////////////////////////////////////////
	currentCamera = characterCamera;
}

Camera::~Camera()
{
}

float Camera::getXTranslate()
{
	return xTranslate;
}

void Camera::setXTranslate(float aXTranslate)
{
	xTranslate = aXTranslate;
}

float Camera::getYTranslate()
{
	return yTranslate;
}

void Camera::setYTranslate(float aYTranslate)
{
	yTranslate = aYTranslate;
}

float Camera::getZTranslate()
{
	return zTranslate;
}

void Camera::setZTranslate(float aZTranslate)
{
	zTranslate = aZTranslate;
}

float Camera::getXRotate()
{
	return xRotate;
}

void Camera::setXRotate(float aXRotate)
{
	xRotate = aXRotate;
}

float Camera::getYRotate()
{
	return yRotate;
}

void Camera::setYRotate(float aYRotate)
{
	yRotate = aYRotate;
}

float Camera::getZRotate()
{
	return zRotate;
}

void Camera::setZRotate(float aZRotate)
{
	zRotate = aZRotate;
}

bool Camera::characterCam()
{
	if (currentCamera == characterCamera)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Camera::panCam()
{
	if (currentCamera == panCamera)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Camera::setState(int aState)
{
	if (aState == kCharacterCamera)
	{
		currentCamera = characterCamera;
	}
	if (aState == kPanCamera)
	{
		currentCamera = panCamera;
	}
}

LPCSTR Camera::getCamText()
{
	if (panCam())//get text string to output depending on which camera is being used
	{
		return "Camera: Pan";
	}
	if (characterCam())
	{
		return "Camera: Character";
	}
}
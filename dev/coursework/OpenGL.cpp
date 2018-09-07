#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>
#include <amp_math.h>
#include "OpenGL.h"
#include "GameObject.h"
#include "Robot.h"
#include "Camera.h"
#include "Environment.h"
#include "FileLoader.h"
#include "LightSource.h"
#include "Building.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

OpenGL::OpenGL()
{
}

OpenGL::~OpenGL()
{
}

bool OpenGL::init()
{	
	theRobot = new Robot;
	theCamera = new Camera;
	theEnvironment = new Environment;
	lightSource.clear();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//set all key presses to false as default
	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;
	aPressed = false;
	wPressed = false;
	sPressed = false;
	dPressed = false;

	splashScreen = true;//set splashcreen to be on

	mouseMovement = true;//enable mouse camera movement

	loadNewFile();// load in level file

	glEnable(GL_LIGHTING); // enable lighting

	return true;
}

bool OpenGL::shutdown()
{
	delete theRobot; // clear created objects
	delete theCamera;
	delete theEnvironment;
	lightSource.clear();
	delete fileLoader;

	return true;
}

void OpenGL::setupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}

void OpenGL::Prepare(float dt)
{
	setAnimation();// set animation based on key presses
	if (theRobot->getMove())
	{
		theRobot->prepare(dt); // make robot animate if correct keys are being pressed
	}
}

void OpenGL::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)
	glLoadIdentity();
	if (splashScreen)//if splashscreen is currently being viewed
	{
		glPushMatrix();

			glTranslatef(theCamera->getXTranslate(),
							theCamera->getYTranslate(),
							theCamera->getZTranslate());

			glRotatef(theCamera->getXRotate(),1.f,0.f,0.f);
			glRotatef(theCamera->getYRotate(),0.f,1.f,0.f);
			glRotatef(theCamera->getZRotate(),0.f,0.f,1.f);

			for (int lightLoop = 0; lightLoop < lightSource.size(); lightLoop++)
			{
				lightSource[lightLoop]->CreateLight();
			}

			theRobot->drawRobot(theRobot->getXPos(), theRobot->getYPos(), theRobot->getZPos());		// draw the robot

			theEnvironment->drawEnvironment();
		glPopMatrix();
		theCamera->setYRotate(theCamera->getYRotate()+0.05f);//rotate camera
	}
	else
	{
		if (theCamera->characterCam())//if the character camera is selected
		{
			gluLookAt(theCamera->getXPos(),theCamera->getYPos(),theCamera->getZPos(),
					  theRobot->getXPos(),theRobot->getYPos(),theRobot->getZPos(),				  
					  0.0f, 1.0f, 0.0f); // moves camera based on movement

			for (int lightLoop = 0; lightLoop < lightSource.size(); lightLoop++)
			{// draw light sources
				lightSource[lightLoop]->CreateLight();
			}
			glPushMatrix();							// put current matrix on stack
				glTranslatef(theRobot->getXPos(), theRobot->getYPos(), theRobot->getZPos());	// move robot (robot pos only changes with pan camera)
				glRotatef(theRobot->getRotationAngle(), 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
				theRobot->drawRobot(0.0f, 0.0f, 0.0f);		// draw the robot
			glPopMatrix();	

			glPushMatrix();							// put current matrix on stack
				theEnvironment->drawEnvironment(); // draw environment
			glPopMatrix();
		}
		else// pan camera
		{
			glPushMatrix();// draw objects based on the camera position

				glTranslatef(theCamera->getXTranslate(),
							 theCamera->getYTranslate(),
							 theCamera->getZTranslate());

				glRotatef(theCamera->getXRotate(),1.f,0.f,0.f);
				glRotatef(theCamera->getYRotate(),0.f,1.f,0.f);
				glRotatef(theCamera->getZRotate(),0.f,0.f,1.f);

				for (int lightLoop = 0; lightLoop < lightSource.size(); lightLoop++)
				{
					lightSource[lightLoop]->CreateLight();
				}

				theRobot->drawRobot(theRobot->getXPos(), theRobot->getYPos(), theRobot->getZPos());		// draw the robot

				theEnvironment->drawEnvironment();
			glPopMatrix();
		}
	}
}

void OpenGL::setAnimation() // where the events based on button presses are called
{
	float radAngle = theRobot->getRotationAngle() /180 * PI; // convert angle to radians for translation
	if (leftPressed)
	{
		if (theCamera->characterCam())
		{
			theRobot->setRotationAngle(theRobot->getRotationAngle() + 2.0f); //rotate robot based on which way the player moves him
		}
		else//pan camera
		{
			theCamera->setYRotate(theCamera->getYRotate()+ROTATE_INCREMENT);//rotate scene
		}
	}
	else if (rightPressed)
	{
		if (theCamera->characterCam())
		{
			theRobot->setRotationAngle(theRobot->getRotationAngle() - 2.0f); //rotate robot based on which way the player moves him
		}
		else//pan camera
		{
			theCamera->setYRotate(theCamera->getYRotate()-ROTATE_INCREMENT);//rotate scene
		}
	}

	if (upPressed)
	{
		if (theCamera->characterCam())
		{
			theRobot->setMove(true); //set walking animation

			theRobot->setXPos(theRobot->getXPos() - (1.0f *sin(radAngle))); //move robot position based on dirction he is facing
			theRobot->setZPos(theRobot->getZPos() - (1.0f *cos(radAngle)));	
			// calculate the  coordinates based on angle the robot is facing using the rotation matrix
			theCamera->setXPos(theCamera->getXPos() - (1.0f *sin(radAngle))); //move camera position based on dirction he is facing
			theCamera->setZPos(theCamera->getZPos() - (1.0f *cos(radAngle)));	
		}
		else//pan camera
		{
			theCamera->setXRotate(theCamera->getXRotate()+ROTATE_INCREMENT);//rotate scene in x direction
		}
	}
	else if (downPressed)
	{
		if (theCamera->characterCam())
		{
			theRobot->setMove(true); //set walking animation

			theRobot->setXPos(theRobot->getXPos() + (1.0f *sin(radAngle))); //move robot position based on dirction he is facing
			theRobot->setZPos(theRobot->getZPos() + (1.0f *cos(radAngle)));
			theCamera->setXPos(theCamera->getXPos() + (1.0f *sin(radAngle))); //move camera position based on dirction he is facing
			theCamera->setZPos(theCamera->getZPos() + (1.0f *cos(radAngle)));
		}
		else//pan camera
		{
			theCamera->setXRotate(theCamera->getXRotate()-ROTATE_INCREMENT);//roate scene in x direction
		}
	}
	else
	{
		theRobot->setMove(false); //stop walking animation
	}

	if (theCamera->panCam())
	{
		if (getAPressed())//translate the camera based
		{
			theCamera->setXTranslate(theCamera->getXTranslate()+1);
		}
		if (getWPressed())
		{
			theCamera->setZTranslate(theCamera->getZTranslate()+1);
		}
		if (getSPressed())
		{
			theCamera->setZTranslate(theCamera->getZTranslate()-1);
		}
		if (getDPressed())
		{
			theCamera->setXTranslate(theCamera->getXTranslate()-1);
		}
	}
}

bool OpenGL::getleftPressed()
{
	return leftPressed;
}

void OpenGL::setLeftPressed(bool aLeftPressed)
{
	leftPressed = aLeftPressed;
}

bool OpenGL::getRightPressed()
{
	return rightPressed;
}

void OpenGL::setRightPressed(bool aRightPressed)
{
	rightPressed = aRightPressed;
}

bool OpenGL::getDownPressed()
{
	return downPressed;
}

void OpenGL::setDownPressed(bool aDownPressed)
{
	downPressed = aDownPressed;
}

bool OpenGL::getUpPressed()
{
	return upPressed;
}

void OpenGL::setUpPressed(bool aUpPressed)
{
	upPressed = aUpPressed;
}

bool OpenGL::getAPressed()
{
	return aPressed;
}

void OpenGL::setAPressed(bool aAPressed)
{
	aPressed = aAPressed;
}

bool OpenGL::getWPressed()
{
	return wPressed;
}

void OpenGL::setWPressed(bool aWPressed)
{
	wPressed = aWPressed;
}

bool OpenGL::getDPressed()
{
	return dPressed;
}

void OpenGL::setDPressed(bool aDPressed)
{
	dPressed = aDPressed;
}

bool OpenGL::getSPressed()
{
	return sPressed;
}

void OpenGL::setSPressed(bool aSPressed)
{
	sPressed = aSPressed;
}

void OpenGL::mouseMove(int aWindowWidth, int aWindowHeight)
{
	if (theCamera->panCam())
	{
		return;
	}

	POINT mousePos;	
	int xMid = aWindowWidth  >> 1;	
	int yMid = aWindowHeight >> 1;	
	float yAngle  = 0.0f;				
	float zAngle  = 0.0f;							
	
	GetCursorPos(&mousePos);	// Get the mouse cursor x,y position					
	
	if (((mousePos.x == xMid) && (mousePos.y == yMid)) ||
		((mousePos.x > aWindowWidth) || (mousePos.y > aWindowHeight)) ||
		((mousePos.x < 0) || (mousePos.y < 0)))
	{
		return;
	}

	SetCursorPos(xMid, yMid);	// Set the mouse cursor in the center of the window						

	// Get the direction from the mouse cursor
	float xMousePos = (xMid - mousePos.x);
	float yMousePos = (yMid - mousePos.y);
	yAngle = xMousePos/1000;		
	zAngle = yMousePos/1000;

	//change robot position to give the impression of looking up/down
	theRobot->setYPos(theRobot->getYPos() + zAngle * 2);

	// limit the rotation around the x-axis, to stop camera going too far
	if(theRobot->getYPos() > 5.5f)
	{
		theRobot->setYPos(5.5f);
	}
	if(theRobot->getYPos() < 0.4f)
	{
		theRobot->setYPos(0.4f);
	}
	
	float xVector = theCamera->getXPos() - theRobot->getXPos();
	float zVector = theCamera->getZPos() - theRobot->getZPos();

	theCamera->setZPos(theRobot->getZPos() + sin(-yAngle)*xVector + cos(-yAngle)*zVector);
	theCamera->setXPos(theRobot->getXPos() + cos(-yAngle)*xVector - sin(-yAngle)*zVector);
}

void OpenGL::printTextToScreen(HDC aHDC, HWND aHWND)
{
	//prepare and print text reports to screen
	LPCSTR camString = theCamera->getCamText();
	LPCSTR fileString = fileLoader->getFileLoadedString();
	string robotString = theRobot->getRobotPositionString();
	LPCSTR robotPosString = robotString.c_str();
	string environmentString = theEnvironment->getMapSizeString();
	LPCSTR mapString = environmentString.c_str();
	string lightString = getLightsString();
	LPCSTR lightingString = lightString.c_str();
	TextOut(aHDC, 100, 100, camString, strlen(camString));
	TextOut(aHDC, 100, 100, camString, strlen(fileString));
	TextOut(aHDC, 100, 100, camString, strlen(robotPosString));
	TextOut(aHDC, 100, 100, camString, strlen(mapString));
	TextOut(aHDC, 100, 100, camString, strlen(lightingString));
}

void OpenGL::switchCamera()
{
	if (theCamera->characterCam())//depending on which is active camera, switch between them
	{
		theCamera->setState(kPanCamera);
	}
	else
	{
		theCamera->setState(kCharacterCamera);
	}
}

void OpenGL::setCharacterCamera()
{
	theCamera->setState(kCharacterCamera);
}

void OpenGL::setPanCamera()
{
	theCamera->setState(kPanCamera);
}

void OpenGL::loadNewFile()
{
	fileLoader = nullptr; // remove all previous file details
	fileLoader = new FileLoader;
	fileLoader->loadFromFile();// load in new details from file

	//for each object load in details recorded in file loader
	theRobot = fileLoader->theRobot;
	theRobot->createTextures();
	theEnvironment = fileLoader->theEnvironment;
	theEnvironment->createTextures();
	for (int buildingLoop = 0; buildingLoop < theEnvironment->building.size(); buildingLoop++)
	{
		theEnvironment->building[buildingLoop]->createTextures();
	}
	theCamera = fileLoader->theCamera;
	lightSource = fileLoader->lightSource;
}

string OpenGL::getLightsString()
{
	if (glIsEnabled(GL_LIGHTING))
	{
		return "Lights: Enabled";
	}
	else
	{
		return "Lights: Disabled";
	}
}

void OpenGL::enableLights()
{
	glEnable(GL_LIGHTING);
	for (int lightLoop = 0; lightLoop < lightSource.size(); lightLoop++)
	{
		lightSource[lightLoop]->enableLight();
	}
}

void OpenGL::disableLights()
{
	glDisable(GL_LIGHTING);
	for (int lightLoop = 0; lightLoop < lightSource.size(); lightLoop++)
	{
		lightSource[lightLoop]->disableLight();
	}
}

void OpenGL::toggleLights()
{
	if (glIsEnabled(GL_LIGHTING))
	{
		disableLights();
	}
	else
	{
		enableLights();
	}
}

void OpenGL::setFileName(string aFilename)
{
	fileLoader->setFileName(aFilename);
}

void OpenGL::setMouseMove(bool aMouseMove)
{
	mouseMovement = aMouseMove;
}

bool OpenGL::getMouseMove()
{
	if (!splashScreen)//if splash screen is active, no mouse camera movement
	{
		return mouseMovement;
	}
	else
	{
		return false;
	}
}
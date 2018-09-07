#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0
#define ROTATE_INCREMENT 5.0f

class Robot;
class Camera;
class FileLoader;
class Environment;
class LightSource;

#include <string>
#include <vector>

using namespace std;


class OpenGL // main class used to store openGL data
{
private:
	// game objects
	Robot *theRobot;
	Camera *theCamera;
	Environment *theEnvironment;
	FileLoader *fileLoader;
	vector< LightSource* > lightSource;

	int m_windowWidth;//window size
	int m_windowHeight;

	bool leftPressed;//key press booleans
	bool rightPressed;
	bool upPressed;
	bool downPressed;
	bool wPressed;
	bool aPressed;
	bool sPressed;
	bool dPressed;

	bool mouseMovement;//if mouse camera movement is enabled

public:
	OpenGL();
	virtual ~OpenGL();

	bool init();//initilase opengl class
	bool shutdown();//shutdown game
	
	void setupProjection(int width, int height);// set up projection

	void Prepare(float dt);//prepare animation of robot
	void Render();//draw scene

	void setAnimation();//set game behaviour based on key presses

	//getters and setters for key presses
	bool getleftPressed();
	void setLeftPressed(bool aLeftPressed);
	bool getRightPressed();
	void setRightPressed(bool aRightPressed);
	bool getDownPressed();
	void setDownPressed(bool aDownPressed);
	bool getUpPressed();
	void setUpPressed(bool aUpPressed);
	bool getAPressed();
	void setAPressed(bool aAPressed);
	bool getWPressed();
	void setWPressed(bool aWPressed);
	bool getSPressed();
	void setSPressed(bool aSPressed);
	bool getDPressed();
	void setDPressed(bool aDPressed);

	void mouseMove(int aWindowWidth, int aWindowHeight);//mouse camera movement

	void printTextToScreen(HDC aHDC, HWND aHWND);//print text reports to screen
	string getLightsString();

	void switchCamera();//switch between active cameras
	void setCharacterCamera();//set character camera
	void setPanCamera();//set pan camera

	void loadNewFile();//load in a new level from a file

	void enableLights();//enable lights in a scene
	void disableLights();//disable lights in a scene
	void toggleLights();//toggle between lights being enabled/disabled

	void setFileName(string aFilename);//set new level details file

	void setMouseMove(bool aMouseMove);//getters and setters for enabling mouse movement
	bool getMouseMove();

	bool splashScreen;// if splashscreen is active
};

#endif
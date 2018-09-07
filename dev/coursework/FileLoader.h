#ifndef __FILELOADER_H
#define __FILELOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Robot;
class Environment;
class Camera;
class LightSource;

using namespace std;

class FileLoader //file loader class, used to load in data from XML file
{
private:
	bool loaded;

	string filename;
public:
	FileLoader();
	virtual ~FileLoader();

	void loadFromFile();// load file data

	void loadLevelDetails(string aLine);//read in level details from file
	void loadBuildingDetails(string aLine);// read in building details from file
	void loadRobotDetails(string aLine);//read in robot details from file
	void loadLightSourceDetails(string aLine);// read in light source details from file

	void setFileName(string aFilename);//set nwew file name

	// objects decalared
	Robot *theRobot;
	Environment *theEnvironment;
	Camera *theCamera;
	vector< LightSource* > lightSource;

	void setFileLoaded(bool aLoaded);
	bool getFileLoaded();
	LPCSTR getFileLoadedString();

	void setLightIndex();// set up indexs for each light source when adding a new one
};

#endif
#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "FileLoader.h"
#include "Robot.h"
#include "Environment.h"
#include "Building.h"
#include "Camera.h"
#include "LightSource.h"

FileLoader::FileLoader()
{
	filename = "../../content/Level_Details.xml";
	theRobot = new Robot;
	theEnvironment = new Environment;
	theCamera = new Camera;
	lightSource.clear(); //initialise to nothing as there are no light sources yet
}

FileLoader::~FileLoader()
{
}

void FileLoader::loadFromFile()
{
	ifstream file(filename);
	string line;

	if (file.is_open())
	{
		setFileLoaded(true);
	}
	else
	{
		setFileLoaded(false);
	}
	bool level_tag = false;
	bool building_tag = false;
	bool robot_tag = false;
	bool lightSource_tag = false;
    while (getline(file,line))// for each line in text file, read in and do something fopr each component
    {
        std::string tmp; // strip whitespaces from the beginning
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ' && tmp.size() == 0)
            {
            }
            else
            {
                tmp += line[i];
            }
        }

        if (tmp == "<Level>")//level details read in
        {
            level_tag = true;
            continue;
        }
        if (tmp == "</Level>")//end of level details
        {
            level_tag = false;
        }
        if (tmp == "<Building>")//new building read in
        {
            building_tag = true;
			theEnvironment->addBuilding();
            continue;
        }
        if (tmp == "</Building>")//end of new building
        {
            building_tag = false;
        }
        if (tmp == "<Robot>")//robot details read in
        {
            robot_tag = true;
            continue;
        }
        if (tmp == "</Robot>")//end of robot details
        {
            robot_tag = false;
        }
        if (tmp == "<LightSource>")//new light source read in
        {
            lightSource_tag = true;
			lightSource.push_back(new LightSource);
			setLightIndex();
			lightSource[lightSource.size()-1]->enableLight();
            continue;
        }
        if (tmp == "</LightSource>")//end of light source details
        {
            lightSource_tag = false;
        }

		if (level_tag)// for each object being read in, store details
		{
			loadLevelDetails(tmp);
		}
		if (building_tag)
		{
			loadBuildingDetails(tmp);
		}
		if (robot_tag)
		{
			loadRobotDetails(tmp);
		}
		if (lightSource_tag)
		{
			loadLightSourceDetails(tmp);
		}
    }
}

void FileLoader::loadLevelDetails(string aLine)
{
	string startDelimiter = ">";
	string stopDelimiter =  "</";
	unsigned firstIndex = aLine.find(startDelimiter);
	unsigned lastIndex = aLine.find(stopDelimiter);
	string value = aLine.substr(firstIndex+1,lastIndex-firstIndex-1); 
	string textureFileDir = "../../content/Textures/";

	if (aLine.find("<width>") != string::npos)// level width read in
	{
		theEnvironment->setLevelWidth(stod(value));
	}

	if (aLine.find("<depth>") != string::npos)// level depth read in
	{
		theEnvironment->setLevelDepth(stod(value));
	}

	if (aLine.find("<levelTopY>") != string::npos)// level top Y position read in
	{
		theEnvironment->setLevelTopY(stod(value));
	}

	if (aLine.find("<levelBottomY>") != string::npos)// level bottom Y read in
	{
		theEnvironment->setLevelBottomY(stod(value));
	}

	if (aLine.find("<groundTexture>") != string::npos)// level ground texture read in
	{
		theEnvironment->setGroundTextureFile(textureFileDir + value);
	}
}

void FileLoader::loadBuildingDetails(string aLine)
{
	string startDelimiter = ">";
	string stopDelimiter =  "</";
	unsigned firstIndex = aLine.find(startDelimiter);
	unsigned lastIndex = aLine.find(stopDelimiter);
	string value = aLine.substr(firstIndex+1,lastIndex-firstIndex-1); 
	int buildingIndex = theEnvironment->building.size()-1;

	if (aLine.find("<width>") != string::npos)// building width read in
	{
		theEnvironment->building[buildingIndex]->setWidth(stod(value));
	}

	if (aLine.find("<height>") != string::npos)// building height read in
	{
		theEnvironment->building[buildingIndex]->setHeight(stod(value));
	}

	if (aLine.find("<depth>") != string::npos)// building depth read in
	{
		//theEnvironment->setBuildingDepth(stod(value),theEnvironment->building.size()-1);
		theEnvironment->building[buildingIndex]->setDepth(stod(value));
	}

	if (aLine.find("<XPos>") != string::npos)// building xPos read in
	{
		//theEnvironment->setBuildingPosX(stod(value),theEnvironment->building.size()-1);
		theEnvironment->building[buildingIndex]->setXPos(stod(value));
	}

	if (aLine.find("<YPos>") != string::npos)// building yPos read in
	{
		//theEnvironment->setBuildingPosY(stod(value),theEnvironment->building.size()-1);
		theEnvironment->building[buildingIndex]->setYPos(stod(value));
	}

	if (aLine.find("<ZPos>") != string::npos)// building zPos read in
	{
		//theEnvironment->setBuildingPosZ(stod(value),theEnvironment->building.size()-1);
		theEnvironment->building[buildingIndex]->setZPos(stod(value));
	}

	if (aLine.find("<frontTextureFile>") != string::npos)// building texcture files read in
	{
		theEnvironment->building[buildingIndex]->setFrontTextureFile(value);
	}

	if (aLine.find("<backTextureFile>") != string::npos)
	{
		theEnvironment->building[buildingIndex]->setBackTextureFile(value);
	}

	if (aLine.find("<rightTextureFile>") != string::npos)
	{
		theEnvironment->building[buildingIndex]->setRightTextureFile(value);
	}

	if (aLine.find("<leftTextureFile>") != string::npos)
	{
		theEnvironment->building[buildingIndex]->setLeftTextureFile(value);
	}

	if (aLine.find("<bottomTextureFile>") != string::npos)
	{
		theEnvironment->building[buildingIndex]->setBottomTextureFile(value);
	}

	if (aLine.find("<roofTextureFile>") != string::npos)
	{
		//theEnvironment->setBuildingRoofTextureFile(textureFileDir + value,theEnvironment->building.size()-1);
		theEnvironment->building[buildingIndex]->setRoofTextureFile(value);
	}
}

void FileLoader::loadRobotDetails(string aLine)
{
	string startDelimiter = ">";
	string stopDelimiter =  "</";
	unsigned firstIndex = aLine.find(startDelimiter);
	unsigned lastIndex = aLine.find(stopDelimiter);
	string value = aLine.substr(firstIndex+1,lastIndex-firstIndex-1); 

	if (aLine.find("<posX>") != string::npos)// robot xPos read in
	{
		theRobot->setXPos(stod(value));
		theCamera->setXPos(stod(value));
	}

	if (aLine.find("<posZ>")!= string::npos)// robot zPos read in
	{
		theRobot->setZPos(stod(value));
		theCamera->setZPos(stod(value)+30);
	}

	if (aLine.find("<faceTexture>") != string::npos)// robot texture files read in
	{
		//theRobot->addHeadTexture();
		theRobot->setFaceTextureFile(value);
	}

	if (aLine.find("<backHeadTexture>") != string::npos)
	{
		theRobot->setBackHeadTextureFile(value);
	}

	if (aLine.find("<leftHeadTexture>") != string::npos)
	{
		theRobot->setLeftHeadTextureFile(value);
	}

	if (aLine.find("<rightHeadTexture>") != string::npos)
	{
		theRobot->setRightHeadTextureFile(value);
	}

	if (aLine.find("<topHeadTexture>") != string::npos)
	{
		theRobot->setTopHeadTextureFile(value);
	}

	if (aLine.find("<bottomHeadTexture>") != string::npos)
	{
		theRobot->setBottomHeadTextureFile(value);
	}

	if (aLine.find("<armTopTexture>") != string::npos)
	{
		theRobot->setTopArmTextureFile(value);
	}

	if (aLine.find("<armBottomTexture>") != string::npos)
	{
		theRobot->setBottomArmTextureFile(value);
	}

	if (aLine.find("<armTexture>") != string::npos)
	{
		theRobot->setArmTextureFile(value);
	}

	if (aLine.find("<chestTexture>") != string::npos)
	{
		theRobot->setChestTextureFile(value);
	}

	if (aLine.find("<legTexture>") != string::npos)
	{
		theRobot->setLegTextureFile(value);
	}

	if (aLine.find("<footTexture>") != string::npos)
	{
		theRobot->setFootTextureFile(value);
	}
}

void FileLoader::loadLightSourceDetails(string aLine)
{
	string startDelimiter = ">";
	string stopDelimiter =  "</";
	unsigned firstIndex = aLine.find(startDelimiter);
	unsigned lastIndex = aLine.find(stopDelimiter);
	string value = aLine.substr(firstIndex+1,lastIndex-firstIndex-1); 
	int index = lightSource.size()-1;

	if (aLine.find("<XPos>") != string::npos)// light source xPos read in
	{
		lightSource[index]->setXPos(stod(value));
	}

	if (aLine.find("<YPos>") != string::npos)// light source yPos read in
	{
		lightSource[index]->setYPos(stod(value));
	}

	if (aLine.find("<ZPos>") != string::npos)// light source zPos read in
	{
		lightSource[index]->setZPos(stod(value));
	}
	if (aLine.find("<AttenuationFactor>") != string::npos)// light source brightness read in
	{
		lightSource[index]->setAttenuationFactor(stod(value));
	}
}

void FileLoader::setFileLoaded(bool aLoaded)
{
	loaded = aLoaded;
}

bool FileLoader::getFileLoaded()
{
	return loaded;
}

LPCSTR FileLoader::getFileLoadedString()
{
	if (getFileLoaded())
	{
		return "File Loaded Successfully!";
	}
	else
	{
		return "File Not Loaded!";
	}
}

void FileLoader::setLightIndex()
{
	switch (lightSource.size()-1)// sets the index of each light source thats read in
	{
		case 0:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT0);
			break;
		case 1:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT1);
			break;
		case 2:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT2);
			break;
		case 3:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT3);
			break;
		case 4:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT4);
			break;
		case 5:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT5);
			break;
		case 6:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT6);
			break;
		case 7:
			lightSource[lightSource.size()-1]->setLightIndex(GL_LIGHT7);
			break;
		default:
			lightSource.pop_back();// if there are more lights than possible, removed newly added ones
			break;
	}
}

void FileLoader::setFileName(string aFilename)
{
	filename = aFilename;
}
#ifndef __TEXTUREOBJECT_H
#define __TEXTUREOBJECT_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class TextureObject //base class to store texturing functionality
{
protected:
	GLuint texture[6];//texture to be stored

	GLuint setTexture(string aFileName);//load in and create texture from image file

public:
	TextureObject();
	virtual ~TextureObject();

};

#endif
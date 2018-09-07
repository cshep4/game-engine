#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glut.h>

#include "TextureObject.h"

TextureObject::TextureObject()
{
}

TextureObject::~TextureObject()
{
}

GLuint TextureObject::setTexture(string aFileName)
{
	sf::Image file;

	glEnable(GL_TEXTURE_2D);//enable texturing

    GLuint texture = 0;

    if (!file.loadFromFile(aFileName))//load in image file
	{
		return texture;//if cant load file, return nothing
	}
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, file.getSize().x, file.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, file.getPixelsPtr());

	//set up texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return texture;
}
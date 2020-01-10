#include "Texture.h"
#include "stb_image.h"
#include<cassert>
#include<iostream>



Texture::Texture(const std::string& fileName)
{
	//width, height, and image components number
	int width, height, numComponents; 
	//load image and store data
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	// textures quantity and adress
	glGenTextures(1, &textureHandler); 
	//bind texture and define type 
	glBindTexture(GL_TEXTURE_2D, textureHandler); 

	// wrap texture width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// wrap texture height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	// linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	// linear filtering for magnifcation (texture is larger)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	//Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); 

	stbi_image_free(imageData);
}

void Texture::Bind(unsigned int unit)
{
	//Check we are working with appropriate texture
	assert(unit >= 0 && unit <= 31); 
	//acitvate texture unit
	glActiveTexture(GL_TEXTURE0 + unit); 
	//type of and texture to bind to unit
	glBindTexture(GL_TEXTURE_2D, textureHandler);
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureHandler); 
}

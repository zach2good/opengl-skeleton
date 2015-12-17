#pragma once

#include "TextureLoader.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION   
#endif

#include "stb_image.h"

TextureLoader& TextureLoader::instance()
{
	static TextureLoader instance;
	return instance;
}

GLuint TextureLoader::loadTexture(std::string filename)
{
	// This makes the image right-way up in OpenGL
	//stbi_set_flip_vertically_on_load(true);

	GLuint m_textureID;

	int m_Error;
	int m_Width, m_Height, m_Channels;
	unsigned char* image = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (image)
	{
		m_Error = 0;
	}
	else
	{
		printf("Error loading: %s \n", filename);
		m_Error = -1;
		image = stbi_load("../res/textures/error.jpg", &m_Width, &m_Height, &m_Channels, 0);
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	GLuint format = 0;

	switch (m_Channels)
	{
	case 1: format = GL_ALPHA;     break;
	case 2: format = GL_LUMINANCE; break;
	case 3: format = GL_RGB;       break;
	case 4: format = GL_RGBA;      break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

	return 	m_textureID;
}
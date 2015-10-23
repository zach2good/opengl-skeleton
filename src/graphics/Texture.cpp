#pragma once

#include "../common.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION   
#endif

#include "stb_image.h"

Texture::Texture(const char* filename)
{
	// This makes the image right-way up in OpenGL
	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(filename, &m_Width, &m_Height, &m_Channels, 0);

	if (image)
	{
		m_Error = 0;
	}
	else {
		printf("Error loading: %s \n", filename);
		m_Error = -1;
		image = stbi_load("../res/models/error.jpg", &m_Width, &m_Height, &m_Channels, 0);
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Mipmapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	switch (m_Channels)
	{
	case 1: Format = GL_ALPHA;     break;
	case 2: Format = GL_LUMINANCE; break;
	case 3: Format = GL_RGB;       break;
	case 4: Format = GL_RGBA;      break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
}
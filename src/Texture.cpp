#pragma once

#include "common.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION   
#endif

#include "stb_image.h"

Texture::Texture(const char* filename)
{
	unsigned char* image = stbi_load(filename, &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);

	if (image)
	{
		m_Error = 0;
	}
	else {
		printf("Error loading: %s \n", filename);
		m_Error = -1;
		image = stbi_load("../res/models/error.jpg", &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
}
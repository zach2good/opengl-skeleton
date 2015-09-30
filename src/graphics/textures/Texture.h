#pragma once

#include <GL\glew.h>
#include <SOIL.h>
#include <stdio.h>
#include <stdlib.h>

class Texture
{
public:
	Texture(const char* filename);

	inline GLuint GetTextureID() { return m_textureID; }
	inline void BindTexture() { glBindTexture(GL_TEXTURE_2D, m_textureID); }

private:
	GLuint m_textureID;

	int m_Error = 0;

	int m_Width;
	int m_Height;
	int m_Channels;
};

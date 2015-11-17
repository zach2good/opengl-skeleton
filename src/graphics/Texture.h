#pragma once

#include "../common.h"
#include "stb_image.h"

class Texture
{
public:
	GLenum Format;

	Texture(const char* filename);

	inline GLuint GetTextureID() { return m_textureID; }

	inline void Bind()
	{
		Bind(0);
	}

	inline void Bind(int samplerSlot)
	{
		assert(samplerSlot >= 0 || samplerSlot <= 31);
		glActiveTexture(GL_TEXTURE0 + samplerSlot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	inline void UnBind()
	{
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	GLuint m_textureID;

	int m_Error;

	int m_Width;
	int m_Height;
	int m_Channels;
};
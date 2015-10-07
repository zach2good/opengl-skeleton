#pragma once

#include <GL\glew.h>
#include <SOIL.h>
#include <stdio.h>
#include <stdlib.h>

class Texture
{
public:
	float shineDamper = 0.12f;
	float reflectivity = 0.02f;
	bool hasTransparency = false;

	Texture(const char* filename)
	{
		unsigned char* image = SOIL_load_image(filename, &m_Width, &m_Height, &m_Channels, SOIL_LOAD_AUTO);

		if (image)
		{
			m_Error = 0;
		}
		else {
			printf("Error loading: %s \n", filename);
			m_Error = -1;
			image = SOIL_load_image("../res/models/error.jpg", &m_Width, &m_Height, &m_Channels, SOIL_LOAD_AUTO);
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

		

		SOIL_free_image_data(image);

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
	}

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

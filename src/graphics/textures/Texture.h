#pragma once

#include <GL\glew.h>
#include <SOIL.h>
#include <stdio.h>
#include <stdlib.h>

class Texture
{
public:
	Texture(const char* filename, const char* type = "texture_diffuse")
		: m_Type(type)
	{
		unsigned char* image = SOIL_load_image(filename, &m_Width, &m_Height, &m_Channels, SOIL_LOAD_AUTO);

		if (image)
		{
			glGenTextures(1, &m_textureID);
			glBindTexture(GL_TEXTURE_2D, m_textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

			glGenerateMipmap(GL_TEXTURE_2D);

			SOIL_free_image_data(image);

			glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

			m_Error = 0;
		}
		else {
			printf("Error loading: %s \n", filename);
			m_Error = -1;
		}	
	}

	inline GLuint GetTextureID() { return m_textureID; }
	inline const char* GetType() { return m_Type; }
	inline void BindTexture() { glBindTexture(GL_TEXTURE_2D, m_textureID); }

private:
	GLuint m_textureID;
	const char* m_Type;

	int m_Error = 0;

	int m_Width;
	int m_Height;
	int m_Channels;
};

#pragma once

#include "../common.h"

class TextureLoader
{
public:
	static TextureLoader& instance();
	GLuint loadTexture(std::string filename);
};
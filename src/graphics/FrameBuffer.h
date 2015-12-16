#pragma once

#include "../common.h"
#include "ShaderProgram.h"

class Framebuffer
{
public:
	Framebuffer::Framebuffer(GLuint w, GLuint h);
	~Framebuffer();


private:
	GLuint framebuffer;
	GLuint screenWidth;
	GLuint screenHeight;

	GLuint quadVAO, quadVBO;

	GLfloat quadVertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
};
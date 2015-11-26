#pragma once

#include "../common.h"
#include "ShaderProgram.h"
#include "GL.h"

class Framebuffer
{
public:
	Framebuffer::Framebuffer(GLuint w, GLuint h);
	~Framebuffer();

	void Bind();
	void Unbind();

	void Render();

private:
	ShaderProgram screenShader = ShaderProgram("../res/shaders/framebuffer");

	GLuint framebuffer;
	GLuint screenWidth;
	GLuint screenHeight;

	GLuint textureColorbuffer;

	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

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
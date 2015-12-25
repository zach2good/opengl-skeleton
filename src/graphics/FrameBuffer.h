#pragma once

#include "../common.h"
#include "../graphics/ShaderProgram.h"

class Framebuffer
{
public:
	Framebuffer(GLuint w, GLuint h);
	~Framebuffer();

	void Bind();
	void Unbind();

	void Render();
	void RenderWithShader(ShaderProgram* shader);

private:
	ShaderProgram* screenShader = new ShaderProgram("../res/shaders/framebuffer");

	GLuint screenWidth;
	GLuint screenHeight;

	GLuint fbo;
	GLuint rbo;
	GLuint textureColorbuffer;

	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

	GLuint quadVAO;
	GLuint quadVBO;
	GLfloat quadVertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
};
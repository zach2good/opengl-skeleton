#pragma once

#include "../common.h"
#include "../graphics/ShaderProgram.h"

class GBuffer
{
public:
	GBuffer::GBuffer(GLuint w, GLuint h);
	~GBuffer();

	void BindForGeometryPass();
	void BindForLightingPass();
	void Unbind();

	void Render();

private:
	ShaderProgram* screenShader = new ShaderProgram("../res/shaders/framebuffer");

	GLuint screenWidth;
	GLuint screenHeight;

	GLuint gBuffer;

	GLuint gPosition;
	GLuint gNormal;
	GLuint gAlbedoSpec;

	GLuint rboDepth;

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
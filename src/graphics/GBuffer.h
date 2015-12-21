#pragma once

#include "../common.h"

class GBuffer
{
public:
	GBuffer::GBuffer() {};
	GBuffer::GBuffer(GLuint w, GLuint h);
	~GBuffer();

	void Bind();
	void Unbind();

	GLuint gBuffer;

	GLuint gPositionDepth;
	GLuint gNormal;
	GLuint gAlbedo;

private:
	GLuint screenWidth;
	GLuint screenHeight;

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

	GLuint rboDepth;
};
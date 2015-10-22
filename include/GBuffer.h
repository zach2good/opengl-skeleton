#pragma once

#include "common.h"

class GBuffer
{
public:

	GBuffer();

	~GBuffer();

	void Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void StartFrame();
	void EndFrame();

private:

	GLuint m_fbo;
	GLuint m_tex;
	GLuint m_depth;
};

#pragma once

#include "../common.h"

class ShadowMap
{
public:
	ShadowMap(GLuint w, GLuint h);
	~ShadowMap();

	void Bind();
	void Unbind();

private:
	GLuint WIDTH;
	GLuint HEIGHT;

	GLuint depthMapFBO;
	GLuint depthMap;
};
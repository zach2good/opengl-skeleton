#pragma once

#include "../common.h"

class GBuffer
{
public:
	GBuffer() {};
	GBuffer(GLuint w, GLuint h);
	~GBuffer();

	void Bind();
	void Unbind();

	void BindForGeometryPass();

	void BindForPointLightPass();
	void BindForDirectionalLightPass();
	void BindForSpotLightPass();

	void BindForPointShadowPass();
	void BindForDirectionalShadowPass();
	void BindForSpotShadowPass();

	void BindForPostProcessingPass();

	void BindForGUIPass();

	void BindForFinalPass();

	GLuint gBuffer;

	GLuint gPositionDepth; //RGBA: RGB = Pos, A = Depth
	GLuint gNormal; // RGB = Normal 
	GLuint gAlbedoSpec; // RGBA: RGB = Color, A = Specular

private:
	GLuint screenWidth;
	GLuint screenHeight;

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

	GLuint rboDepth;
};
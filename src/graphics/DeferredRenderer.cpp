#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer(Window* window) :
	m_Window(window)
{

}
DeferredRenderer::~DeferredRenderer()
{

}

void DeferredRenderer::submit(GameObject* go)
{
	m_GameObjects.push_back(go);
}

void DeferredRenderer::draw(ShaderProgram* shader, Camera* camera)
{
	// Gbuffer format:

	// 0: RGBA = Pos(X, Y, Z) + Depth
	// 1: RGB = Norms
	// 2: RGBA = Albedo	+ Specular

	// Set up Uniforms 

	// 1. Geometry Pass

	// 2. SSAO Texture

	// 3. SSAO Blur

	// 4. Sobel Texture

	// Lighting Pass

	// Post-Processing Pass

	m_GameObjects.clear();
}

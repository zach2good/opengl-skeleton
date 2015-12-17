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
	m_gameObjects.push_back(go);
}

void DeferredRenderer::draw(ShaderProgram* shader, Camera* camera)
{
	m_gameObjects.clear();
}

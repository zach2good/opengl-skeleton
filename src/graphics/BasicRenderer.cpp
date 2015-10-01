#include "BasicRenderer.h"

BasicRenderer::BasicRenderer()
{

}

BasicRenderer::~BasicRenderer()
{

}

void BasicRenderer::Prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void BasicRenderer::Submit(Entity e)
{

}

void BasicRenderer::Render()
{

}
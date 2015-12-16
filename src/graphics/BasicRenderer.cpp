#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(Window* window) :
	m_Window(window)
{

}
BasicRenderer::~BasicRenderer()
{

}

void BasicRenderer::submit(GameObject* go)
{
	m_gameObjects.push_back(go);
}

void BasicRenderer::draw(ShaderProgram* shader, Camera* camera)
{
	// Sort by mesh 

	// Try to do instanced rendering per batch

	shader->Bind();

	// V
	shader->SetUniform4fv("view", camera->GetViewMatrix());
	shader->SetUniform3fv("viewPos", camera->Position);

	// P
	shader->SetUniform4fv("projection", 
		glm::perspective(camera->Zoom, m_Window->getAspect(), 0.1f, 1000.0f));

	// Draw
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		auto g = m_gameObjects.at(i);

		// M
		auto m = g->m_Transform.GetTransformationMatrix();
		shader->SetUniform4fv("model", m);

		// Draw	
		g->m_Mesh.render();
	}

	shader->Unbind();

	// Empty list
	m_gameObjects.clear();
}

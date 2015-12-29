#include "ForwardRenderer.h"

ForwardRenderer::ForwardRenderer(Window* window) :
	m_Window(window)
{

}

ForwardRenderer::~ForwardRenderer()
{

}

void ForwardRenderer::submit(GameObject* go)
{
	m_gameObjects.push_back(go);
}

void ForwardRenderer::draw(ShaderProgram* shader, Camera* camera)
{
	shader->Bind();

	// V
	shader->SetUniform4fv("view", camera->GetViewMatrix());
	shader->SetUniform3fv("viewPos", camera->Position);

	// P
	shader->SetUniform4fv("projection", 
		glm::perspective(camera->Zoom, m_Window->getAspect(), 0.1f, 1000.0f));

	// Find Lights to generate uniforms
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		auto g = m_gameObjects.at(i);

		if (g)
		{
			auto l = g->m_Transform.m_position;
			shader->SetUniform3fv("lightPos", l);
		}
	}

	// Draw
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		auto g = m_gameObjects.at(i);

		if (g->m_Model != NULL)
		{
			// M
			auto m = g->m_Transform.GetTransformationMatrix();
			shader->SetUniform4fv("model", m);

			//shader->SetUniform1i("hasTextures", (int)g->m_Model->HasTextures());

			g->m_Model->draw(shader);
		}	
	}

	shader->Unbind();

	// Empty list
	m_gameObjects.clear();
}

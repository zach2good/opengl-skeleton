#include "Scene4.h"

void Scene4::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(true);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 10);
	light.SetPosition(vec3(3.0f, 0.0f, 3.0f));
}

void Scene4::destroy()
{

}

void Scene4::update()
{
	shader.UpdateShader();
	trans.ChangeRotation(vec3(0.0f, 0.3f, 0.0f));
}

void Scene4::render()
{
	shader.Bind();

	shader.SetUniform4fv("model", trans.GetTransformationMatrix());
	shader.SetUniform4fv("view", camera.GetViewMatrix());
	shader.SetUniform4fv("projection", glm::perspective(camera.Zoom, m_Window->getAspect(), 0.1f, 1000.0f));
	shader.SetUniform3fv("viewPos", camera.Position);

	shader.SetUniform3fv("lightPos", light.GetPosition());

	shader.SetUniformTexture(texture.GetTextureID(), "ourTexture1", 0);

	mesh->render();

	shader.Unbind();
}

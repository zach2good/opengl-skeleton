#include "Scene3.h"

void Scene3::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(true);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 10);
}

void Scene3::destroy()
{

}

void Scene3::update()
{
	shader.UpdateShader();
	trans.ChangeRotation(vec3(0.0f, 0.3f, 0.0f));
}

void Scene3::render()
{
	m_Window->clear();

	shader.Bind();

	shader.SetUniform4fv("model", trans.GetTransformationMatrix());
	shader.SetUniform4fv("view", camera.GetViewMatrix());
	shader.SetUniform4fv("projection", glm::perspective(camera.Zoom, m_Window->getAspect(), 0.1f, 1000.0f));
	shader.SetUniform3fv("viewPos", camera.Position);

	shader.SetUniformTexture(texture.GetTextureID(), "ourTexture1", 0);

	mesh->render();

	shader.Unbind();
}

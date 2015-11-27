#include "Scene5.h"

void Scene5::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 10);
	light.SetPosition(vec3(3.0f, 0.0f, 3.0f));
}

void Scene5::destroy()
{

}

void Scene5::update()
{
	shader.UpdateShader();
	trans.ChangeRotation(vec3(0.0f, 0.6f, 0.0f));
}

void Scene5::render()
{
	// Draw to Framebuffer
	frameBuffer.Bind();
		m_Window->clear();

		shader.Bind();

		shader.SetUniform4fv("model", trans.GetTransformationMatrix());
		shader.SetUniform4fv("view", camera.GetViewMatrix());
		shader.SetUniform4fv("projection", glm::perspective(camera.Zoom, m_Window->getAspect(), 0.1f, 1000.0f));
		shader.SetUniform3fv("viewPos", camera.Position);
		shader.SetUniform3fv("lightPos", light.GetPosition());
		shader.SetUniformTexture(texture.GetTextureID(), "ourTexture1", 0);

		mesh->render();

		shader.Unbind();
	frameBuffer.Unbind();

	frameBuffer.RenderWithShader(&edgeShader);
}
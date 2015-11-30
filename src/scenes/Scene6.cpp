#include "Scene6.h"

void Scene6::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 3);
	light.SetPosition(vec3(0.0f, 0.0f, 3.0f));
}

void Scene6::destroy()
{

}

void Scene6::update()
{
	shader.UpdateShader();
	
	Input& input = Input::instance();

	if (input.isKeyDown(SDL_SCANCODE_A)) {
		trans.ChangeRotation(vec3(0.0f, -0.6f, 0.0f));
	}

	if (input.isKeyDown(SDL_SCANCODE_D)) {
		trans.ChangeRotation(vec3(0.0f, 0.6f, 0.0f));
	}

	if (input.isKeyDown(SDL_SCANCODE_W)) {
		trans.ChangeRotation(vec3(-0.6f, 0.0f, 0.0f));
	}

	if (input.isKeyDown(SDL_SCANCODE_S)) {
		trans.ChangeRotation(vec3(0.6f, 0.0f, 0.0f));
	}

	if (input.isMouseDown(SDL_BUTTON_LEFT))
	{
		trans.ChangeRotation(vec3(input.getRelPos().y, input.getRelPos().x, 0.0f));
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
		trans.ChangePosition(vec3(input.getRelPos().x, -input.getRelPos().y, 0.0f));
	}
}

void Scene6::render()
{
	// Draw to Framebuffer
	//frameBuffer.Bind();
		m_Window->clear();

		shader.Bind();

		shader.SetUniform4fv("model", trans.GetTransformationMatrix());
		shader.SetUniform4fv("view", camera.GetViewMatrix());
		shader.SetUniform4fv("projection", glm::perspective(camera.Zoom, m_Window->getAspect(), 0.1f, 1000.0f));
		shader.SetUniform3fv("viewPos", camera.Position);
		shader.SetUniform3fv("lightPos", light.GetPosition());

		shader.SetUniformTexture(texture.GetTextureID(), "diffuseMap", 0);
		shader.SetUniformTexture(normal.GetTextureID(), "normalMap", 1);

		mesh->render();

		shader.Unbind();
	//frameBuffer.Unbind();

	//frameBuffer.Render();
}

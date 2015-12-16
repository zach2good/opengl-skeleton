#include "GScene1.h"

void GScene1::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 3);
	m_gameObject.m_Transform.SetPosition(vec3(1, 0, 0));
	m_gameObject2.m_Transform.SetPosition(vec3(-1, 0, 0));
}

void GScene1::destroy()
{

}

void GScene1::update()
{
	shader.UpdateShader();

	Input& input = Input::instance();

	float speed = 0.01f;

	if (input.isKeyDown(SDL_SCANCODE_A)) {
		camera.ProcessKeyboard(LEFT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_D)) {
		camera.ProcessKeyboard(RIGHT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_W)) {
		camera.ProcessKeyboard(UP, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_S)) {
		camera.ProcessKeyboard(DOWN, speed);
	}

	if (input.isMouseDown(SDL_BUTTON_LEFT))
	{
		//trans.ChangeRotation(vec3(input.getRelPos().y, input.getRelPos().x, 0.0f));
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
		//trans.ChangePosition(vec3(input.getRelPos().x, -input.getRelPos().y, 0.0f));
	}
}

void GScene1::render()
{
	// Clear Screen
	m_Window->clear();

	// Submit
	renderer.submit(&m_gameObject);
	renderer.submit(&m_gameObject2);

	// Draw
	renderer.draw(&shader, &camera);
}

#include "GScene1.h"

void GScene1::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(true);
	m_Window->setGLBlend(true);

	camera.Position = vec3(30, 30, 50);
	camera.calculate_lookAt_matrix(camera.Position, vec3(0));

	GameObject* floor = new GameObject();
	floor->m_Model = new Model("../res/models/quad.obj");
	floor->m_Transform.SetPosition(vec3(-500, 0, 100));
	floor->m_Transform.SetRotation(vec3(-90, 0, 0));
	floor->m_Transform.SetScale(vec3(1000, 1000, 1000));
	objects.push_back(floor);

	GameObject* mainModel = new GameObject();
	mainModel->m_Model = new Model("../res/rungholt/house.obj");
	mainModel->m_Transform.SetPosition(vec3(0, 0, 0));
	objects.push_back(mainModel);

	light = new GameObject();
	light->isLight = true;
	objects.push_back(light);
}

void GScene1::destroy()
{

}

void GScene1::update()
{
	shader.UpdateShader();

	Input& input = Input::instance();

	float speed = 0.1f;

	if (input.isKeyDown(SDL_SCANCODE_A)) {
		camera.ProcessKeyboard(LEFT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_D)) {
		camera.ProcessKeyboard(RIGHT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_W)) {
		camera.ProcessKeyboard(FORWARD, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_S)) {
		camera.ProcessKeyboard(BACKWARD, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_E)) {
		camera.ProcessKeyboard(UP, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_Q)) {
		camera.ProcessKeyboard(DOWN, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_SPACE)) {
		camera.LookAt(vec3(0));
	}

	if (input.isMouseDown(SDL_BUTTON_LEFT))
	{
		camera.ProcessMouseMovement(input.getRelPos().x * 10.0f, -input.getRelPos().y * 10.0f);
	}

	float ticks = ((float)SDL_GetTicks()) / 500.0f;
	float x_mov = sinf(ticks);

	light->m_Transform.SetPosition(camera.Position);
}

void GScene1::render()
{
	for (GameObject* g : objects)
	{
		renderer.submit(g);
	}

	glViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.draw(&shader, &camera);
}

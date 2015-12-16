#include "GScene1.h"

void GScene1::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 5);

	GameObject* mainModel = new GameObject();
	mainModel->m_Model = new Model("../res/rungholt/house.obj");
	mainModel->m_Transform.SetPosition(vec3(0, -10, -50));
	objects.push_back(mainModel);

	light = new GameObject();
	light->isLight = true;
	objects.push_back(light);

	//for (int i = 0; i < 100; i++)
	//{
	//	GameObject* g = new GameObject();

	//	g->m_Transform.SetPosition(
	//		vec3((rand() % 1000 - 500) / 100,
	//			(rand() % 1000 - 500) / 100,
	//			(rand() % 1000 - 500) / 100));

	//	g->m_Mesh = new Mesh("../res/models/cube.obj");
	//	g->m_Transform.SetScale(vec3(0.05f));
	//	objects.push_back(g);
	//}
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
	// Clear Screen
	m_Window->clear();

	// Submit
	for (GameObject* g : objects)
	{
		renderer.submit(g);
	}

	// Draw
	renderer.draw(&shader, &camera);
}

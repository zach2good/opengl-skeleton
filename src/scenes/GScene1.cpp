#include "GScene1.h"

void GScene1::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 5);

	m_gameObject.m_Transform.SetPosition(vec3(1, 0, 0));
	m_gameObject.m_Transform.SetScale(vec3(0.4f));
	m_gameObject.m_Mesh = new Mesh("../res/models/box.obj");

	m_gameObject2.m_Transform.SetPosition(vec3(-1, 0, 0));
	m_gameObject2.m_Mesh = new Mesh("../res/models/cube.obj");

	m_gameObject3.m_Transform.SetPosition(vec3(0, 0, -1));
	m_gameObject3.m_Transform.SetScale(vec3(0.4f));
	m_gameObject3.m_Mesh = new Mesh("../res/models/flashlight.obj");

	m_lightGameObject.isLight = true;
	m_lightGameObject.m_Transform.SetPosition(vec3(0, 1.5, 1));
	m_lightGameObject.m_Transform.SetScale(vec3(0.05f));
	m_lightGameObject.m_Mesh = new Mesh("../res/models/sphere.obj");

	for (int i = 0; i < 100; i++)
	{
		GameObject* g = new GameObject();
		g->m_Transform.SetPosition(vec3(rand() % 4 - 2, rand() % 4 - 2, rand() % 4 - 2));
		g->m_Mesh = new Mesh("../res/models/cube.obj");
		g->m_Transform.SetScale(vec3(0.05f));
		objects.push_back(g);
	}
	
	m_floorGameObject.m_Transform.SetPosition(vec3(-10, -1, -10));
	m_floorGameObject.m_Transform.SetRotation(vec3(90, 0, 0));
	m_floorGameObject.m_Transform.SetScale(vec3(10, 10, 0));
	m_floorGameObject.m_Mesh = new Mesh("../res/models/quad.obj");
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
		//trans.ChangeRotation(vec3(input.getRelPos().y, input.getRelPos().x, 0.0f));
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
		//trans.ChangePosition(vec3(input.getRelPos().x, -input.getRelPos().y, 0.0f));
	}

	float ticks = ((float)SDL_GetTicks()) / 500.0f;
	float x_mov = sinf(ticks);
	float y = m_lightGameObject.m_Transform.GetPosition().y;

	m_lightGameObject.m_Transform.SetPosition(vec3(x_mov, y, 1));
}

void GScene1::render()
{
	// Clear Screen
	m_Window->clear();

	// Submit
	renderer.submit(&m_gameObject);
	renderer.submit(&m_gameObject2);
	renderer.submit(&m_gameObject3);
	renderer.submit(&m_lightGameObject);

	renderer.submit(&m_floorGameObject);
	
	for (GameObject* g : objects)
	{
		renderer.submit(g);
	}

	// Draw
	renderer.draw(&shader, &camera);
}

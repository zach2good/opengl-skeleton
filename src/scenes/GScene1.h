#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../core/Input.h"
#include "../graphics/ForwardRenderer.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/Camera.h"
#include "../graphics/Mesh.h"
#include "../components/Transform.h"

class GScene1
{
public:
	GScene1(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;

	ForwardRenderer renderer = ForwardRenderer(m_Window);
	ShaderProgram shader = ShaderProgram("../res/shaders/gscene1");
	
	Camera camera;

	std::vector<GameObject*> objects;
	GameObject* light;
};

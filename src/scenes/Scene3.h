#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/Texture.h"

class Scene3
{
public:
	Scene3(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;

	ShaderProgram shader = ShaderProgram("../res/shaders/scene3");
};
